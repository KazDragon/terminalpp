#!/usr/bin/env python3

from __future__ import annotations

import argparse
import json
import re
import sys
from dataclasses import dataclass


SEMVER_LABELS = {
    "semver:major": "major",
    "semver:minor": "minor",
    "semver:patch": "patch",
}


BREAKING_PATTERNS = (
    r"\bbreaking change\b",
    r"\bbreaking\b",
    r"\bbackward incompatible\b",
    r"\bbackwards incompatible\b",
)


MINOR_PATTERNS = (
    r"\bnew feature\b",
    r"\bfeature\b",
    r"\benhancement\b",
    r"\badds? support\b",
)


CONVENTIONAL_MAJOR = re.compile(r"^[a-z]+(?:\([^)]+\))?!:", re.IGNORECASE)
CONVENTIONAL_MINOR = re.compile(r"^feat(?:\([^)]+\))?:", re.IGNORECASE)
CONVENTIONAL_PATCH = re.compile(r"^(?:fix|perf)(?:\([^)]+\))?:", re.IGNORECASE)


@dataclass(frozen=True, order=True)
class Version:
    major: int
    minor: int
    patch: int

    @classmethod
    def parse(cls, value: str) -> "Version":
        match = re.fullmatch(r"v?(\d+)\.(\d+)\.(\d+)", value.strip())
        if not match:
            raise ValueError(f"Unsupported semantic version: {value!r}")

        return cls(*(int(part) for part in match.groups()))

    def bump(self, release_type: str) -> "Version":
        if release_type == "major":
            return Version(self.major + 1, 0, 0)
        if release_type == "minor":
            return Version(self.major, self.minor + 1, 0)
        if release_type == "patch":
            return Version(self.major, self.minor, self.patch + 1)

        raise ValueError(f"Unknown release type: {release_type}")

    def tag(self) -> str:
        return f"v{self.major}.{self.minor}.{self.patch}"


def choose_release_type(labels: list[str], title: str, body: str, commits: list[str]) -> tuple[str, str]:
    normalized_labels = {label.strip().lower() for label in labels if label.strip()}

    for label, release_type in SEMVER_LABELS.items():
        if label in normalized_labels:
            return release_type, f"label:{label}"

    combined_text = "\n".join([title, body, *commits]).lower()

    if "!" in title and CONVENTIONAL_MAJOR.match(title):
        return "major", "title:conventional-breaking"

    if CONVENTIONAL_MINOR.match(title):
        return "minor", "title:conventional-feat"

    if CONVENTIONAL_PATCH.match(title):
        return "patch", "title:conventional-fix"

    for commit in commits:
        if CONVENTIONAL_MAJOR.match(commit):
            return "major", f"commit:{commit}"

    for pattern in BREAKING_PATTERNS:
        if re.search(pattern, combined_text):
            return "major", f"text:{pattern}"

    for commit in commits:
        if CONVENTIONAL_MINOR.match(commit):
            return "minor", f"commit:{commit}"

    if any(re.search(pattern, combined_text) for pattern in MINOR_PATTERNS):
        return "minor", "text:feature"

    for commit in commits:
        if CONVENTIONAL_PATCH.match(commit):
            return "patch", f"commit:{commit}"

    return "patch", "default:patch"


def main() -> int:
    parser = argparse.ArgumentParser(description="Compute the next Terminal++ release version")
    parser.add_argument("--current-version", required=True, help="Current semantic version or tag")
    parser.add_argument("--labels-json", default="[]", help="JSON array of pull request labels")
    parser.add_argument("--title", default="", help="Pull request title")
    parser.add_argument("--body", default="", help="Pull request body")
    parser.add_argument(
        "--commits-json",
        default="[]",
        help="JSON array of commit subjects associated with the release",
    )
    args = parser.parse_args()

    try:
        current_version = Version.parse(args.current_version)
        labels = json.loads(args.labels_json)
        commits = json.loads(args.commits_json)
    except (ValueError, json.JSONDecodeError) as exc:
        print(str(exc), file=sys.stderr)
        return 1

    if not isinstance(labels, list) or not all(isinstance(item, str) for item in labels):
        print("--labels-json must decode to a list of strings", file=sys.stderr)
        return 1

    if not isinstance(commits, list) or not all(isinstance(item, str) for item in commits):
        print("--commits-json must decode to a list of strings", file=sys.stderr)
        return 1

    release_type, reason = choose_release_type(labels, args.title, args.body, commits)
    next_version = current_version.bump(release_type)

    print(f"release_type={release_type}")
    print(f"reason={reason}")
    print(f"current_tag={current_version.tag()}")
    print(f"next_tag={next_version.tag()}")
    print(f"next_version={next_version.major}.{next_version.minor}.{next_version.patch}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
