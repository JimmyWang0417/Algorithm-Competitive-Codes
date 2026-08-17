#!/usr/bin/env python3
import os
import re
import subprocess
import tempfile
from pathlib import Path


def generate_tree():
    paths = subprocess.check_output(
        ["git", "ls-files", "--cached", "--others", "--exclude-standard", "-z"]
    ).decode().rstrip("\0").split("\0")
    with tempfile.TemporaryDirectory() as directory:
        root = Path(directory)
        for path in paths:
            target = root / path
            target.parent.mkdir(parents=True, exist_ok=True)
            target.touch()
        return subprocess.check_output(
            ["lsd", "--tree", "--all", "--ignore-config", "--icon", "never", "."],
            cwd=root,
            text=True,
        )

intxt = [
    "<!-- count the code begin -->\n[^<]*<!-- count the code end -->\n",
    "<!-- directory tree begin -->\n[^<]*<!-- directory tree end -->\n"
]
outxt = [os.popen("tokei").read(), generate_tree()]
with open("README.md", "r+", encoding="utf-8") as filetxt:
    lines = filetxt.read()
    tree_end = "<!-- directory tree end -->"
    if lines.count(tree_end) > 1:
        lines = lines[:lines.index(tree_end) + len(tree_end)] + "\n"
    filetxt.seek(0)
    for a, output in zip(intxt, outxt):
        lines = re.sub(
            a,
            re.sub(r"\[\^<\]\*", r"{}", a).format("```plain\n" + output + "```\n"),
            lines,
            flags=re.M  # 明确指定 flags 参数
        )
    filetxt.write(lines)
    filetxt.truncate()
