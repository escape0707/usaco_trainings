"""
ID: totheso1
LANG: PYTHON3
TASK: msquare
"""

from __future__ import annotations

from dataclasses import dataclass
from typing import Any, Optional, cast, Tuple

fin = open("msquare.in", "r")
fout = open("msquare.out", "w")


def fprint(*args: Any, **kwargs: Any) -> None:
    print(*args, file=fout, **kwargs)


# Code start
INITIAL = "12345678"
GOAL = fin.readline().strip().replace(" ", "")


def solve() -> None:
    @dataclass
    class TreeNode:
        operation: int
        prev: Optional[TreeNode]

    def print_node(head: TreeNode) -> None:
        ord_A = ord("A")
        operation_collection_reversed = []
        while (operation := head.operation) != -1:
            operation_collection_reversed.append(chr(operation + ord_A))
            head = cast(TreeNode, head.prev)
        fprint("".join(reversed(operation_collection_reversed)))

    trans_collection = (
        (7, 6, 5, 4, 3, 2, 1, 0),
        (3, 0, 1, 2, 5, 6, 7, 4),
        (0, 6, 1, 3, 4, 2, 5, 7),
    )

    def apply_transform(state: str, trans: Tuple[int, ...]) -> str:
        return "".join(map(state.__getitem__, trans))

    queue = [(INITIAL, TreeNode(-1, None))]
    visited_state_collection = {INITIAL}
    length = -1
    while queue:
        length += 1
        next_queue = []
        for state, node in queue:
            if state == GOAL:
                fprint(length)
                print_node(node)
                return
            for i, trans in enumerate(trans_collection):
                next_state = apply_transform(state, trans)
                if next_state not in visited_state_collection:
                    next_queue.append((next_state, TreeNode(i, node)))
                    visited_state_collection.add(next_state)
        queue = next_queue


solve()
# Code end
