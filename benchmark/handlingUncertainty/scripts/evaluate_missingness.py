import pandas as pd
import csv

PRED_FILE = "../blocking_missing/coupled/seed2099/burst_mr_0_2_L_10/result.csv"
TRUTH_FILE = "coupled_truth_labels.csv"
NUM_PROPERTIES = 4

print("Loading predictions from:", PRED_FILE)
pred = pd.read_csv(PRED_FILE)

print("Loading truth from:", TRUTH_FILE)
truth = pd.read_csv(TRUTH_FILE)

assert "time" in pred.columns
assert "time" in truth.columns

merged = pred.merge(truth, on="time", how="inner")
print(f"Merged rows: {len(merged)}")

metrics = {}

for i in range(1, NUM_PROPERTIES + 1):

    pred_col = f"pred_P{i}"
    truth_col = f"viol_C{i}"

    p = merged[pred_col]
    t = merged[truth_col]

    p = p.str.strip().str.replace('"', '')
    p = p.astype(int)
    t = t.astype(int)

    TP = ((p == 1) & (t == 1)).sum()
    FP = ((p == 1) & (t == 0)).sum()
    FN = ((p == 0) & (t == 1)).sum()
    TN = ((p == 0) & (t == 0)).sum()

    precision = TP / (TP + FP + 1e-9)
    recall    = TP / (TP + FN + 1e-9)
    f1        = 2 * precision * recall / (precision + recall + 1e-9)
    IoU       = TP / (TP + FP + FN + 1e-9)

    metrics[f"P{i}"] = {
        "TP": TP,
        "FP": FP,
        "FN": FN,
        "TN": TN,
        "Precision": round(precision, 4),
        "Recall": round(recall, 4),
        "F1": round(f1, 4),
        "IoU": round(IoU, 4)
    }

output_rows = []
total_TP = total_FP = total_FN = total_TN = 0

for prop, m in metrics.items():
    row = [
        prop,
        m["TP"],
        m["FP"],
        m["FN"],
        m["TN"],
        round(m["Precision"], 6),
        round(m["Recall"], 6),
        round(m["F1"], 6),
        round(m["IoU"], 6),
    ]
    output_rows.append(row)

    total_TP += m["TP"]
    total_FP += m["FP"]
    total_FN += m["FN"]
    total_TN += m["TN"]

# Compute totals
total_precision = total_TP / (total_TP + total_FP) if (total_TP + total_FP) > 0 else 0
total_recall    = total_TP / (total_TP + total_FN) if (total_TP + total_FN) > 0 else 0
total_f1        = 2 * total_precision * total_recall / (total_precision + total_recall) if (total_precision + total_recall) > 0 else 0
total_iou       = total_TP / (total_TP + total_FP + total_FN) if (total_TP + total_FP + total_FN) > 0 else 0

output_rows.append([
    "Total",
    total_TP,
    total_FP,
    total_FN,
    total_TN,
    round(total_precision, 6),
    round(total_recall, 6),
    round(total_f1, 6),
    round(total_iou, 6),
])

# Write CSV
with open("evaluation_results.csv", "w", newline="") as f:
    writer = csv.writer(f)
    writer.writerow(["Property", "TP", "FP", "FN", "TN", "Precision", "Recall", "F1", "IoU"])
    writer.writerows(output_rows)

print("Saved CSV as evaluation_results.csv")