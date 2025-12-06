import csv

event_map = {
    'p': "EVENT_P",
    'q': "EVENT_Q",
    'r': "EVENT_R",
    's': "EVENT_S",
    'n': "EVENT_N",
    'x': "EVENT_X",
    'y': "EVENT_Y",
}

csv_file = "independent_truth_with_violations.csv"
vector_name = "independent_truth_with_violations"

vector_entries = []

with open(csv_file, newline='') as f:
    reader = csv.DictReader(f)
    for row in reader:
        active_events = []
        for event, cpp_name in event_map.items():
            if row.get(event, "").strip().lower() == 'true':
                active_events.append(cpp_name)
        if not active_events:
            active_events.append("EVENT_NONE")
        vector_entries.append(" | ".join(active_events))

vector_string = f"const uint8_t {vector_name}[] PROGMEM = {{ {', '.join(vector_entries)} }};"
print(vector_string)