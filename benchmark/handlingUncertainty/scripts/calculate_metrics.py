import pandas as pd
import csv
from pathlib import Path

# Put as many prediction files here as you want
PRED_FILES = [
"../blocking_missing/coupled_prob_var_limit/seed2025/burst_mr_0_1_L_3/result_0_1.csv",
"../blocking_missing/coupled_prob_var_limit/seed2025/burst_mr_0_1_L_3/result_0_2.csv",
"../blocking_missing/coupled_prob_var_limit/seed2025/burst_mr_0_1_L_3/result_0_3.csv",
"../blocking_missing/coupled_prob_var_limit/seed2025/burst_mr_0_1_L_3/result_0_4.csv",
"../blocking_missing/coupled_prob_var_limit/seed2025/burst_mr_0_1_L_3/result_0_5.csv",
"../blocking_missing/coupled_prob_var_limit/seed2025/burst_mr_0_1_L_5/result_0_1.csv",
"../blocking_missing/coupled_prob_var_limit/seed2025/burst_mr_0_1_L_5/result_0_2.csv",
"../blocking_missing/coupled_prob_var_limit/seed2025/burst_mr_0_1_L_5/result_0_3.csv",
"../blocking_missing/coupled_prob_var_limit/seed2025/burst_mr_0_1_L_5/result_0_4.csv",
"../blocking_missing/coupled_prob_var_limit/seed2025/burst_mr_0_1_L_5/result_0_5.csv",
"../blocking_missing/coupled_prob_var_limit/seed2025/burst_mr_0_1_L_10/result_0_1.csv",
"../blocking_missing/coupled_prob_var_limit/seed2025/burst_mr_0_1_L_10/result_0_2.csv",
"../blocking_missing/coupled_prob_var_limit/seed2025/burst_mr_0_1_L_10/result_0_3.csv",
"../blocking_missing/coupled_prob_var_limit/seed2025/burst_mr_0_1_L_10/result_0_4.csv",
"../blocking_missing/coupled_prob_var_limit/seed2025/burst_mr_0_1_L_10/result_0_5.csv",
"../blocking_missing/coupled_prob_var_limit/seed2025/burst_mr_0_2_L_3/result_0_1.csv",
"../blocking_missing/coupled_prob_var_limit/seed2025/burst_mr_0_2_L_3/result_0_2.csv",
"../blocking_missing/coupled_prob_var_limit/seed2025/burst_mr_0_2_L_3/result_0_3.csv",
"../blocking_missing/coupled_prob_var_limit/seed2025/burst_mr_0_2_L_3/result_0_4.csv",
"../blocking_missing/coupled_prob_var_limit/seed2025/burst_mr_0_2_L_3/result_0_5.csv",
"../blocking_missing/coupled_prob_var_limit/seed2025/burst_mr_0_2_L_5/result_0_1.csv",
"../blocking_missing/coupled_prob_var_limit/seed2025/burst_mr_0_2_L_5/result_0_2.csv",
"../blocking_missing/coupled_prob_var_limit/seed2025/burst_mr_0_2_L_5/result_0_3.csv",
"../blocking_missing/coupled_prob_var_limit/seed2025/burst_mr_0_2_L_5/result_0_4.csv",
"../blocking_missing/coupled_prob_var_limit/seed2025/burst_mr_0_2_L_5/result_0_5.csv",
"../blocking_missing/coupled_prob_var_limit/seed2025/burst_mr_0_2_L_10/result_0_1.csv",
"../blocking_missing/coupled_prob_var_limit/seed2025/burst_mr_0_2_L_10/result_0_2.csv",
"../blocking_missing/coupled_prob_var_limit/seed2025/burst_mr_0_2_L_10/result_0_3.csv",
"../blocking_missing/coupled_prob_var_limit/seed2025/burst_mr_0_2_L_10/result_0_4.csv",
"../blocking_missing/coupled_prob_var_limit/seed2025/burst_mr_0_2_L_10/result_0_5.csv",
"../blocking_missing/coupled_prob_var_limit/seed2099/burst_mr_0_1_L_3/result_0_1.csv",
"../blocking_missing/coupled_prob_var_limit/seed2099/burst_mr_0_1_L_3/result_0_2.csv",
"../blocking_missing/coupled_prob_var_limit/seed2099/burst_mr_0_1_L_3/result_0_3.csv",
"../blocking_missing/coupled_prob_var_limit/seed2099/burst_mr_0_1_L_3/result_0_4.csv",
"../blocking_missing/coupled_prob_var_limit/seed2099/burst_mr_0_1_L_3/result_0_5.csv",
"../blocking_missing/coupled_prob_var_limit/seed2099/burst_mr_0_1_L_5/result_0_1.csv",
"../blocking_missing/coupled_prob_var_limit/seed2099/burst_mr_0_1_L_5/result_0_2.csv",
"../blocking_missing/coupled_prob_var_limit/seed2099/burst_mr_0_1_L_5/result_0_3.csv",
"../blocking_missing/coupled_prob_var_limit/seed2099/burst_mr_0_1_L_5/result_0_4.csv",
"../blocking_missing/coupled_prob_var_limit/seed2099/burst_mr_0_1_L_5/result_0_5.csv",
"../blocking_missing/coupled_prob_var_limit/seed2099/burst_mr_0_1_L_10/result_0_1.csv",
"../blocking_missing/coupled_prob_var_limit/seed2099/burst_mr_0_1_L_10/result_0_2.csv",
"../blocking_missing/coupled_prob_var_limit/seed2099/burst_mr_0_1_L_10/result_0_3.csv",
"../blocking_missing/coupled_prob_var_limit/seed2099/burst_mr_0_1_L_10/result_0_4.csv",
"../blocking_missing/coupled_prob_var_limit/seed2099/burst_mr_0_1_L_10/result_0_5.csv",
"../blocking_missing/coupled_prob_var_limit/seed2099/burst_mr_0_2_L_3/result_0_1.csv",
"../blocking_missing/coupled_prob_var_limit/seed2099/burst_mr_0_2_L_3/result_0_2.csv",
"../blocking_missing/coupled_prob_var_limit/seed2099/burst_mr_0_2_L_3/result_0_3.csv",
"../blocking_missing/coupled_prob_var_limit/seed2099/burst_mr_0_2_L_3/result_0_4.csv",
"../blocking_missing/coupled_prob_var_limit/seed2099/burst_mr_0_2_L_3/result_0_5.csv",
"../blocking_missing/coupled_prob_var_limit/seed2099/burst_mr_0_2_L_5/result_0_1.csv",
"../blocking_missing/coupled_prob_var_limit/seed2099/burst_mr_0_2_L_5/result_0_2.csv",
"../blocking_missing/coupled_prob_var_limit/seed2099/burst_mr_0_2_L_5/result_0_3.csv",
"../blocking_missing/coupled_prob_var_limit/seed2099/burst_mr_0_2_L_5/result_0_4.csv",
"../blocking_missing/coupled_prob_var_limit/seed2099/burst_mr_0_2_L_5/result_0_5.csv",
"../blocking_missing/coupled_prob_var_limit/seed2099/burst_mr_0_2_L_10/result_0_1.csv",
"../blocking_missing/coupled_prob_var_limit/seed2099/burst_mr_0_2_L_10/result_0_2.csv",
"../blocking_missing/coupled_prob_var_limit/seed2099/burst_mr_0_2_L_10/result_0_3.csv",
"../blocking_missing/coupled_prob_var_limit/seed2099/burst_mr_0_2_L_10/result_0_4.csv",
"../blocking_missing/coupled_prob_var_limit/seed2099/burst_mr_0_2_L_10/result_0_5.csv",
"../event_missing/coupled_prob_var_limit/seed2025/col-p_mcar_1_0/result_0_1.csv",
"../event_missing/coupled_prob_var_limit/seed2025/col-p_mcar_1_0/result_0_2.csv",
"../event_missing/coupled_prob_var_limit/seed2025/col-p_mcar_1_0/result_0_3.csv",
"../event_missing/coupled_prob_var_limit/seed2025/col-p_mcar_1_0/result_0_4.csv",
"../event_missing/coupled_prob_var_limit/seed2025/col-p_mcar_1_0/result_0_5.csv",
"../event_missing/coupled_prob_var_limit/seed2025/col-r_mcar_1_0/result_0_1.csv",
"../event_missing/coupled_prob_var_limit/seed2025/col-r_mcar_1_0/result_0_2.csv",
"../event_missing/coupled_prob_var_limit/seed2025/col-r_mcar_1_0/result_0_3.csv",
"../event_missing/coupled_prob_var_limit/seed2025/col-r_mcar_1_0/result_0_4.csv",
"../event_missing/coupled_prob_var_limit/seed2025/col-r_mcar_1_0/result_0_5.csv",
"../event_missing/coupled_prob_var_limit/seed2025/col-s_mcar_1_0/result_0_1.csv",
"../event_missing/coupled_prob_var_limit/seed2025/col-s_mcar_1_0/result_0_2.csv",
"../event_missing/coupled_prob_var_limit/seed2025/col-s_mcar_1_0/result_0_3.csv",
"../event_missing/coupled_prob_var_limit/seed2025/col-s_mcar_1_0/result_0_4.csv",
"../event_missing/coupled_prob_var_limit/seed2025/col-s_mcar_1_0/result_0_5.csv",
"../event_missing/coupled_prob_var_limit/seed2099/col-p_mcar_1_0/result_0_1.csv",
"../event_missing/coupled_prob_var_limit/seed2099/col-p_mcar_1_0/result_0_2.csv",
"../event_missing/coupled_prob_var_limit/seed2099/col-p_mcar_1_0/result_0_3.csv",
"../event_missing/coupled_prob_var_limit/seed2099/col-p_mcar_1_0/result_0_4.csv",
"../event_missing/coupled_prob_var_limit/seed2099/col-p_mcar_1_0/result_0_5.csv",
"../event_missing/coupled_prob_var_limit/seed2099/col-r_mcar_1_0/result_0_1.csv",
"../event_missing/coupled_prob_var_limit/seed2099/col-r_mcar_1_0/result_0_2.csv",
"../event_missing/coupled_prob_var_limit/seed2099/col-r_mcar_1_0/result_0_3.csv",
"../event_missing/coupled_prob_var_limit/seed2099/col-r_mcar_1_0/result_0_4.csv",
"../event_missing/coupled_prob_var_limit/seed2099/col-r_mcar_1_0/result_0_5.csv",
"../event_missing/coupled_prob_var_limit/seed2099/col-s_mcar_1_0/result_0_1.csv",
"../event_missing/coupled_prob_var_limit/seed2099/col-s_mcar_1_0/result_0_2.csv",
"../event_missing/coupled_prob_var_limit/seed2099/col-s_mcar_1_0/result_0_3.csv",
"../event_missing/coupled_prob_var_limit/seed2099/col-s_mcar_1_0/result_0_4.csv",
"../event_missing/coupled_prob_var_limit/seed2099/col-s_mcar_1_0/result_0_5.csv",
"../periodic/coupled_prob_var_limit/seed2025/T10_keep0_5/result_0_1.csv",
"../periodic/coupled_prob_var_limit/seed2025/T10_keep0_5/result_0_2.csv",
"../periodic/coupled_prob_var_limit/seed2025/T10_keep0_5/result_0_3.csv",
"../periodic/coupled_prob_var_limit/seed2025/T10_keep0_5/result_0_4.csv",
"../periodic/coupled_prob_var_limit/seed2025/T10_keep0_5/result_0_5.csv",
"../periodic/coupled_prob_var_limit/seed2025/T10_keep0_7/result_0_1.csv",
"../periodic/coupled_prob_var_limit/seed2025/T10_keep0_7/result_0_2.csv",
"../periodic/coupled_prob_var_limit/seed2025/T10_keep0_7/result_0_3.csv",
"../periodic/coupled_prob_var_limit/seed2025/T10_keep0_7/result_0_4.csv",
"../periodic/coupled_prob_var_limit/seed2025/T10_keep0_7/result_0_5.csv",
"../periodic/coupled_prob_var_limit/seed2025/T20_keep0_5/result_0_1.csv",
"../periodic/coupled_prob_var_limit/seed2025/T20_keep0_5/result_0_2.csv",
"../periodic/coupled_prob_var_limit/seed2025/T20_keep0_5/result_0_3.csv",
"../periodic/coupled_prob_var_limit/seed2025/T20_keep0_5/result_0_4.csv",
"../periodic/coupled_prob_var_limit/seed2025/T20_keep0_5/result_0_5.csv",
"../periodic/coupled_prob_var_limit/seed2025/T20_keep0_7/result_0_1.csv",
"../periodic/coupled_prob_var_limit/seed2025/T20_keep0_7/result_0_2.csv",
"../periodic/coupled_prob_var_limit/seed2025/T20_keep0_7/result_0_3.csv",
"../periodic/coupled_prob_var_limit/seed2025/T20_keep0_7/result_0_4.csv",
"../periodic/coupled_prob_var_limit/seed2025/T20_keep0_7/result_0_5.csv",
"../periodic/coupled_prob_var_limit/seed2099/T10_keep0_5/result_0_1.csv",
"../periodic/coupled_prob_var_limit/seed2099/T10_keep0_5/result_0_2.csv",
"../periodic/coupled_prob_var_limit/seed2099/T10_keep0_5/result_0_3.csv",
"../periodic/coupled_prob_var_limit/seed2099/T10_keep0_5/result_0_4.csv",
"../periodic/coupled_prob_var_limit/seed2099/T10_keep0_5/result_0_5.csv",
"../periodic/coupled_prob_var_limit/seed2099/T10_keep0_7/result_0_1.csv",
"../periodic/coupled_prob_var_limit/seed2099/T10_keep0_7/result_0_2.csv",
"../periodic/coupled_prob_var_limit/seed2099/T10_keep0_7/result_0_3.csv",
"../periodic/coupled_prob_var_limit/seed2099/T10_keep0_7/result_0_4.csv",
"../periodic/coupled_prob_var_limit/seed2099/T10_keep0_7/result_0_5.csv",
"../periodic/coupled_prob_var_limit/seed2099/T20_keep0_5/result_0_1.csv",
"../periodic/coupled_prob_var_limit/seed2099/T20_keep0_5/result_0_2.csv",
"../periodic/coupled_prob_var_limit/seed2099/T20_keep0_5/result_0_3.csv",
"../periodic/coupled_prob_var_limit/seed2099/T20_keep0_5/result_0_4.csv",
"../periodic/coupled_prob_var_limit/seed2099/T20_keep0_5/result_0_5.csv",
"../periodic/coupled_prob_var_limit/seed2099/T20_keep0_7/result_0_1.csv",
"../periodic/coupled_prob_var_limit/seed2099/T20_keep0_7/result_0_2.csv",
"../periodic/coupled_prob_var_limit/seed2099/T20_keep0_7/result_0_3.csv",
"../periodic/coupled_prob_var_limit/seed2099/T20_keep0_7/result_0_4.csv",
"../periodic/coupled_prob_var_limit/seed2099/T20_keep0_7/result_0_5.csv",
"../proportional_missing/coupled_prob_var_limit/seed2025/iid_mr_0_1/result_0_1.csv",
"../proportional_missing/coupled_prob_var_limit/seed2025/iid_mr_0_1/result_0_2.csv",
"../proportional_missing/coupled_prob_var_limit/seed2025/iid_mr_0_1/result_0_3.csv",
"../proportional_missing/coupled_prob_var_limit/seed2025/iid_mr_0_1/result_0_4.csv",
"../proportional_missing/coupled_prob_var_limit/seed2025/iid_mr_0_1/result_0_5.csv",
"../proportional_missing/coupled_prob_var_limit/seed2025/iid_mr_0_2/result_0_1.csv",
"../proportional_missing/coupled_prob_var_limit/seed2025/iid_mr_0_2/result_0_2.csv",
"../proportional_missing/coupled_prob_var_limit/seed2025/iid_mr_0_2/result_0_3.csv",
"../proportional_missing/coupled_prob_var_limit/seed2025/iid_mr_0_2/result_0_4.csv",
"../proportional_missing/coupled_prob_var_limit/seed2025/iid_mr_0_2/result_0_5.csv",
"../proportional_missing/coupled_prob_var_limit/seed2025/iid_mr_0_05/result_0_1.csv",
"../proportional_missing/coupled_prob_var_limit/seed2025/iid_mr_0_05/result_0_2.csv",
"../proportional_missing/coupled_prob_var_limit/seed2025/iid_mr_0_05/result_0_3.csv",
"../proportional_missing/coupled_prob_var_limit/seed2025/iid_mr_0_05/result_0_4.csv",
"../proportional_missing/coupled_prob_var_limit/seed2025/iid_mr_0_05/result_0_5.csv",
"../proportional_missing/coupled_prob_var_limit/seed2099/iid_mr_0_1/result_0_1.csv",
"../proportional_missing/coupled_prob_var_limit/seed2099/iid_mr_0_1/result_0_2.csv",
"../proportional_missing/coupled_prob_var_limit/seed2099/iid_mr_0_1/result_0_3.csv",
"../proportional_missing/coupled_prob_var_limit/seed2099/iid_mr_0_1/result_0_4.csv",
"../proportional_missing/coupled_prob_var_limit/seed2099/iid_mr_0_1/result_0_5.csv",
"../proportional_missing/coupled_prob_var_limit/seed2099/iid_mr_0_2/result_0_1.csv",
"../proportional_missing/coupled_prob_var_limit/seed2099/iid_mr_0_2/result_0_2.csv",
"../proportional_missing/coupled_prob_var_limit/seed2099/iid_mr_0_2/result_0_3.csv",
"../proportional_missing/coupled_prob_var_limit/seed2099/iid_mr_0_2/result_0_4.csv",
"../proportional_missing/coupled_prob_var_limit/seed2099/iid_mr_0_2/result_0_5.csv",
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

    for i in range(1, NUM_PROPERTIES + 1):
        pred_col = f"pred_P{i}"
        truth_col = f"viol_C{i}"

        if pred_col not in merged.columns:
            raise KeyError(f"Missing column in predictions: {pred_col}")
        if truth_col not in merged.columns:
            raise KeyError(f"Missing column in truth: {truth_col}")

        p = merged[pred_col]
        t = merged[truth_col]

        # Keep your original cleaning logic
        p = p.astype(str).str.strip().str.replace('"', '', regex=False)
        p = p.astype(int)
        t = t.astype(int)

        TP = ((p == 1) & (t == 1)).sum()
        FP = ((p == 1) & (t == 0)).sum()
        FN = ((p == 0) & (t == 1)).sum()
        TN = ((p == 0) & (t == 0)).sum()

        precision = TP / (TP + FP + 1e-9)
        recall    = TP / (TP + FN + 1e-9)
        f1        = 2 * precision * recall / (precision + recall + 1e-9)
        iou       = TP / (TP + FP + FN + 1e-9)

        metrics[f"P{i}"] = {
            "TP": int(TP),
            "FP": int(FP),
            "FN": int(FN),
            "TN": int(TN),
            "Precision": round(float(precision), 6),
            "Recall": round(float(recall), 6),
            "F1": round(float(f1), 6),
            "IoU": round(float(iou), 6),
        }

    output_rows = []
    total_TP = total_FP = total_FN = total_TN = 0

    for prop, m in metrics.items():
        output_rows.append([
            prop,
            m["TP"], m["FP"], m["FN"], m["TN"],
            m["Precision"], m["Recall"], m["F1"], m["IoU"],
        ])
        total_TP += m["TP"]
        total_FP += m["FP"]
        total_FN += m["FN"]
        total_TN += m["TN"]

    total_precision = total_TP / (total_TP + total_FP) if (total_TP + total_FP) > 0 else 0.0
    total_recall    = total_TP / (total_TP + total_FN) if (total_TP + total_FN) > 0 else 0.0
    total_f1        = (2 * total_precision * total_recall / (total_precision + total_recall)) if (total_precision + total_recall) > 0 else 0.0
    total_iou       = total_TP / (total_TP + total_FP + total_FN) if (total_TP + total_FP + total_FN) > 0 else 0.0

    output_rows.append([
        "Total",
        int(total_TP), int(total_FP), int(total_FN), int(total_TN),
        round(total_precision, 6),
        round(total_recall, 6),
        round(total_f1, 6),
        round(total_iou, 6),
    ])

    # (2) Write output next to the prediction file
    out_path = pred_path.parent / f"{pred_path.stem}_metrics.csv"
    with open(out_path, "w", newline="") as f:
        writer = csv.writer(f)
        writer.writerow(["Property", "TP", "FP", "FN", "TN", "Precision", "Recall", "F1", "IoU"])
        writer.writerows(output_rows)

    print("Saved CSV as:", out_path)