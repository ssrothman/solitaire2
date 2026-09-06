"""Command-line dispatch for solitaire2 Python tools."""

from __future__ import annotations

import sys
from collections.abc import Callable, Sequence


def _scaffold_tool(arguments: Sequence[str]) -> int:
    del arguments
    print("solitaire2 tool scaffold: implementation pending")
    return 0


TOOLS: dict[str, Callable[[Sequence[str]], int]] = {
    "scaffold": _scaffold_tool,
}


def main(arguments: Sequence[str] | None = None) -> int:
    """Dispatch to the Python tool named by the first argument."""
    args = list(sys.argv[1:] if arguments is None else arguments)
    if not args:
        print("usage: solitaire2 <tool> [arguments]")
        print("available tools: " + ", ".join(sorted(TOOLS)))
        return 2

    tool = TOOLS.get(args[0])
    if tool is None:
        print(f"unknown tool: {args[0]}", file=sys.stderr)
        return 2
    return tool(args[1:])


if __name__ == "__main__":
    raise SystemExit(main())
