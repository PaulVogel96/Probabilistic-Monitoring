import csv

def count_ones_per_column(csv_file_path):
    counts = {}

    with open(csv_file_path, newline="") as csvfile:
        reader = csv.DictReader(csvfile)

        for field in reader.fieldnames:
            if field != "time":
                counts[field] = 0

        for row in reader:
            for field in counts:
                value = row[field].strip().strip('"')
                if value == "1":
                    counts[field] += 1

    return counts


if __name__ == "__main__":
    csv_path = "coupled_truth_labels.csv"
    result = count_ones_per_column(csv_path)

    for column, count in result.items():
        print(f"{column}: {count}")
