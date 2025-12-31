import pandas as pd
import csv
from pathlib import Path

# Put as many prediction files here as you want
PRED_FILES = [
    "../blocking_missing/coupled/seed2025/burst_mr_0_1_L_3/result.csv",
    "../blocking_missing/coupled_prob_var_limit/seed2025/burst_mr_0_1_L_3/result_0_1.csv",
    "../blocking_missing/coupled_prob_var_limit/seed2025/burst_mr_0_1_L_3/result_0_2.csv",
    "../blocking_missing/coupled_prob_var_limit/seed2025/burst_mr_0_1_L_3/result_0_3.csv",
    "../blocking_missing/coupled_prob_var_limit/seed2025/burst_mr_0_1_L_3/result_0_4.csv",
    "../blocking_missing/coupled_prob_var_limit/seed2025/burst_mr_0_1_L_3/result_0_5.csv",

    "../blocking_missing/coupled/seed2025/burst_mr_0_1_L_5/result.csv",
    "../blocking_missing/coupled_prob_var_limit/seed2025/burst_mr_0_1_L_5/result_0_1.csv",
    "../blocking_missing/coupled_prob_var_limit/seed2025/burst_mr_0_1_L_5/result_0_2.csv",
    "../blocking_missing/coupled_prob_var_limit/seed2025/burst_mr_0_1_L_5/result_0_3.csv",
    "../blocking_missing/coupled_prob_var_limit/seed2025/burst_mr_0_1_L_5/result_0_4.csv",
    "../blocking_missing/coupled_prob_var_limit/seed2025/burst_mr_0_1_L_5/result_0_5.csv",

    "../blocking_missing/coupled/seed2025/burst_mr_0_1_L_10/result.csv",
    "../blocking_missing/coupled_prob_var_limit/seed2025/burst_mr_0_1_L_10/result_0_1.csv",
    "../blocking_missing/coupled_prob_var_limit/seed2025/burst_mr_0_1_L_10/result_0_2.csv",
    "../blocking_missing/coupled_prob_var_limit/seed2025/burst_mr_0_1_L_10/result_0_3.csv",
    "../blocking_missing/coupled_prob_var_limit/seed2025/burst_mr_0_1_L_10/result_0_4.csv",
    "../blocking_missing/coupled_prob_var_limit/seed2025/burst_mr_0_1_L_10/result_0_5.csv",

    "../blocking_missing/coupled/seed2025/burst_mr_0_2_L_3/result.csv",
    "../blocking_missing/coupled_prob_var_limit/seed2025/burst_mr_0_2_L_3/result_0_1.csv",
    "../blocking_missing/coupled_prob_var_limit/seed2025/burst_mr_0_2_L_3/result_0_2.csv",
    "../blocking_missing/coupled_prob_var_limit/seed2025/burst_mr_0_2_L_3/result_0_3.csv",
    "../blocking_missing/coupled_prob_var_limit/seed2025/burst_mr_0_2_L_3/result_0_4.csv",
    "../blocking_missing/coupled_prob_var_limit/seed2025/burst_mr_0_2_L_3/result_0_5.csv",

    "../blocking_missing/coupled/seed2025/burst_mr_0_2_L_5/result.csv",
    "../blocking_missing/coupled_prob_var_limit/seed2025/burst_mr_0_2_L_5/result_0_1.csv",
    "../blocking_missing/coupled_prob_var_limit/seed2025/burst_mr_0_2_L_5/result_0_2.csv",
    "../blocking_missing/coupled_prob_var_limit/seed2025/burst_mr_0_2_L_5/result_0_3.csv",
    "../blocking_missing/coupled_prob_var_limit/seed2025/burst_mr_0_2_L_5/result_0_4.csv",
    "../blocking_missing/coupled_prob_var_limit/seed2025/burst_mr_0_2_L_5/result_0_5.csv",

    "../blocking_missing/coupled/seed2025/burst_mr_0_2_L_10/result.csv",
    "../blocking_missing/coupled_prob_var_limit/seed2025/burst_mr_0_2_L_10/result_0_1.csv",
    "../blocking_missing/coupled_prob_var_limit/seed2025/burst_mr_0_2_L_10/result_0_2.csv",
    "../blocking_missing/coupled_prob_var_limit/seed2025/burst_mr_0_2_L_10/result_0_3.csv",
    "../blocking_missing/coupled_prob_var_limit/seed2025/burst_mr_0_2_L_10/result_0_4.csv",
    "../blocking_missing/coupled_prob_var_limit/seed2025/burst_mr_0_2_L_10/result_0_5.csv",

    "../blocking_missing/coupled/seed2099/burst_mr_0_1_L_3/result.csv",
    "../blocking_missing/coupled_prob_var_limit/seed2099/burst_mr_0_1_L_3/result_0_1.csv",
    "../blocking_missing/coupled_prob_var_limit/seed2099/burst_mr_0_1_L_3/result_0_2.csv",
    "../blocking_missing/coupled_prob_var_limit/seed2099/burst_mr_0_1_L_3/result_0_3.csv",
    "../blocking_missing/coupled_prob_var_limit/seed2099/burst_mr_0_1_L_3/result_0_4.csv",
    "../blocking_missing/coupled_prob_var_limit/seed2099/burst_mr_0_1_L_3/result_0_5.csv",

    "../blocking_missing/coupled/seed2099/burst_mr_0_1_L_5/result.csv",
    "../blocking_missing/coupled_prob_var_limit/seed2099/burst_mr_0_1_L_5/result_0_1.csv",
    "../blocking_missing/coupled_prob_var_limit/seed2099/burst_mr_0_1_L_5/result_0_2.csv",
    "../blocking_missing/coupled_prob_var_limit/seed2099/burst_mr_0_1_L_5/result_0_3.csv",
    "../blocking_missing/coupled_prob_var_limit/seed2099/burst_mr_0_1_L_5/result_0_4.csv",
    "../blocking_missing/coupled_prob_var_limit/seed2099/burst_mr_0_1_L_5/result_0_5.csv",

    "../blocking_missing/coupled/seed2099/burst_mr_0_1_L_10/result.csv",
    "../blocking_missing/coupled_prob_var_limit/seed2099/burst_mr_0_1_L_10/result_0_1.csv",
    "../blocking_missing/coupled_prob_var_limit/seed2099/burst_mr_0_1_L_10/result_0_2.csv",
    "../blocking_missing/coupled_prob_var_limit/seed2099/burst_mr_0_1_L_10/result_0_3.csv",
    "../blocking_missing/coupled_prob_var_limit/seed2099/burst_mr_0_1_L_10/result_0_4.csv",
    "../blocking_missing/coupled_prob_var_limit/seed2099/burst_mr_0_1_L_10/result_0_5.csv",

    "../blocking_missing/coupled/seed2099/burst_mr_0_2_L_3/result.csv",
    "../blocking_missing/coupled_prob_var_limit/seed2099/burst_mr_0_2_L_3/result_0_1.csv",
    "../blocking_missing/coupled_prob_var_limit/seed2099/burst_mr_0_2_L_3/result_0_2.csv",
    "../blocking_missing/coupled_prob_var_limit/seed2099/burst_mr_0_2_L_3/result_0_3.csv",
    "../blocking_missing/coupled_prob_var_limit/seed2099/burst_mr_0_2_L_3/result_0_4.csv",
    "../blocking_missing/coupled_prob_var_limit/seed2099/burst_mr_0_2_L_3/result_0_5.csv",

    "../blocking_missing/coupled/seed2099/burst_mr_0_2_L_5/result.csv",
    "../blocking_missing/coupled_prob_var_limit/seed2099/burst_mr_0_2_L_5/result_0_1.csv",
    "../blocking_missing/coupled_prob_var_limit/seed2099/burst_mr_0_2_L_5/result_0_2.csv",
    "../blocking_missing/coupled_prob_var_limit/seed2099/burst_mr_0_2_L_5/result_0_3.csv",
    "../blocking_missing/coupled_prob_var_limit/seed2099/burst_mr_0_2_L_5/result_0_4.csv",
    "../blocking_missing/coupled_prob_var_limit/seed2099/burst_mr_0_2_L_5/result_0_5.csv",

    "../blocking_missing/coupled/seed2099/burst_mr_0_2_L_10/result.csv",
    "../blocking_missing/coupled_prob_var_limit/seed2099/burst_mr_0_2_L_10/result_0_1.csv",
    "../blocking_missing/coupled_prob_var_limit/seed2099/burst_mr_0_2_L_10/result_0_2.csv",
    "../blocking_missing/coupled_prob_var_limit/seed2099/burst_mr_0_2_L_10/result_0_3.csv",
    "../blocking_missing/coupled_prob_var_limit/seed2099/burst_mr_0_2_L_10/result_0_4.csv",
    "../blocking_missing/coupled_prob_var_limit/seed2099/burst_mr_0_2_L_10/result_0_5.csv",

    "../event_missing/coupled/seed2025/col-p_mcar_1_0/result.csv",
    "../event_missing/coupled_prob_var_limit/seed2025/col-p_mcar_1_0/result_0_1.csv",
    "../event_missing/coupled_prob_var_limit/seed2025/col-p_mcar_1_0/result_0_2.csv",
    "../event_missing/coupled_prob_var_limit/seed2025/col-p_mcar_1_0/result_0_3.csv",
    "../event_missing/coupled_prob_var_limit/seed2025/col-p_mcar_1_0/result_0_4.csv",
    "../event_missing/coupled_prob_var_limit/seed2025/col-p_mcar_1_0/result_0_5.csv",

    "../event_missing/coupled/seed2025/col-r_mcar_1_0/result.csv",
    "../event_missing/coupled_prob_var_limit/seed2025/col-r_mcar_1_0/result_0_1.csv",
    "../event_missing/coupled_prob_var_limit/seed2025/col-r_mcar_1_0/result_0_2.csv",
    "../event_missing/coupled_prob_var_limit/seed2025/col-r_mcar_1_0/result_0_3.csv",
    "../event_missing/coupled_prob_var_limit/seed2025/col-r_mcar_1_0/result_0_4.csv",
    "../event_missing/coupled_prob_var_limit/seed2025/col-r_mcar_1_0/result_0_5.csv",

    "../event_missing/coupled/seed2025/col-s_mcar_1_0/result.csv",
    "../event_missing/coupled_prob_var_limit/seed2025/col-s_mcar_1_0/result_0_1.csv",
    "../event_missing/coupled_prob_var_limit/seed2025/col-s_mcar_1_0/result_0_2.csv",
    "../event_missing/coupled_prob_var_limit/seed2025/col-s_mcar_1_0/result_0_3.csv",
    "../event_missing/coupled_prob_var_limit/seed2025/col-s_mcar_1_0/result_0_4.csv",
    "../event_missing/coupled_prob_var_limit/seed2025/col-s_mcar_1_0/result_0_5.csv",

    "../event_missing/coupled/seed2099/col-p_mcar_1_0/result.csv",
    "../event_missing/coupled_prob_var_limit/seed2099/col-p_mcar_1_0/result_0_1.csv",
    "../event_missing/coupled_prob_var_limit/seed2099/col-p_mcar_1_0/result_0_2.csv",
    "../event_missing/coupled_prob_var_limit/seed2099/col-p_mcar_1_0/result_0_3.csv",
    "../event_missing/coupled_prob_var_limit/seed2099/col-p_mcar_1_0/result_0_4.csv",
    "../event_missing/coupled_prob_var_limit/seed2099/col-p_mcar_1_0/result_0_5.csv",

    "../event_missing/coupled/seed2099/col-r_mcar_1_0/result.csv",
    "../event_missing/coupled_prob_var_limit/seed2099/col-r_mcar_1_0/result_0_1.csv",
    "../event_missing/coupled_prob_var_limit/seed2099/col-r_mcar_1_0/result_0_2.csv",
    "../event_missing/coupled_prob_var_limit/seed2099/col-r_mcar_1_0/result_0_3.csv",
    "../event_missing/coupled_prob_var_limit/seed2099/col-r_mcar_1_0/result_0_4.csv",
    "../event_missing/coupled_prob_var_limit/seed2099/col-r_mcar_1_0/result_0_5.csv",

    "../event_missing/coupled/seed2099/col-s_mcar_1_0/result.csv",
    "../event_missing/coupled_prob_var_limit/seed2099/col-s_mcar_1_0/result_0_1.csv",
    "../event_missing/coupled_prob_var_limit/seed2099/col-s_mcar_1_0/result_0_2.csv",
    "../event_missing/coupled_prob_var_limit/seed2099/col-s_mcar_1_0/result_0_3.csv",
    "../event_missing/coupled_prob_var_limit/seed2099/col-s_mcar_1_0/result_0_4.csv",
    "../event_missing/coupled_prob_var_limit/seed2099/col-s_mcar_1_0/result_0_5.csv",

    "../periodic/coupled/seed2025/T10_keep0_5/result.csv",
    "../periodic/coupled_prob_var_limit/seed2025/T10_keep0_5/result_0_1.csv",
    "../periodic/coupled_prob_var_limit/seed2025/T10_keep0_5/result_0_2.csv",
    "../periodic/coupled_prob_var_limit/seed2025/T10_keep0_5/result_0_3.csv",
    "../periodic/coupled_prob_var_limit/seed2025/T10_keep0_5/result_0_4.csv",
    "../periodic/coupled_prob_var_limit/seed2025/T10_keep0_5/result_0_5.csv",

    "../periodic/coupled/seed2025/T10_keep0_7/result.csv",
    "../periodic/coupled_prob_var_limit/seed2025/T10_keep0_7/result_0_1.csv",
    "../periodic/coupled_prob_var_limit/seed2025/T10_keep0_7/result_0_2.csv",
    "../periodic/coupled_prob_var_limit/seed2025/T10_keep0_7/result_0_3.csv",
    "../periodic/coupled_prob_var_limit/seed2025/T10_keep0_7/result_0_4.csv",
    "../periodic/coupled_prob_var_limit/seed2025/T10_keep0_7/result_0_5.csv",

    "../periodic/coupled/seed2025/T20_keep0_5/result.csv",
    "../periodic/coupled_prob_var_limit/seed2025/T20_keep0_5/result_0_1.csv",
    "../periodic/coupled_prob_var_limit/seed2025/T20_keep0_5/result_0_2.csv",
    "../periodic/coupled_prob_var_limit/seed2025/T20_keep0_5/result_0_3.csv",
    "../periodic/coupled_prob_var_limit/seed2025/T20_keep0_5/result_0_4.csv",
    "../periodic/coupled_prob_var_limit/seed2025/T20_keep0_5/result_0_5.csv",

    "../periodic/coupled/seed2025/T20_keep0_7/result.csv",
    "../periodic/coupled_prob_var_limit/seed2025/T20_keep0_7/result_0_1.csv",
    "../periodic/coupled_prob_var_limit/seed2025/T20_keep0_7/result_0_2.csv",
    "../periodic/coupled_prob_var_limit/seed2025/T20_keep0_7/result_0_3.csv",
    "../periodic/coupled_prob_var_limit/seed2025/T20_keep0_7/result_0_4.csv",
    "../periodic/coupled_prob_var_limit/seed2025/T20_keep0_7/result_0_5.csv",

    "../periodic/coupled/seed2099/T10_keep0_5/result.csv",
    "../periodic/coupled_prob_var_limit/seed2099/T10_keep0_5/result_0_1.csv",
    "../periodic/coupled_prob_var_limit/seed2099/T10_keep0_5/result_0_2.csv",
    "../periodic/coupled_prob_var_limit/seed2099/T10_keep0_5/result_0_3.csv",
    "../periodic/coupled_prob_var_limit/seed2099/T10_keep0_5/result_0_4.csv",
    "../periodic/coupled_prob_var_limit/seed2099/T10_keep0_5/result_0_5.csv",

    "../periodic/coupled/seed2099/T10_keep0_7/result.csv",
    "../periodic/coupled_prob_var_limit/seed2099/T10_keep0_7/result_0_1.csv",
    "../periodic/coupled_prob_var_limit/seed2099/T10_keep0_7/result_0_2.csv",
    "../periodic/coupled_prob_var_limit/seed2099/T10_keep0_7/result_0_3.csv",
    "../periodic/coupled_prob_var_limit/seed2099/T10_keep0_7/result_0_4.csv",
    "../periodic/coupled_prob_var_limit/seed2099/T10_keep0_7/result_0_5.csv",

    "../periodic/coupled/seed2099/T20_keep0_5/result.csv",
    "../periodic/coupled_prob_var_limit/seed2099/T20_keep0_5/result_0_1.csv",
    "../periodic/coupled_prob_var_limit/seed2099/T20_keep0_5/result_0_2.csv",
    "../periodic/coupled_prob_var_limit/seed2099/T20_keep0_5/result_0_3.csv",
    "../periodic/coupled_prob_var_limit/seed2099/T20_keep0_5/result_0_4.csv",
    "../periodic/coupled_prob_var_limit/seed2099/T20_keep0_5/result_0_5.csv",

    "../periodic/coupled/seed2099/T20_keep0_7/result.csv",
    "../periodic/coupled_prob_var_limit/seed2099/T20_keep0_7/result_0_1.csv",
    "../periodic/coupled_prob_var_limit/seed2099/T20_keep0_7/result_0_2.csv",
    "../periodic/coupled_prob_var_limit/seed2099/T20_keep0_7/result_0_3.csv",
    "../periodic/coupled_prob_var_limit/seed2099/T20_keep0_7/result_0_4.csv",
    "../periodic/coupled_prob_var_limit/seed2099/T20_keep0_7/result_0_5.csv",

    "../proportional_missing/coupled/seed2025/iid_mr_0_1/result.csv",
    "../proportional_missing/coupled_prob_var_limit/seed2025/iid_mr_0_1/result_0_1.csv",
    "../proportional_missing/coupled_prob_var_limit/seed2025/iid_mr_0_1/result_0_2.csv",
    "../proportional_missing/coupled_prob_var_limit/seed2025/iid_mr_0_1/result_0_3.csv",
    "../proportional_missing/coupled_prob_var_limit/seed2025/iid_mr_0_1/result_0_4.csv",
    "../proportional_missing/coupled_prob_var_limit/seed2025/iid_mr_0_1/result_0_5.csv",

    "../proportional_missing/coupled/seed2025/iid_mr_0_2/result.csv",
    "../proportional_missing/coupled_prob_var_limit/seed2025/iid_mr_0_2/result_0_1.csv",
    "../proportional_missing/coupled_prob_var_limit/seed2025/iid_mr_0_2/result_0_2.csv",
    "../proportional_missing/coupled_prob_var_limit/seed2025/iid_mr_0_2/result_0_3.csv",
    "../proportional_missing/coupled_prob_var_limit/seed2025/iid_mr_0_2/result_0_4.csv",
    "../proportional_missing/coupled_prob_var_limit/seed2025/iid_mr_0_2/result_0_5.csv",

    "../proportional_missing/coupled/seed2025/iid_mr_0_05/result.csv",
    "../proportional_missing/coupled_prob_var_limit/seed2025/iid_mr_0_05/result_0_1.csv",
    "../proportional_missing/coupled_prob_var_limit/seed2025/iid_mr_0_05/result_0_2.csv",
    "../proportional_missing/coupled_prob_var_limit/seed2025/iid_mr_0_05/result_0_3.csv",
    "../proportional_missing/coupled_prob_var_limit/seed2025/iid_mr_0_05/result_0_4.csv",
    "../proportional_missing/coupled_prob_var_limit/seed2025/iid_mr_0_05/result_0_5.csv",

    "../proportional_missing/coupled/seed2099/iid_mr_0_1/result.csv",
    "../proportional_missing/coupled_prob_var_limit/seed2099/iid_mr_0_1/result_0_1.csv",
    "../proportional_missing/coupled_prob_var_limit/seed2099/iid_mr_0_1/result_0_2.csv",
    "../proportional_missing/coupled_prob_var_limit/seed2099/iid_mr_0_1/result_0_3.csv",
    "../proportional_missing/coupled_prob_var_limit/seed2099/iid_mr_0_1/result_0_4.csv",
    "../proportional_missing/coupled_prob_var_limit/seed2099/iid_mr_0_1/result_0_5.csv",

    "../proportional_missing/coupled/seed2099/iid_mr_0_2/result.csv",
    "../proportional_missing/coupled_prob_var_limit/seed2099/iid_mr_0_2/result_0_1.csv",
    "../proportional_missing/coupled_prob_var_limit/seed2099/iid_mr_0_2/result_0_2.csv",
    "../proportional_missing/coupled_prob_var_limit/seed2099/iid_mr_0_2/result_0_3.csv",
    "../proportional_missing/coupled_prob_var_limit/seed2099/iid_mr_0_2/result_0_4.csv",
    "../proportional_missing/coupled_prob_var_limit/seed2099/iid_mr_0_2/result_0_5.csv",

    "../proportional_missing/coupled/seed2099/iid_mr_0_05/result.csv",
    "../proportional_missing/coupled_prob_var_limit/seed2099/iid_mr_0_05/result_0_1.csv",
    "../proportional_missing/coupled_prob_var_limit/seed2099/iid_mr_0_05/result_0_2.csv",
    "../proportional_missing/coupled_prob_var_limit/seed2099/iid_mr_0_05/result_0_3.csv",
    "../proportional_missing/coupled_prob_var_limit/seed2099/iid_mr_0_05/result_0_4.csv",
    "../proportional_missing/coupled_prob_var_limit/seed2099/iid_mr_0_05/result_0_5.csv",
]

TRUTH_FILE = "coupled_truth_labels.csv"
NUM_PROPERTIES = 4

print("Loading truth from:", TRUTH_FILE)
truth = pd.read_csv(TRUTH_FILE)
assert "time" in truth.columns

for pred_path_str in PRED_FILES:
    pred_path = Path(pred_path_str)
    print("\n======================================")
    print("Loading predictions from:", pred_path)

    pred = pd.read_csv(pred_path)
    assert "time" in pred.columns

    merged = pred.merge(truth, on="time", how="inner")
    print(f"Merged rows: {len(merged)}")

    metrics = {}
    tp_times = {}  # property -> list of time values where TP occurs

    for i in range(1, NUM_PROPERTIES + 1):
        pred_col = f"pred_P{i}"
        truth_col = f"viol_C{i}"

        if pred_col not in merged.columns:
            raise KeyError(f"Missing column in predictions: {pred_col}")
        if truth_col not in merged.columns:
            raise KeyError(f"Missing column in truth: {truth_col}")

        # Clean/parse
        p = merged[pred_col].astype(str).str.strip().str.replace('"', '', regex=False).astype(int)
        t = merged[truth_col].astype(int)

        TP_mask = (p == 1) & (t == 1)
        FP_mask = (p == 1) & (t == 0)
        FN_mask = (p == 0) & (t == 1)
        TN_mask = (p == 0) & (t == 0)

        TP = int(TP_mask.sum())
        FP = int(FP_mask.sum())
        FN = int(FN_mask.sum())
        TN = int(TN_mask.sum())

        denom = TP + FP + FN + TN
        precision = TP / (TP + FP + 1e-9)
        recall    = TP / (TP + FN + 1e-9)
        f1        = 2 * precision * recall / (precision + recall + 1e-9)
        iou       = TP / (TP + FP + FN + 1e-9)
        fp_pct    = FP / denom if denom > 0 else 0.0

        prop = f"P{i}"
        metrics[prop] = {
            "TP": TP,
            "FP": FP,
            "FN": FN,
            "TN": TN,
            "Precision": round(float(precision), 6),
            "Recall": round(float(recall), 6),
            "F1": round(float(f1), 6),
            "IoU": round(float(iou), 6),
            "FP_pct": round(float(fp_pct), 6),
            "Denom": int(denom),
        }

        # Store TP timestamps for overlap checks later
        tp_times[prop] = merged.loc[TP_mask, "time"].tolist()

    # Totals (same style as before: sum counts across properties)
    total_TP = sum(metrics[f"P{i}"]["TP"] for i in range(1, NUM_PROPERTIES + 1))
    total_FP = sum(metrics[f"P{i}"]["FP"] for i in range(1, NUM_PROPERTIES + 1))
    total_FN = sum(metrics[f"P{i}"]["FN"] for i in range(1, NUM_PROPERTIES + 1))
    total_TN = sum(metrics[f"P{i}"]["TN"] for i in range(1, NUM_PROPERTIES + 1))

    total_precision = total_TP / (total_TP + total_FP) if (total_TP + total_FP) > 0 else 0.0
    total_recall    = total_TP / (total_TP + total_FN) if (total_TP + total_FN) > 0 else 0.0
    total_f1        = (2 * total_precision * total_recall / (total_precision + total_recall)) if (total_precision + total_recall) > 0 else 0.0
    total_iou       = total_TP / (total_TP + total_FP + total_FN) if (total_TP + total_FP + total_FN) > 0 else 0.0

    denom_total = total_TP + total_FP + total_FN + total_TN
    total_fp_pct = total_FP / denom_total if denom_total > 0 else 0.0

    metrics["Total"] = {
        "TP": int(total_TP),
        "FP": int(total_FP),
        "FN": int(total_FN),
        "TN": int(total_TN),
        "Precision": round(total_precision, 6),
        "Recall": round(total_recall, 6),
        "F1": round(total_f1, 6),
        "IoU": round(total_iou, 6),
        "FP_pct": round(float(total_fp_pct), 6),
        "Denom": int(denom_total),
    }

    # For overlap on Total: define TP-times as union across P1..P4
    total_tp_union = set()
    for i in range(1, NUM_PROPERTIES + 1):
        total_tp_union.update(tp_times[f"P{i}"])
    tp_times["Total"] = sorted(total_tp_union)

    # Write metrics CSVif pred_path.name == "result.csv":
    if pred_path.name == "result.csv":
        out_metrics = pred_path.parent / "results_metrics.csv"
    else:
        out_metrics = pred_path.parent / f"{pred_path.stem}_metrics.csv"

    with open(out_metrics, "w", newline="") as f:
        writer = csv.writer(f)
        writer.writerow(["Property", "TP", "FP", "FN", "TN", "Precision", "Recall", "F1", "IoU", "FP_pct", "Denom"])
        for prop in ["P1", "P2", "P3", "P4", "Total"]:
            m = metrics[prop]
            writer.writerow([prop, m["TP"], m["FP"], m["FN"], m["TN"],
                             m["Precision"], m["Recall"], m["F1"], m["IoU"],
                             m["FP_pct"], m["Denom"]])

    print("Saved metrics CSV as:", out_metrics)

    # Write TP-times CSV (one row per TP timestamp)
    out_tps = pred_path.parent / f"{pred_path.stem}_tp_times.csv"
    tp_rows = []
    for prop in ["P1", "P2", "P3", "P4", "Total"]:
        for t in tp_times[prop]:
            tp_rows.append([prop, t])

    with open(out_tps, "w", newline="") as f:
        writer = csv.writer(f)
        writer.writerow(["Property", "time"])
        writer.writerows(tp_rows)

    print("Saved TP-times CSV as:", out_tps)