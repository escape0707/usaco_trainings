"""
ID: totheso1
LANG: PYTHON3
TASK: shuttle
"""

from __future__ import annotations

from dataclasses import dataclass
from itertools import islice
from typing import Any, Tuple, cast

fin = open("shuttle.in", "r")
fout = open("shuttle.out", "w")


def fprint(*args: Any, **kwargs: Any) -> None:
    print(*args, file=fout, **kwargs)


# Code start
N = int(fin.readline())


def solve() -> None:
    @dataclass
    class TreeNode:
        move: int
        prev: TreeNode

    def bfs(start: str) -> TreeNode:
        que = [(start, TreeNode(-1, cast(TreeNode, None)))]
        visited_collection = set((start,))
        while que:
            next_que = []
            for curr_state, prev in que:
                empty_pos = curr_state.find("_")
                next_state_collection = []
                if 1 <= empty_pos:
                    if curr_state[empty_pos - 1] == "B":
                        if 2 <= empty_pos and curr_state[empty_pos - 2] == "W":
                            next_state_collection.append(
                                (
                                    curr_state[: empty_pos - 2]
                                    + "_BW"
                                    + curr_state[empty_pos + 1 :],
                                    TreeNode(empty_pos - 2, prev),
                                )
                            )
                    else:
                        next_state_collection.append(
                            (
                                curr_state[: empty_pos - 1]
                                + "_W"
                                + curr_state[empty_pos + 1 :],
                                TreeNode(empty_pos - 1, prev),
                            )
                        )
                if empty_pos < 2 * N:
                    if curr_state[empty_pos + 1] == "B":
                        next_state_collection.append(
                            (
                                curr_state[:empty_pos]
                                + "B_"
                                + curr_state[empty_pos + 2 :],
                                TreeNode(empty_pos + 1, prev),
                            )
                        )
                    elif empty_pos < 2 * N - 1 and curr_state[empty_pos + 2] == "B":
                        next_state_collection.append(
                            (
                                curr_state[:empty_pos]
                                + "BW_"
                                + curr_state[empty_pos + 3 :],
                                TreeNode(empty_pos + 2, prev),
                            )
                        )
                for state_node in next_state_collection:
                    next_state = state_node[0]
                    if next_state in visited_collection:
                        continue
                    if next_state == end:
                        return state_node[1]
                    next_que.append(state_node)
                    visited_collection.add(next_state)
            que = next_que
        raise ValueError("Can't solve.")

    start = "W" * N + "_" + "B" * N
    end = "B" * N + "_" + "W" * N
    last_move = bfs(start)
    move_collection_reversed = []
    while last_move.move != -1:
        move_collection_reversed.append(last_move.move + 1)
        last_move = last_move.prev
    move_collection = reversed(move_collection_reversed)
    while True:
        t = tuple(islice(move_collection, 20))
        if not t:
            break
        fprint(*t)


solve()
# Code end
