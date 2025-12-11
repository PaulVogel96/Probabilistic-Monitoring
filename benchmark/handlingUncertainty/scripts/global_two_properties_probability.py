import csv

def prob_column_true(csv_file, column):
    total = 0
    true_count = 0

    with open(csv_file, newline='') as f:
        reader = csv.DictReader(f)
        for row in reader:
            val = row.get(column)
            total += 1
            if val.strip() in ("1"):
                true_count += 1

    if total == 0:
        return 0.0

    return true_count / total

def prob_p_and_s_true(csv_file, col_p="p", col_s="s"):
    total = 0
    both_true = 0

    with open(csv_file, newline='') as f:
        reader = csv.DictReader(f)
        for row in reader:
            vp = row.get(col_p)
            vs = row.get(col_s)
            total += 1

            p_true = vp.strip() in ("1")
            s_true = vs.strip() in ("1")

            if p_true and s_true:
                both_true += 1

    if total == 0:
        return 0.0

    return both_true / total


if __name__ == "__main__":
    csv_file = "coupled_truth_truth.csv"

    p_prob = prob_column_true(csv_file, "p")
    print(f"P(true) = {p_prob:.6f}")

    s_prob = prob_column_true(csv_file, "s")
    print(f"S(true) = {s_prob:.6f}")

    p_and_s_prob = prob_p_and_s_true(csv_file, "p", "s")
    print(f"P & S (both true) = {p_and_s_prob:.6f}")