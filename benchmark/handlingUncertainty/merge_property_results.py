import csv

files = {
    "pred_P1": "proportional_missing/coupled/iid_mr_0_1/P1/result.csv",
    "pred_P2": "proportional_missing/coupled/iid_mr_0_1/P2/result.csv",
    "pred_P3": "proportional_missing/coupled/iid_mr_0_1/P3/result.csv",
    "pred_P4": "proportional_missing/coupled/iid_mr_0_1/P4/result.csv"
}

merged = {}

for prop, fname in files.items():
    with open(fname, newline='') as f:
        reader = csv.DictReader(f)
        for row in reader:
            t = int(row["ts"])
            if t not in merged:
                merged[t] = {}
            merged[t][prop] = int(row["violated"])

timestamps = sorted(merged.keys())

with open("merged_violation_iid_mr_0_1.csv", "w", newline='') as f:
    writer = csv.writer(f)
    writer.writerow(["time","pred_P1","pred_P2","pred_P3","pred_P4"])
    for t in timestamps:
        writer.writerow([
            t,
            merged[t].get("pred_P1", 0),
            merged[t].get("pred_P2", 0),
            merged[t].get("pred_P3", 0),
            merged[t].get("pred_P4", 0),
        ])