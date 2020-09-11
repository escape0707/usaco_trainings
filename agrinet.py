"""
ID: totheso1
LANG: PYTHON3
TASK: agrinet
"""

from math import inf
from typing import Any, List, cast

fin = open("agrinet.in", "r")
fout = open("agrinet.out", "w")


def fprint(*args: Any, **kwargs: Any) -> None:
    print(*args, file=fout, **kwargs)


# Code start
FARM_COUNT = int(fin.readline())
distance = []
for i in range(FARM_COUNT):
    curr: List[int] = []
    while len(curr) != FARM_COUNT:
        curr.extend(map(int, fin.readline().split()))
    distance.append(curr)

closest = [0] + [cast(int, inf)] * (FARM_COUNT - 1)
in_tree = [False] * FARM_COUNT
ans = 0
for tree_size in range(FARM_COUNT):
    i, dist_i = min(
        enumerate(closest),
        key=lambda i_dist: inf if in_tree[i_dist[0]] else i_dist[1],
    )
    ans += dist_i
    in_tree[i] = True
    for j, (dist_j, dist_ij) in enumerate(zip(closest, distance[i])):
        closest[j] = min(dist_j, dist_ij)
fprint(ans)
# Code end
