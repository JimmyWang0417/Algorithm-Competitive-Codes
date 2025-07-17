#!/usr/bin/env python3
import os
import re

intxt = [
    "<!-- count the code begin -->\n[^<]*<!-- count the code end -->\n",
    "<!-- directory tree begin -->\n[^<]*<!-- directory tree end -->\n"
]
outxt = ["tokei", "lsd --tree -I Environment -I __pycache__ --icon never"]
with open("README.md", "r+", encoding="utf-8") as filetxt:
    lines = filetxt.read()
    filetxt.seek(0)
    for a, b in zip(intxt, outxt):
        lines = re.sub(
            a,
            re.sub(r"\[\^<\]\*", r"{}", a).format("```plain\n" + os.popen(b).read() + "```\n"),
            lines,
            flags=re.M  # 明确指定 flags 参数
        )
    filetxt.write(lines)