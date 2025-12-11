import pandas as pd

PRED_FILE = "../proportional_missing/coupled/seed2025/iid_mr_0_1/merged_violation_iid_mr_0_1_probabilistic.csv"
TRUTH_FILE = "coupled_truth_labels.csv"
NUM_PROPERTIES = 4

print("Loading predictions from:", PRED_FILE)
pred = pd.read_csv(PRED_FILE)

print("Loading truth from:", TRUTH_FILE)
truth = pd.read_csv(TRUTH_FILE)

assert "time" in pred.columns
assert "time" in truth.columns

merged = pred.merge(truth, on="time", how="inner")

if len(merged) == 0:
    raise ValueError("ERROR: The merge produced 0 rows. "
                     "Time columns probably do not match. "
                     "Check the 'time' column formatting!")

print(f"Merged rows: {len(merged)}")

metrics = {}

for i in range(1, NUM_PROPERTIES + 1):

    pred_col = f"pred_P{i}"
    truth_col = f"viol_C{i}"

    if pred_col not in merged:
        raise KeyError(f"Missing column in predictions: {pred_col}")

    if truth_col not in merged:
        raise KeyError(f"Missing column in truth file: {truth_col}")

    p = merged[pred_col]
    t = merged[truth_col]

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

print("\n===== Evaluation Results =====\n")
for prop, data in metrics.items():
    print(f"{prop}:")
    for k, v in data.items():
        print(f"  {k}: {v}")
    print()
