"""
ID: totheso1
LANG: PYTHON3
TASK: comehome
NOTE:
    The graph according to the problem is too dense.
    So using a heap optimization on Dijkstra algorithm is not necessary.
"""

from itertools import islice
from math import inf
from typing import Any, cast, Tuple

fin = open("comehome.in", "r")
fout = open("comehome.out", "w")


def fprint(*args: Any, **kwargs: Any) -> None:
    print(*args, file=fout, **kwargs)


# Code start
PASTURE_COUNT = 26
PATH_COUNT = int(fin.readline())
shortest = [
    [0 if i == j else cast(int, inf) for j in range(PASTURE_COUNT * 2)]
    for i in range(PASTURE_COUNT * 2)
]
ord_A = ord("A")


def initialize() -> None:
    for line in fin:
        a_str, b_str, dist_str = line.split()
        a, b = (
            ord(c.upper()) - ord_A + int(c.isupper()) * PASTURE_COUNT
            for c in (a_str, b_str)
        )
        dist = int(dist_str)
        shortest[a][b] = shortest[b][a] = min(shortest[a][b], dist)


def solve_with_floyd_warshell() -> Tuple[str, int]:
    for k in range(PASTURE_COUNT * 2):
        for i in range(PASTURE_COUNT * 2):
            for j in range(i):
                shortest[i][j] = shortest[j][i] = min(
                    shortest[i][j], shortest[i][k] + shortest[k][j]
                )

    who: int
    ans = cast(int, inf)
    for i, dist in enumerate(
        islice(shortest[-1], PASTURE_COUNT, PASTURE_COUNT * 2 - 1)
    ):
        if dist < ans:
            who, ans = i, dist
    return chr(who + ord_A), ans


def solve_with_basic_dijkstra() -> Tuple[str, int]:
    visited = [False] * PASTURE_COUNT * 2
    for visited_count in range(PASTURE_COUNT * 2):
        i, dist_si = min(
            enumerate(shortest[-1]),
            key=lambda i_dist: inf if visited[i_dist[0]] else i_dist[1],
        )
        if PASTURE_COUNT <= i < PASTURE_COUNT * 2 - 1:
            return chr(i - PASTURE_COUNT + ord_A), dist_si
        visited[i] = True
        for j, dist_ij in enumerate(shortest[i]):
            shortest[-1][j] = min(shortest[-1][j], dist_si + dist_ij)
    raise ValueError("No cow can reach barn.")


initialize()
who, ans = solve_with_basic_dijkstra()
fprint(who, ans)
# Code end
