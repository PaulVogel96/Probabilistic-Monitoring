#!/usr/bin/env python3
"""
Create compact LaTeX tables from merged CSVs.

Input:
  handlingUncertainty/merged_results/merged_<seed>_<prop>.csv

Output:
  handlingUncertainty/merged_results_latex/<seed>_<prop>.tex

Features:
- Output filenames: seed2025_P1.tex, seed2099_Total.tex, ...
- Column 'file' -> 'experiment' with human-readable labels
- Deterministic runs marked with ", det"
- Probabilistic runs show ", vt = <threshold>"
- Very compact layout (tiny font, tight column spacing)
- Each table starts on its own page (\clearpage)
- Float metrics cut to 3 decimals
- Column headers: underscores -> spaces; FP% printed correctly as FP\%
- longtable centered on page (LTleft/LTright fill), caption width set to textwidth
- Reduced vertical spacing around longtable/caption to help fit one page
"""

from pathlib import Path
from typing import Tuple, Optional
import re
import pandas as pd

# ==============================
# CONFIG
# ==============================

SCRIPT_DIR = Path(__file__).resolve().parent
ROOT_DIR = SCRIPT_DIR.parent  # handlingUncertainty/

INPUT_DIR = ROOT_DIR / "merged_results"
OUTPUT_DIR = ROOT_DIR / "merged_results_latex"

USE_LONGTABLE = True

# Compact table settings
LATEX_FONT_SIZE = r"\tiny"
TABCOLSEP_PT = 1
ARRAYSTRETCH = 0.85  # keep as-is (no tweak requested)

# Number formatting
FLOAT_FORMAT = "{:.3f}"  # 3 decimals

CSV_SEP = ";"
CSV_DECIMAL = ","

# Column renaming (merged CSV -> LaTeX table)
RENAME_COLS = {
    "file": "experiment",
    "FP_pct": "FP%",
    "TP_identical_vs_det": "TP_shared",
    "TP_det_not_in_prob": "TP_det_only",
    "TP_prob_not_in_det": "TP_prob_only",
}

# Desired order (after renaming)
COL_ORDER = [
    "experiment",
    "TP", "FP", "FN", "TN",
    "Precision", "Recall", "F1", "IoU",
    "FP%", "Denom",
    "TP_shared", "TP_det_only", "TP_prob_only",
]

INT_COLS = {
    "TP", "FP", "FN", "TN", "Denom",
    "TP_shared", "TP_det_only", "TP_prob_only",
}
FLOAT_COLS = {"Precision", "Recall", "F1", "IoU", "FP%"}


# ==============================
# LATEX HELPERS
# ==============================

def latex_escape(s: str) -> str:
    if s is None:
        return ""
    s = str(s)
    replacements = {
        "\\": r"\textbackslash{}",
        "_": r"\_",
        "%": r"\%",
        "&": r"\&",
        "#": r"\#",
        "{": r"\{",
        "}": r"\}",
        "$": r"\$",
        "~": r"\textasciitilde{}",
        "^": r"\textasciitilde{}",
    }
    for k, v in replacements.items():
        s = s.replace(k, v)
    return s


def header_display_name(col: str) -> str:
    """Printed header only: underscores -> spaces. Let latex_escape handle special chars like %."""
    return col.replace("_", " ")


def format_cell(col: str, val) -> str:
    try:
        if pd.isna(val):
            return ""
    except Exception:
        pass

    if col == "experiment":
        return latex_escape(str(val))

    if col in INT_COLS:
        try:
            return str(int(float(val)))
        except Exception:
            return latex_escape(str(val))

    if col in FLOAT_COLS:
        try:
            return FLOAT_FORMAT.format(float(val))
        except Exception:
            return latex_escape(str(val))

    return latex_escape(str(val))


def df_to_latex_tabular(df: pd.DataFrame, caption: str, label: str) -> str:
    cols = list(df.columns)
    align = "l" + "r" * (len(cols) - 1)

    header = " & ".join([latex_escape(header_display_name(c)) for c in cols]) + r" \\"

    lines = []
    # each table starts on its own page
    lines.append(r"\clearpage")

    # scope compact settings locally
    lines.append("{")
    lines.append(LATEX_FONT_SIZE)
    lines.append(r"\setlength{\tabcolsep}{" + str(TABCOLSEP_PT) + r"pt}")
    lines.append(r"\renewcommand{\arraystretch}{" + str(ARRAYSTRETCH) + r"}")

    # reduce vertical whitespace around longtable/caption
    lines.append(r"\setlength{\LTpre}{0pt}")
    lines.append(r"\setlength{\LTpost}{0pt}")
    lines.append(r"\setlength{\abovecaptionskip}{0pt}")
    lines.append(r"\setlength{\belowcaptionskip}{0pt}")

    if USE_LONGTABLE:
        # center longtable on page + keep caption width reasonable
        lines.append(r"\setlength{\LTleft}{\fill}")
        lines.append(r"\setlength{\LTright}{\fill}")
        lines.append(r"\setlength{\LTcapwidth}{\textwidth}")

        lines.append(r"\begin{longtable}{" + align + r"}")
        lines.append(r"\caption{" + caption + r"}\label{" + label + r"} \\")
        lines.append(r"\toprule")
        lines.append(header)
        lines.append(r"\midrule")
        lines.append(r"\endfirsthead")

        lines.append(r"\toprule")
        lines.append(header)
        lines.append(r"\midrule")
        lines.append(r"\endhead")

        lines.append(r"\bottomrule")
        lines.append(r"\endfoot")
    else:
        lines.append(r"\begin{table}[htbp]")
        lines.append(r"\centering")
        lines.append(r"\caption{" + caption + r"}")
        lines.append(r"\label{" + label + r"}")
        lines.append(r"\begin{tabular}{" + align + r"}")
        lines.append(r"\toprule")
        lines.append(header)
        lines.append(r"\midrule")

    for _, row in df.iterrows():
        row_cells = [format_cell(c, row[c]) for c in cols]
        lines.append(" & ".join(row_cells) + r" \\")

    if USE_LONGTABLE:
        lines.append(r"\end{longtable}")
    else:
        lines.append(r"\bottomrule")
        lines.append(r"\end{tabular}")
        lines.append(r"\end{table}")

    lines.append("}")  # end scope

    return "\n".join(lines) + "\n"


# ==============================
# PATH -> LABEL MAPPING
# ==============================

def ufloat_from_underscores(s: str) -> str:
    return "" if s is None else s.replace("_", ".")


def extract_vt_from_metrics_filename(name: str) -> Optional[str]:
    m = re.match(r"result_(\d+_\d+)_metrics\.csv$", name)
    if not m:
        return None
    return ufloat_from_underscores(m.group(1))


def format_experiment_label(rel_path_str: str) -> str:
    """
    Convert a path (relative to handlingUncertainty/) into a compact experiment label.
    """
    p = Path(rel_path_str)
    parts = p.parts
    if len(parts) < 5:
        return rel_path_str

    general = parts[0]      # blocking_missing, periodic, event_missing, ...
    setup = parts[1]        # coupled / coupled_prob_var_limit
    specific = parts[3]     # experiment folder name
    filename = parts[-1]    # metrics file name

    general_label = general.replace("_", " ")

    is_det = (setup == "coupled")
    vt = None
    if setup == "coupled_prob_var_limit":
        vt = extract_vt_from_metrics_filename(filename)

    det_suffix = ", det" if is_det else ""

    # blocking_missing: burst_mr_0_2_L_5
    m = re.match(r"burst_mr_(\d+_\d+)_L_(\d+)$", specific)
    if m:
        mr = ufloat_from_underscores(m.group(1))
        L = m.group(2)
        if vt is None:
            return "{} (mr = {}, l = {}{})".format(general_label, mr, L, det_suffix)
        return "{} (mr = {}, l = {}, vt = {})".format(general_label, mr, L, vt)

    # proportional_missing: iid_mr_0_05
    m = re.match(r"iid_mr_(\d+_\d+)$", specific)
    if m:
        mr = ufloat_from_underscores(m.group(1))
        if vt is None:
            return "{} (mr = {}{})".format(general_label, mr, det_suffix)
        return "{} (mr = {}, vt = {})".format(general_label, mr, vt)

    # periodic: T20_keep0_7
    m = re.match(r"T(\d+)_keep(\d+_\d+)$", specific)
    if m:
        T = m.group(1)
        keep = ufloat_from_underscores(m.group(2))
        if vt is None:
            return "{} (T = {}, keep = {}{})".format(general_label, T, keep, det_suffix)
        return "{} (T = {}, keep = {}, vt = {})".format(general_label, T, keep, vt)

    # event_missing: col-p_mcar_1_0 -> ONLY show (col = p)
    m = re.match(r"col-([a-zA-Z]+)_mcar_(\d+_\d+)$", specific)
    if m:
        col = m.group(1)
        if vt is None:
            return "{} (col = {}{})".format(general_label, col, det_suffix)
        return "{} (col = {}, vt = {})".format(general_label, col, vt)

    # fallback
    if vt is None:
        return "{} ({})".format(general_label, specific + (", det" if is_det else ""))
    return "{} ({}, vt = {})".format(general_label, specific, vt)


# ==============================
# CSV READ + TRANSFORM
# ==============================

def clean_numeric_series(series: pd.Series) -> pd.Series:
    """
    Robust numeric parsing:
    - strip whitespace
    - normalize decimal comma -> dot
    - remove stray non-numeric characters
    """
    s = series.astype(str).str.strip()
    s = s.replace({"": ""})
    s = s.str.replace(",", ".", regex=False)
    s = s.str.replace(r"[^0-9\.\-]", "", regex=True)
    return s


def read_merged_csv(csv_path: Path) -> pd.DataFrame:
    df = pd.read_csv(
        csv_path,
        sep=CSV_SEP,
        decimal=CSV_DECIMAL,
        dtype=str,
        keep_default_na=False,
    )

    if "file" not in df.columns:
        raise ValueError("Expected a 'file' column in {}".format(csv_path))

    df = df.rename(columns=RENAME_COLS)

    # experiment column from former file path
    df["experiment"] = df["experiment"].apply(format_experiment_label)

    # reorder columns
    cols = [c for c in COL_ORDER if c in df.columns] + [c for c in df.columns if c not in COL_ORDER]
    df = df[cols]

    # parse numeric cols
    for c in df.columns:
        if c in INT_COLS:
            df[c] = pd.to_numeric(clean_numeric_series(df[c]), errors="coerce")
        elif c in FLOAT_COLS:
            df[c] = pd.to_numeric(clean_numeric_series(df[c]), errors="coerce")

    return df


def make_caption_and_label(seed: str, prop: str) -> Tuple[str, str]:
    # shorter caption to save vertical space
    caption = "{} --- {}.".format(seed, prop)
    label = "tab:{}_{}".format(seed, prop)
    return caption, label


# ==============================
# MAIN
# ==============================

def main():
    if not INPUT_DIR.exists():
        raise SystemExit("Input dir not found: {}".format(INPUT_DIR))

    OUTPUT_DIR.mkdir(parents=True, exist_ok=True)

    csv_files = sorted(INPUT_DIR.glob("merged_*.csv"))
    if not csv_files:
        raise SystemExit("No merged CSV files found in: {}".format(INPUT_DIR))

    print("Reading from:", INPUT_DIR)
    print("Writing .tex to:", OUTPUT_DIR)
    print("Mode:", "longtable" if USE_LONGTABLE else "table")

    for csv_path in csv_files:
        # merged_seed2025_P1.csv
        stem = csv_path.stem
        parts = stem.split("_")
        if len(parts) < 3:
            print("Skipping unexpected filename:", csv_path.name)
            continue

        seed = parts[1]
        prop = parts[2]

        df = read_merged_csv(csv_path)
        caption, label = make_caption_and_label(seed, prop)

        tex = df_to_latex_tabular(df, caption=caption, label=label)

        out_path = OUTPUT_DIR / "{}_{}.tex".format(seed, prop)
        out_path.write_text(tex, encoding="utf-8")
        print("Wrote:", out_path)

    print("\nDone.")
    print("LaTeX requirements:")
    print(r"  \usepackage{booktabs}")
    if USE_LONGTABLE:
        print(r"  \usepackage{longtable}")


if __name__ == "__main__":
    main()
