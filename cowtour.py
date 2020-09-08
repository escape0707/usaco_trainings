"""
ID: totheso1
LANG: PYTHON3
TASK: cowtour
NOTE:
    I have optimize the time constant of my solution down half to get an Accepted.
"""

from itertools import islice
from math import inf, sqrt
from typing import Any, Iterable, List, Tuple, cast

fin = open("cowtour.in", "r")
fout = open("cowtour.out", "w")


def fprint(*args: Any, **kwargs: Any) -> None:
    print(*args, file=fout, **kwargs)


# Code start
PASTURE_COUNT = int(fin.readline())
coordinate: List[Tuple[int, int]] = []
shortest = [
    [0.0 if i == j else inf for j in range(PASTURE_COUNT)] for i in range(PASTURE_COUNT)
]
belong = [i for i in range(PASTURE_COUNT)]
set_size = [1 for _ in range(PASTURE_COUNT)]
farthest = [0.0 for _ in range(PASTURE_COUNT)]
diameter = [0.0 for _ in range(PASTURE_COUNT)]


def find(i: int) -> int:
    while belong[i] != i:
        belong[i] = i = belong[belong[i]]
    return i


def union(i: int, j: int) -> None:
    i = find(i)
    j = find(j)
    if i == j:
        return
    if set_size[i] < set_size[j]:
        i, j = j, i
    belong[j] = i
    set_size[i] += set_size[j]


def distance(i: int, j: int) -> float:
    def euclidean_distance(v1: Iterable[Any], v2: Iterable[Any]) -> float:
        return sqrt(sum((a - b) ** 2 for a, b in zip(v1, v2)))

    return euclidean_distance(coordinate[i], coordinate[j])


def initialize() -> None:
    for _ in range(PASTURE_COUNT):
        coordinate.append(
            cast(Tuple[int, int], tuple(map(int, fin.readline().split())))
        )
    for i, line in enumerate(fin):
        for j, c in enumerate(islice(line, i)):
            if c == "1":
                union(i, j)
                shortest[i][j] = shortest[j][i] = distance(i, j)


def solve() -> None:
    for k in range(PASTURE_COUNT):
        for i in range(PASTURE_COUNT):
            for j in range(i):
                # if inf in (shortest[i][k], shortest[k][j]):
                #     continue
                shortest[i][j] = shortest[j][i] = min(
                    shortest[i][j], shortest[i][k] + shortest[k][j]
                )

    for i in range(PASTURE_COUNT):
        for j in range(PASTURE_COUNT):
            if shortest[i][j] != inf:
                farthest[i] = max(farthest[i], shortest[i][j])

    for i in range(PASTURE_COUNT):
        set_id = find(i)
        diameter[set_id] = max(diameter[set_id], farthest[i])

    ans = inf
    for i in range(PASTURE_COUNT):
        for j in range(i):
            set_i, set_j = find(i), find(j)
            if set_i != set_j:
                ans = min(
                    ans,
                    max(
                        diameter[set_i],
                        diameter[set_j],
                        farthest[i] + distance(i, j) + farthest[j],
                    ),
                )
    fprint(f"{ans:.6f}")


initialize()
solve()
# Code end
