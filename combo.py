"""
ID: totheso1
LANG: PYTHON3
TASK: combo
"""
from math import prod
from itertools import starmap

fin = open("combo.in", "r")
fout = open("combo.out", "w")


def fprint(*args, **kwargs) -> None:
    print(*args, file=fout, **kwargs)


# Code start
TOLERANCE = 2
TOLERANCE_SPAN = TOLERANCE * 2 + 1
DIALS_COUNT = 3

N = int(fin.readline())
john_combo = tuple(map(int, fin.readline().split()))
master_combo = tuple(map(int, fin.readline().split()))


def overlap(i: int, j: int) -> int:
    if N <= TOLERANCE_SPAN:
        return N
    if i > j:
        i, j = j, i
    return max(0, TOLERANCE_SPAN - min(j - i, i + N - j))


fprint(
    min(N, TOLERANCE_SPAN) ** DIALS_COUNT * 2
    - prod(starmap(overlap, zip(john_combo, master_combo)))
)
# Code end
