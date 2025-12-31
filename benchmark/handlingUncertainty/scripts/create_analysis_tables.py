#!/usr/bin/env python3
from pathlib import Path
import pandas as pd

# ==============================
# CONFIG
# ==============================

SCRIPT_DIR = Path(__file__).resolve().parent
ROOT_DIR = SCRIPT_DIR.parent  # handlingUncertainty/

SEEDS = ["seed2025", "seed2099"]
PROPERTIES = ["P1", "P2", "P3", "P4", "Total"]

SETUP_COUPLED = "coupled"
SETUP_VAR = "coupled_prob_var_limit"

# Metrics filenames
COUPLED_METRICS_FILE = "results_metrics.csv"
VAR_LIMIT_METRICS_PATTERN = "result_*_metrics.csv"

# TP-times filenames
COUPLED_TP_FILE = "result_tp_times.csv"
VAR_LIMIT_TP_SUFFIX = "_tp_times.csv"  # result_0_1_tp_times.csv etc.

OUTPUT_DIR = ROOT_DIR / "merged_results"

# CSV formatting for LibreOffice Calc
CSV_SEP = ";"
CSV_DECIMAL = ","
FLOAT_FMT = "%.6f"


# ==============================
# HELPERS
# ==============================

def collect_experiments_for_seed(seed: str):
    """
    Build mapping:
      (general_experiment, specific_experiment_folder) -> {
          "coupled_metrics": Path|None,
          "coupled_tp": Path|None,
          "var_metrics": [Path...],  # result_0_1_metrics.csv, ...
      }
    Ordering guarantee: var_metrics sorted by filename so 0_1..0_5.
    """
    experiments = {}

    for general_dir in ROOT_DIR.iterdir():
        if not general_dir.is_dir():
            continue

        for setup_name in [SETUP_COUPLED, SETUP_VAR]:
            setup_dir = general_dir / setup_name
            if not setup_dir.is_dir():
                continue

            seed_dir = setup_dir / seed
            if not seed_dir.is_dir():
                continue

            for specific_dir in seed_dir.iterdir():
                if not specific_dir.is_dir():
                    continue

                key = (general_dir.name, specific_dir.name)
                ex = experiments.setdefault(
                    key,
                    {"coupled_metrics": None, "coupled_tp": None, "var_metrics": []},
                )

                if setup_name == SETUP_COUPLED:
                    m = specific_dir / COUPLED_METRICS_FILE
                    t = specific_dir / COUPLED_TP_FILE
                    if m.exists():
                        ex["coupled_metrics"] = m
                    if t.exists():
                        ex["coupled_tp"] = t
                else:
                    for candidate in specific_dir.glob(VAR_LIMIT_METRICS_PATTERN):
                        if candidate.is_file():
                            ex["var_metrics"].append(candidate)

    for _, group in experiments.items():
        group["var_metrics"].sort(key=lambda p: p.name)

    return experiments


def read_metrics_for_file(csv_path: Path):
    """
    Read one metrics file and return:
      Property -> dict with TP,FP,FN,TN,Precision,Recall,F1,IoU,FP_pct,Denom (if present)
    """
    try:
        df = pd.read_csv(csv_path)
    except Exception as e:
        print(f"Could not read {csv_path}: {e}")
        return {}

    if "Property" not in df.columns:
        print(f"Skipping {csv_path}: no 'Property' column")
        return {}

    required = ["TP", "FP", "FN", "TN", "Precision", "Recall", "F1", "IoU"]
    missing = [c for c in required if c not in df.columns]
    if missing:
        print(f"Skipping {csv_path}: missing columns {missing}")
        return {}

    result = {}
    for prop in PROPERTIES:
        row_df = df[df["Property"].astype(str).str.strip() == prop]
        if row_df.empty:
            # Not fatal; continue
            continue
        row = row_df.iloc[0]
        d = {c: row[c] for c in required}
        if "FP_pct" in df.columns:
            d["FP_pct"] = row["FP_pct"]
        if "Denom" in df.columns:
            d["Denom"] = row["Denom"]
        result[prop] = d

    return result


def read_tp_times(tp_path: Path):
    """
    Read one TP-times file and return:
      Property -> set(str(time))
    If a file has 0 TP rows overall, this returns {} (still valid).
    """
    try:
        df = pd.read_csv(tp_path)
    except Exception as e:
        print(f"Could not read {tp_path}: {e}")
        return None  # None means "not available"

    if "Property" not in df.columns or "time" not in df.columns:
        print(f"Skipping {tp_path}: must contain Property,time")
        return None

    out = {}
    if len(df) == 0:
        return out

    df["Property"] = df["Property"].astype(str).str.strip()
    # Store time as string to avoid dtype mismatch
    df["time"] = df["time"].astype(str)

    for prop, grp in df.groupby("Property"):
        out[str(prop)] = set(grp["time"].tolist())

    return out


def ensure_fp_pct_and_denom(metrics: dict) -> None:
    """
    If FP_pct or Denom are missing in metrics[prop], compute them from counts.
    """
    tp = float(metrics.get("TP", 0) or 0)
    fp = float(metrics.get("FP", 0) or 0)
    fn = float(metrics.get("FN", 0) or 0)
    tn = float(metrics.get("TN", 0) or 0)

    denom = tp + fp + fn + tn
    if "Denom" not in metrics or pd.isna(metrics.get("Denom")):
        metrics["Denom"] = denom

    if "FP_pct" not in metrics or pd.isna(metrics.get("FP_pct")):
        metrics["FP_pct"] = (fp / denom) if denom > 0 else 0.0


def rel_after_handling_uncertainty(p: Path) -> str:
    return str(p.relative_to(ROOT_DIR))


def write_calc_csv(df: pd.DataFrame, out_path: Path):
    out_path.parent.mkdir(parents=True, exist_ok=True)
    df.to_csv(
        out_path,
        index=False,
        sep=CSV_SEP,
        decimal=CSV_DECIMAL,
        float_format=FLOAT_FMT,
        encoding="utf-8",
    )


# ==============================
# MAIN MERGE
# ==============================

def build_merged_tables_for_seed(seed: str):
    experiments = collect_experiments_for_seed(seed)
    if not experiments:
        print(f"No result metric files found for {seed}")
        return

    per_property_rows = {prop: [] for prop in PROPERTIES}

    for (general, specific) in sorted(experiments.keys()):
        group = experiments[(general, specific)]

        coupled_metrics_path = group["coupled_metrics"]
        coupled_tp_path = group["coupled_tp"]

        det_tp_sets = None
        if coupled_tp_path and coupled_tp_path.exists():
            det_tp_sets = read_tp_times(coupled_tp_path)
            if det_tp_sets is None:
                print(f"WARNING: Could not load deterministic TP-times: {coupled_tp_path}")

        def add_file(metrics_path: Path, is_prob: bool):
            metrics_by_prop = read_metrics_for_file(metrics_path)
            if not metrics_by_prop:
                return

            prob_tp_sets = None
            if is_prob:
                base = metrics_path.stem.replace("_metrics", "")  # result_0_1
                tp_path = metrics_path.parent / f"{base}{VAR_LIMIT_TP_SUFFIX}"
                if tp_path.exists():
                    prob_tp_sets = read_tp_times(tp_path)
                    if prob_tp_sets is None:
                        print(f"WARNING: Could not load prob TP-times: {tp_path}")
                else:
                    print(f"WARNING: Missing TP-times file for {metrics_path}: expected {tp_path}")

            rel_str = rel_after_handling_uncertainty(metrics_path)

            for prop in PROPERTIES:
                if prop not in metrics_by_prop:
                    continue

                m = metrics_by_prop[prop]
                ensure_fp_pct_and_denom(m)

                row = {
                    "file": rel_str,
                    "TP": m["TP"],
                    "FP": m["FP"],
                    "FN": m["FN"],
                    "TN": m["TN"],
                    "Precision": m["Precision"],
                    "Recall": m["Recall"],
                    "F1": m["F1"],
                    "IoU": m["IoU"],
                    "FP_pct": m["FP_pct"],
                    "Denom": m["Denom"],
                }

                # ✅ FIX: compute overlap even when TP sets are empty dicts {}
                if is_prob and (det_tp_sets is not None) and (prob_tp_sets is not None):
                    det_set = det_tp_sets.get(prop, set())
                    prob_set = prob_tp_sets.get(prop, set())

                    row["TP_identical_vs_det"] = len(det_set & prob_set)
                    row["TP_det_not_in_prob"] = len(det_set - prob_set)
                    row["TP_prob_not_in_det"] = len(prob_set - det_set)
                else:
                    row["TP_identical_vs_det"] = ""
                    row["TP_det_not_in_prob"] = ""
                    row["TP_prob_not_in_det"] = ""

                per_property_rows[prop].append(row)

        # (1) deterministic first
        if coupled_metrics_path is not None and coupled_metrics_path.exists():
            add_file(coupled_metrics_path, is_prob=False)

        # (2) probabilistic thresholds 0_1..0_5 in filename order
        for var_metrics_path in group["var_metrics"]:
            add_file(var_metrics_path, is_prob=True)

    OUTPUT_DIR.mkdir(parents=True, exist_ok=True)

    for prop in PROPERTIES:
        rows = per_property_rows[prop]
        if not rows:
            print(f"No rows collected for {prop} in {seed}, skipping.")
            continue

        merged_df = pd.DataFrame(rows)

        # numeric columns
        num_cols = [
            "TP", "FP", "FN", "TN",
            "Precision", "Recall", "F1", "IoU",
            "FP_pct", "Denom",
            "TP_identical_vs_det", "TP_det_not_in_prob", "TP_prob_not_in_det",
        ]
        for col in num_cols:
            if col in merged_df.columns:
                merged_df[col] = pd.to_numeric(merged_df[col], errors="ignore")

        out_path = OUTPUT_DIR / f"merged_{seed}_{prop}.csv"
        write_calc_csv(merged_df, out_path)
        print(f"Wrote merged file: {out_path}")


def main():
    print(f"ROOT_DIR = {ROOT_DIR}")
    print(f"Writing merged CSVs to: {OUTPUT_DIR}")

    for seed in SEEDS:
        print(f"\n=== Processing seed {seed} ===")
        build_merged_tables_for_seed(seed)


if __name__ == "__main__":
    main()