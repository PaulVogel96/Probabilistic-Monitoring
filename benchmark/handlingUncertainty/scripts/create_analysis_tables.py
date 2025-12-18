from pathlib import Path
import os
import pandas as pd

# Automatically detect root folder (handlingUncertainty)
SCRIPT_DIR = Path(__file__).resolve().parent
ROOT_DIR = SCRIPT_DIR.parent     # parent of 'scripts/'

SEEDS = ["seed2025", "seed2099"]
PROPERTIES = ["P1", "P2", "P3", "P4", "Total"]

COUPLED_FILE = "results_metrics.csv"
VAR_LIMIT_FILE_GLOB = "result_*_metrics.csv"

OUTPUT_DIR = ROOT_DIR / "merged_results"


# ==============================
# HELPERS
# ==============================

def classify_setup(path: Path) -> int:
    """Used for sorting: coupled before coupled_prob_var_limit."""
    parts = path.parts
    if "coupled" in parts and "coupled_prob_var_limit" not in parts:
        return 0
    if "coupled_prob_var_limit" in parts:
        return 1
    return 2


def sort_key(path: Path) -> tuple:
    """Sort entries by logical hierarchy."""
    try:
        rel = path.relative_to(ROOT_DIR)
    except ValueError:
        rel = path

    parts = list(rel.parts)

    general = parts[0] if len(parts) > 0 else ""
    seed = ""
    specific = ""
    filename = path.name
    setup_order = classify_setup(path)

    for p in parts:
        if p in SEEDS:
            seed = p

    if len(parts) >= 2:
        specific = parts[-2]

    return (general, seed, setup_order, specific, filename)


def collect_result_files_for_seed(seed: str):
    """Collect coupled + var_limit metric files."""
    result_files = []

    # Coupled: results_metrics.csv
    for path in ROOT_DIR.rglob(COUPLED_FILE):
        if f"/{seed}/" in str(path).replace(os.sep, "/"):
            result_files.append(path)

    # Var-limit: result_X_Y_metrics.csv
    for path in ROOT_DIR.rglob(VAR_LIMIT_FILE_GLOB):
        if f"/{seed}/" in str(path).replace(os.sep, "/"):
            result_files.append(path)

    result_files.sort(key=sort_key)
    return result_files


# ==============================
# MAIN LOGIC
# ==============================

def build_merged_tables_for_seed(seed: str):
    result_files = collect_result_files_for_seed(seed)
    if not result_files:
        print(f"No result metric files found for {seed}")
        return

    per_property_rows = {prop: [] for prop in PROPERTIES}

    for csv_path in result_files:
        try:
            df = pd.read_csv(csv_path)
        except Exception as e:
            print(f"Could not read {csv_path}: {e}")
            continue

        if "Property" not in df.columns:
            print(f"Skipping {csv_path}: no 'Property' column")
            continue

        for prop in PROPERTIES:
            row_df = df[df["Property"] == prop]
            if row_df.empty:
                print(f"WARNING: {csv_path} missing row for Property={prop}")
                continue

            row = row_df.iloc[0]
            metrics = ["TP", "FP", "FN", "TN", "Precision", "Recall", "F1", "IoU"]

            missing = [m for m in metrics if m not in row_df.columns]
            if missing:
                print(f"WARNING: {csv_path} missing {missing} for {prop}")
                continue

            per_property_rows[prop].append({
                "file": str(csv_path),
                **{m: row[m] for m in metrics}
            })

    OUTPUT_DIR.mkdir(parents=True, exist_ok=True)

    for prop in PROPERTIES:
        rows = per_property_rows[prop]
        if not rows:
            print(f"No rows collected for {prop} in {seed}, skipping.")
            continue

        merged_df = pd.DataFrame(rows)
        out_path = OUTPUT_DIR / f"merged_{seed}_{prop}.csv"
        merged_df.to_csv(out_path, index=False)
        print(f"Wrote merged file: {out_path}")


def main():
    print(f"ROOT_DIR = {ROOT_DIR}")
    print(f"Writing merged CSVs to {OUTPUT_DIR}")

    for seed in SEEDS:
        print(f"\n=== Processing seed {seed} ===")
        build_merged_tables_for_seed(seed)


if __name__ == "__main__":
    main()
