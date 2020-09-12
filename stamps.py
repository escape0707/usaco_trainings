"""
ID: totheso1
LANG: PYTHON3
TASK: stamps
NOTE:
    Python3 will get Time Limit Exceeded, use C++ / Java / Pascal instead.
"""

from collections import deque
from itertools import chain, count
from typing import Any

fin = open("stamps.in", "r")
fout = open("stamps.out", "w")


def fprint(*args: Any, **kwargs: Any) -> None:
    print(*args, file=fout, **kwargs)


# Code start
STAMP_TOTAL, STAMP_TYPE_COUNT = map(int, fin.readline().split())
value_collection = tuple(chain.from_iterable(map(int, line.split()) for line in fin))


def solve() -> None:
    stamp_needed_collection = deque((0,), max(value_collection))
    for i in count(1):
        min_needed = STAMP_TOTAL + 1
        for value in value_collection:
            if value <= i:
                min_needed = min(min_needed, stamp_needed_collection[-value] + 1)
        if min_needed == STAMP_TOTAL + 1:
            fprint(i - 1)
            break
        stamp_needed_collection.append(min_needed)


solve()
# Code end
