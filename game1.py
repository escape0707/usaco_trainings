"""
ID: totheso1
LANG: PYTHON3
TASK: game1
"""

from itertools import chain
from typing import Any

fin = open("game1.in", "r")
fout = open("game1.out", "w")


def fprint(*args: Any, **kwargs: Any) -> None:
    print(*args, file=fout, **kwargs)


# Code start
INT_COUNT = int(fin.readline())
int_collection = tuple(chain.from_iterable(map(int, line.split()) for line in fin))


def solve() -> None:
    dp = [(i, 0) for i in int_collection]
    for length in range(2, INT_COUNT + 1):
        for left in range(INT_COUNT - length + 1):
            right = left + length - 1
            dp[left] = max(
                (
                    int_collection[left] + dp[left + 1][1],
                    dp[left + 1][0],
                ),
                (
                    int_collection[right] + dp[left][1],
                    dp[left][0],
                ),
            )
    fprint(*dp[0])


solve()
# Code end
