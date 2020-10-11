"""
ID: totheso1
LANG: PYTHON3
TASK: milk4
"""

from __future__ import annotations

from dataclasses import dataclass
from itertools import count
from math import inf
from operator import itemgetter
from typing import Any, List, Tuple, cast

fin = open("milk4.in", "r")
fout = open("milk4.out", "w")


def fprint(*args: Any, **kwargs: Any) -> None:
    print(*args, file=fout, **kwargs)


# Code start
@dataclass
class TreeNode:
    value: int
    prev: TreeNode

    def __lt__(self, other: TreeNode) -> bool:
        if other is None:
            return False
        if self is None:
            return True
        if self.value < other.value:
            return True
        if self.prev is other.prev is None:
            return False
        return self.prev < other.prev


TARGET = int(fin.readline())
dp = [(0, cast(TreeNode, None))] + [(cast(int, inf), cast(TreeNode, None))] * TARGET


def solve() -> None:
    fin.readline()
    for pail_value in dict.fromkeys(sorted(map(int, fin), reverse=True)):
        including: List[Tuple[int, TreeNode]] = [
            (cast(int, inf), cast(TreeNode, None))
        ] * pail_value
        for i, prev in zip(range(pail_value, TARGET + 1), count()):
            new_tuple = (
                dp[prev][0] + 1,
                TreeNode(pail_value, dp[prev][1]),
            )
            including.append(min(including[prev], new_tuple))
        for i in range(pail_value, TARGET + 1):
            dp[i] = min(dp[i], including[i])

    fprint(dp[TARGET][0], end="")
    curr_node = dp[TARGET][1]
    while curr_node:
        fprint(f" {curr_node.value}", end="")
        curr_node = curr_node.prev
    fprint()


solve()
# Code end
