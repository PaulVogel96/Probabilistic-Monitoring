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

csv_file = "proportional_missing/seed2099/coupled_truth.tessla.iid.mr0.05.csv"
vector_name = "coupled_proportional_missing_seed2099_iid_mr_0_05"

vector_entries = []

with open(csv_file, newline='') as f:
    reader = csv.DictReader(f)
    for row in reader:
        active_events = []
        all_missing = True
        for event, cpp_name in event_map.items():
            cell = row.get(event, "").strip().lower()

            if cell in ["true", "1"]:
                active_events.append(cpp_name)
                all_missing = False

            elif cell in ["false", "0"]:
                all_missing = False

            elif cell == "" or cell == "nan":
                pass
            else:
                pass

        if all_missing:
            active_events = ["EVENTS_MISSING"]

        elif not active_events:
            active_events = ["EVENT_NONE"]

        vector_entries.append(" | ".join(active_events))

vector_string = f"const uint8_t {vector_name}[] PROGMEM = {{ {', '.join(vector_entries)} }};"
print(vector_string)