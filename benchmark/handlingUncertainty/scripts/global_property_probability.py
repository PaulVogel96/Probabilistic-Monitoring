import csv

CSV_PATH = "coupled_truth_truth.csv"

COLUMNS = ["p", "r", "s"]

counts_true = {col: 0 for col in COLUMNS}
total_rows = 0

with open(CSV_PATH, newline="") as f:
    reader = csv.DictReader(f)
    for row in reader:
        total_rows += 1
        for col in COLUMNS:
            val = row[col].strip()
            if val == "1":
                counts_true[col] += 1

print(f"Total rows: {total_rows}\n")

for col in COLUMNS:
    prob = counts_true[col] / total_rows if total_rows > 0 else 0
    print(f"{col}: {counts_true[col]} true → P({col}=1) = {prob:.4f}")
