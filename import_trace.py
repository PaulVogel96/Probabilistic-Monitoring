import csv

event_map = {
    'p': 1 << 0,
    's': 1 << 1,
    'q': 1 << 2,
    'r': 1 << 3,
}

csv_file = "trace.csv"
vector_name = "events_to_process"

vector_entries = []

with open(csv_file, newline='') as f:
    reader = csv.DictReader(f)
    for row in reader:
        mask = 0
        for event, bit in event_map.items():
            if row[event].strip().lower() == 'true':
                mask |= bit
        vector_entries.append(f"{mask}")

vector_string = f"std::vector<uint8_t> {vector_name} = {{ {', '.join(vector_entries)} }};"
print(vector_string)