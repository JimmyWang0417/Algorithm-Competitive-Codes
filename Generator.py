#!/usr/bin/env python3
import os
from pathlib import Path
import re
import subprocess
from tempfile import TemporaryDirectory


REPO_ROOT = Path(__file__).resolve().parent
README_PATH = REPO_ROOT / "README.md"
COUNT_BEGIN = "<!-- count the code begin -->"
COUNT_END = "<!-- count the code end -->"
TREE_BEGIN = "<!-- directory tree begin -->"
TREE_END = "<!-- directory tree end -->"


def run_output(command: list[str]) -> str:
    return subprocess.run(
        command,
        cwd=REPO_ROOT,
        check=True,
        capture_output=True,
        text=True,
    ).stdout


def build_directory_tree() -> str:
    """Render a tree containing repository files not ignored by Git rules."""
    listed = subprocess.run(
        ["git", "ls-files", "--cached", "--others", "--exclude-standard", "-z"],
        cwd=REPO_ROOT,
        check=True,
        capture_output=True,
    ).stdout
    ignored = subprocess.run(
        ["git", "check-ignore", "--no-index", "--stdin", "-z"],
        cwd=REPO_ROOT,
        input=listed,
        check=False,
        capture_output=True,
    ).stdout
    ignored_paths = set(ignored.split(b"\0"))

    with TemporaryDirectory(prefix="gitignore-tree-") as temp_dir:
        tree_root = Path(temp_dir)
        for raw_path in listed.split(b"\0"):
            if not raw_path:
                continue
            relative_path = Path(os.fsdecode(raw_path))
            if raw_path in ignored_paths or ".git" in relative_path.parts:
                continue
            destination = tree_root / relative_path
            destination.parent.mkdir(parents=True, exist_ok=True)
            destination.touch()

        return subprocess.run(
            [
                "lsd",
                "--tree",
                "--all",
                "--ignore-config",
                "--ignore-glob",
                ".git",
                "--icon",
                "never",
            ],
            cwd=tree_root,
            check=True,
            capture_output=True,
            text=True,
        ).stdout


def replace_block(markdown: str, begin: str, end: str, content: str) -> str:
    if markdown.count(begin) != 1 or markdown.count(end) != 1:
        raise RuntimeError(f"README marker count is invalid: {begin} / {end}")
    pattern = re.compile(
        rf"^{re.escape(begin)}\r?\n.*?^{re.escape(end)}",
        flags=re.MULTILINE | re.DOTALL,
    )
    replacement = f"{begin}\n```plain\n{content.rstrip(chr(10))}\n```\n{end}"
    updated, count = pattern.subn(lambda _: replacement, markdown, count=1)
    if count != 1:
        raise RuntimeError(f"README marker block not found: {begin}")
    return updated


def main() -> None:
    markdown = README_PATH.read_text(encoding="utf-8")
    markdown = replace_block(markdown, COUNT_BEGIN, COUNT_END, run_output(["tokei"]))
    markdown = replace_block(markdown, TREE_BEGIN, TREE_END, build_directory_tree())
    README_PATH.write_text(markdown, encoding="utf-8")


if __name__ == "__main__":
    main()
