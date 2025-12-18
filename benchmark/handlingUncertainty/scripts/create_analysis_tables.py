#!/usr/bin/env python3
import os
from pathlib import Path
import pandas as pd

# ==============================
# CONFIG
# ==============================

# This script is expected to live in:
#   benchmark/handlingUncertainty/scripts/
# ROOT_DIR will then be:
#   benchmark/handlingUncertainty/
SCRIPT_DIR = Path(__file__).resolve().parent
ROOT_DIR = SCRIPT_DIR.parent

SEEDS = ["seed2025", "seed2099"]
PROPERTIES = ["P1", "P2", "P3", "P4", "Total"]

SETUP_COUPLED = "coupled"
SETUP_VAR = "coupled_prob_var_limit"

# Filenames for metrics
COUPLED_FILE = "results_metrics.csv"
VAR_LIMIT_PATTERN = "result_*_metrics.csv"

# Where to put the merged CSVs
OUTPUT_DIR = ROOT_DIR / "merged_results"


# ==============================
# HELPERS
# ==============================

def collect_experiments_for_seed(seed: str):
    """
    Build a mapping:
      (general_experiment, specific_experiment_folder) -> {
          "coupled": Path or None,
          "var": [Path, Path, ...]  # result_0_1_metrics.csv, ...
      }
    for the given seed.
    """
    experiments = {}

    # general_experiment dirs are direct children of ROOT_DIR
    for general_dir in ROOT_DIR.iterdir():
        if not general_dir.is_dir():
            continue

        # coupled / coupled_prob_var_limit under each general_dir
        for setup_name in [SETUP_COUPLED, SETUP_VAR]:
            setup_dir = general_dir / setup_name
            if not setup_dir.is_dir():
                continue

            seed_dir = setup_dir / seed
            if not seed_dir.is_dir():
                continue

            # specific_experiment_folder under each seed dir
            for specific_dir in seed_dir.iterdir():
                if not specific_dir.is_dir():
                    continue

                key = (general_dir.name, specific_dir.name)
                ex = experiments.setdefault(key, {"coupled": None, "var": []})

                if setup_name == SETUP_COUPLED:
                    candidate = specific_dir / COUPLED_FILE
                    if candidate.exists():
                        ex["coupled"] = candidate
                else:
                    # coupled_prob_var_limit
                    for candidate in specific_dir.glob(VAR_LIMIT_PATTERN):
                        if candidate.is_file():
                            ex["var"].append(candidate)

    # sort the var files for each experiment by filename (so 0_1, 0_2, ..., 0_5)
    for key, group in experiments.items():
        group["var"].sort(key=lambda p: p.name)

    return experiments


def read_metrics_for_file(csv_path: Path):
    """
    Read one results_metrics / result_*_metrics file and
    return a dict: Property -> metrics dict.
    """
    try:
        df = pd.read_csv(csv_path)
    except Exception as e:
        print(f"Could not read {csv_path}: {e}")
        return {}

    if "Property" not in df.columns:
        print(f"Skipping {csv_path}: no 'Property' column")
        return {}

    metrics_cols = ["TP", "FP", "FN", "TN", "Precision", "Recall", "F1", "IoU"]
    missing_any = [c for c in metrics_cols if c not in df.columns]
    if missing_any:
        print(f"Skipping {csv_path}: missing metric columns {missing_any}")
        return {}

    result = {}
    for prop in PROPERTIES:
        row_df = df[df["Property"] == prop]
        if row_df.empty:
            print(f"WARNING: {csv_path} missing row for Property={prop}")
            continue
        row = row_df.iloc[0]
        result[prop] = {m: row[m] for m in metrics_cols}

    return result


def build_merged_tables_for_seed(seed: str):
    experiments = collect_experiments_for_seed(seed)
    if not experiments:
        print(f"No result metric files found for {seed}")
        return

    # property -> list of row dicts
    per_property_rows = {prop: [] for prop in PROPERTIES}

    # Sort experiments by (general_experiment, specific_experiment_folder)
    for (general, specific) in sorted(experiments.keys()):
        group = experiments[(general, specific)]

        # Helper: add all props from one CSV (keeps order coupled, then var)
        def add_file(csv_path: Path):
            metrics_by_prop = read_metrics_for_file(csv_path)
            if not metrics_by_prop:
                return
            # relative path starting after handlingUncertainty/
            rel_path = csv_path.relative_to(ROOT_DIR)
            rel_str = str(rel_path)
            for prop, metrics in metrics_by_prop.items():
                row = {"file": rel_str}
                row.update(metrics)
                per_property_rows[prop].append(row)

        # 1) coupled (if exists)
        if group["coupled"] is not None:
            add_file(group["coupled"])

        # 2) coupled_prob_var_limit files in filename order
        for var_path in group["var"]:
            add_file(var_path)

    OUTPUT_DIR.mkdir(parents=True, exist_ok=True)

    # Write one merged CSV per property for this seed
    for prop in PROPERTIES:
        rows = per_property_rows[prop]
        if not rows:
            print(f"No rows collected for {prop} in {seed}, skipping.")
            continue

        merged_df = pd.DataFrame(rows)

        # Ensure metric columns are numeric so formatting is consistent
        metric_cols = ["TP", "FP", "FN", "TN", "Precision", "Recall", "F1", "IoU"]
        for col in metric_cols:
            if col in merged_df.columns:
                merged_df[col] = pd.to_numeric(merged_df[col], errors="coerce")

        out_path = OUTPUT_DIR / f"merged_{seed}_{prop}.csv"

        # Write with:
        # - first line: sep=;   (hint for LibreOffice/Excel)
        # - separator: ;        (so commas can be used as decimal sep)
        # - decimal: ,          (European decimal)
        with open(out_path, "w", encoding="utf-8", newline="") as f:
            f.write("sep=;\n")
            merged_df.to_csv(
                f,
                index=False,
                sep=";",
                decimal=",",
                float_format="%.6f",  # 6 decimal places for floats
            )

        print(f"Wrote merged file: {out_path}")


# ==============================
# MAIN
# ==============================

def main():
    print(f"ROOT_DIR = {ROOT_DIR}")
    print(f"Writing merged CSVs to: {OUTPUT_DIR}")

    for seed in SEEDS:
        print(f"\n=== Processing seed {seed} ===")
        build_merged_tables_for_seed(seed)


if __name__ == "__main__":
    main()
