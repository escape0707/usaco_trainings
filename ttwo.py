"""
ID: totheso1
LANG: PYTHON3
TASK: ttwo
"""

from operator import add
from typing import Any, Tuple

fin = open("ttwo.in", "r")
fout = open("ttwo.out", "w")


def fprint(*args: Any, **kwargs: Any) -> None:
    print(*args, file=fout, **kwargs)


# Code start
EDGE_LENGTH = 10
DIRECTION_COUNT = 4
is_obstacle = [[True] * (EDGE_LENGTH + 2)]
direction_collection = ((-1, 0), (0, 1), (1, 0), (0, -1))


def next_state(state: Tuple[int, int, int]) -> Tuple[int, int, int]:
    i, j, direction = state
    new_i, new_j = map(add, (i, j), direction_collection[direction])
    if is_obstacle[new_i][new_j]:
        return i, j, (direction + 1) % DIRECTION_COUNT
    return new_i, new_j, direction


for i, line in enumerate(fin):
    row = [True]
    for j, c in enumerate(line.strip()):
        if c == "*":
            row.append(True)
        else:
            row.append(False)
            if c == "F":
                farmer = (i + 1, j + 1, 0)
            elif c == "C":
                cow = (i + 1, j + 1, 0)
    is_obstacle.append(row + [True])
is_obstacle.append([True] * (EDGE_LENGTH + 2))

ans = 0
for step in range(((EDGE_LENGTH * EDGE_LENGTH) * DIRECTION_COUNT) ** 2):
    fi, fj, fdir = farmer
    ci, cj, cdir = cow
    if (fi, fj) == (ci, cj):
        ans = step
        break
    farmer = next_state(farmer)
    cow = next_state(cow)

fprint(ans)
# Code end
