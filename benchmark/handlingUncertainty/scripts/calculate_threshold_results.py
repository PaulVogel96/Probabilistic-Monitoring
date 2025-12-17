#!/usr/bin/env python3
import sys
import re
from pathlib import Path
from typing import List

import pandas as pd

# ==============================
# CONFIGURATION
# ==============================

INPUT_FILES = [
    "../blocking_missing/coupled_prob_var_limit/seed2025/burst_mr_0_1_L_3/result.csv",
    "../blocking_missing/coupled_prob_var_limit/seed2025/burst_mr_0_1_L_5/result.csv",
    "../blocking_missing/coupled_prob_var_limit/seed2025/burst_mr_0_1_L_10/result.csv",
    "../blocking_missing/coupled_prob_var_limit/seed2025/burst_mr_0_2_L_3/result.csv",
    "../blocking_missing/coupled_prob_var_limit/seed2025/burst_mr_0_2_L_5/result.csv",
    "../blocking_missing/coupled_prob_var_limit/seed2025/burst_mr_0_2_L_10/result.csv",
    "../blocking_missing/coupled_prob_var_limit/seed2099/burst_mr_0_1_L_3/result.csv",
    "../blocking_missing/coupled_prob_var_limit/seed2099/burst_mr_0_1_L_5/result.csv",
    "../blocking_missing/coupled_prob_var_limit/seed2099/burst_mr_0_1_L_10/result.csv",
    "../blocking_missing/coupled_prob_var_limit/seed2099/burst_mr_0_2_L_3/result.csv",
    "../blocking_missing/coupled_prob_var_limit/seed2099/burst_mr_0_2_L_5/result.csv",
    "../blocking_missing/coupled_prob_var_limit/seed2099/burst_mr_0_2_L_10/result.csv",
    "../event_missing/coupled_prob_var_limit/seed2025/col-p_mcar_1_0/result.csv",
    "../event_missing/coupled_prob_var_limit/seed2025/col-r_mcar_1_0/result.csv",
    "../event_missing/coupled_prob_var_limit/seed2025/col-s_mcar_1_0/result.csv",
    "../event_missing/coupled_prob_var_limit/seed2099/col-p_mcar_1_0/result.csv",
    "../event_missing/coupled_prob_var_limit/seed2099/col-r_mcar_1_0/result.csv",
    "../event_missing/coupled_prob_var_limit/seed2099/col-s_mcar_1_0/result.csv",
    "../periodic/coupled_prob_var_limit/seed2025/T10_keep0_5/result.csv",
    "../periodic/coupled_prob_var_limit/seed2025/T10_keep0_7/result.csv",
    "../periodic/coupled_prob_var_limit/seed2025/T20_keep0_5/result.csv",
    "../periodic/coupled_prob_var_limit/seed2025/T20_keep0_7/result.csv",
    "../periodic/coupled_prob_var_limit/seed2099/T10_keep0_5/result.csv",
    "../periodic/coupled_prob_var_limit/seed2099/T10_keep0_7/result.csv",
    "../periodic/coupled_prob_var_limit/seed2099/T20_keep0_5/result.csv",
    "../periodic/coupled_prob_var_limit/seed2099/T20_keep0_7/result.csv",
    "../proportional_missing/coupled_prob_var_limit/seed2025/iid_mr_0_1/result.csv",
    "../proportional_missing/coupled_prob_var_limit/seed2025/iid_mr_0_2/result.csv",
    "../proportional_missing/coupled_prob_var_limit/seed2025/iid_mr_0_05/result.csv",
    "../proportional_missing/coupled_prob_var_limit/seed2099/iid_mr_0_1/result.csv",
    "../proportional_missing/coupled_prob_var_limit/seed2099/iid_mr_0_2/result.csv",
    "../proportional_missing/coupled_prob_var_limit/seed2099/iid_mr_0_05/result.csv",
]

LOW_SUM = 0.99
HIGH_SUM = 1.01

# ==============================
# INTERNALS
# ==============================

SVI_RE = re.compile(
    r"S:\s*([0-9]*\.?[0-9]+)\s*;\s*V:\s*([0-9]*\.?[0-9]+)\s*;\s*I:\s*([0-9]*\.?[0-9]+)"
)

def parse_svi(cell):
    if pd.isna(cell):
        return (None, None, None)
    s = str(cell).strip().strip('"')
    m = SVI_RE.search(s)
    if not m:
        return (None, None, None)
    return (float(m.group(1)), float(m.group(2)), float(m.group(3)))

def threshold_to_filename(threshold: float) -> str:
    return f"{threshold:.12g}".replace(".", "_")

def warn_on_bad_sums(csv_path: Path, times: pd.Series, pred_cols, svi_table):
    for col in pred_cols:
        for idx, (S, V, I) in enumerate(svi_table[col]):
            if S is None:
                continue
            total = S + V + I
            EPS = 1e-9
            if total < (LOW_SUM - EPS) or total > (HIGH_SUM + EPS):
                t = times.iloc[idx]
                print(
                    f"WARNING: {csv_path} time={t} predicate={col} "
                    f"S+V+I={total:.6f} (S={S:.6f}, V={V:.6f}, I={I:.6f})"
                )

def process_file(csv_path: Path, thresholds: List[float]) -> None:
    df = pd.read_csv(csv_path)

    if "time" not in df.columns:
        raise ValueError(f"{csv_path} missing 'time' column")

    pred_cols = [c for c in df.columns if c.startswith("pred_P")]
    if not pred_cols:
        raise ValueError(f"{csv_path} has no pred_P* columns")

    times = df["time"]

    svi_table = {col: df[col].apply(parse_svi).tolist() for col in pred_cols}

    warn_on_bad_sums(csv_path, times, pred_cols, svi_table)

    v_table = {
        col: pd.Series([t[1] if t[1] is not None else 0.0 for t in svi_table[col]])
        for col in pred_cols
    }

    for threshold in thresholds:
        out = pd.DataFrame()
        out["time"] = times

        for col in pred_cols:
            out[col] = (v_table[col] >= threshold).astype(int)

        fname = f"result_{threshold_to_filename(threshold)}.csv"
        out_path = csv_path.parent / fname

        out.to_csv(out_path, index=False, quoting=1)
        print(f"Wrote: {out_path}")

def main():
    if len(sys.argv) < 2:
        raise SystemExit("Usage: python make_binary_results.py <threshold1> [threshold2 ...]")

    try:
        thresholds = [float(t) for t in sys.argv[1:]]
    except ValueError:
        raise SystemExit("All thresholds must be numeric")

    for t in thresholds:
        if not (0.0 <= t <= 1.0):
            raise SystemExit(f"Threshold out of range [0,1]: {t}")

    for f in INPUT_FILES:
        csv_path = Path(f)
        if not csv_path.exists():
            print(f"Skipping (not found): {csv_path}")
            continue
        process_file(csv_path, thresholds)

if __name__ == "__main__":
    main()
