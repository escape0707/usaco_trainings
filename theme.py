"""
ID: totheso1
LANG: PYTHON3
TASK: theme
NOTE:
    My Python solution get TLE, C++ get AC.
    Not gonna spend time investigate this now.
"""

from itertools import chain, islice
from typing import Any

fin = open("theme.in", "r")
fout = open("theme.out", "w")


def fprint(*args: Any, **kwargs: Any) -> None:
    print(*args, file=fout, **kwargs)


# Code start
NOTE_COUNT = int(fin.readline())
arr = list(chain.from_iterable(map(int, line.split()) for line in fin))


def initialize() -> None:
    for i, (a, b) in enumerate(zip(arr, islice(arr, 1, None))):
        arr[i] = b - a


def solve() -> None:
    ans = 0
    for offset in range(len(arr)):
        same_count = 0
        for i in range(len(arr) - offset):
            if arr[i] == arr[i + offset]:
                same_count += 1
                if offset <= same_count:
                    break
                ans = max(ans, same_count)
            else:
                same_count = 0
    fprint(ans + 1 if ans >= 4 else 0)


initialize()
solve()
# Code end
