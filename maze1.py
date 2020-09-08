"""
ID: totheso1
LANG: PYTHON3
TASK: maze1
"""

from itertools import islice
from typing import Any

fin = open("maze1.in", "r")
fout = open("maze1.out", "w")


def fprint(*args: Any, **kwargs: Any) -> None:
    print(*args, file=fout, **kwargs)


# Code start
WIDTH, HEIGHT = map(int, fin.readline().split())
available = [[True] * (WIDTH * 2 + 1) for _ in range(HEIGHT * 2 + 1)]
start = []


def initialize() -> None:
    for i, line in enumerate(fin):
        for j, c in enumerate(islice(line, len(line) - 1)):
            if (i in (0, HEIGHT * 2) or j in (0, WIDTH * 2)) and c == " ":
                start.append((i, j))
                available[i][j] = False
            else:
                available[i][j] = c == " "


def bfs() -> int:
    direction_collection = ((-1, 0), (0, 1), (1, 0), (0, -1))

    que = start[:]
    step_doubled = 0
    while que:
        step_doubled += 1
        que_next = []
        for i, j in que:
            for di, dj in direction_collection:
                new_i, new_j = i + di, j + dj
                if 0 < new_i < HEIGHT * 2 and 0 < new_j < WIDTH * 2:
                    if available[new_i][new_j]:
                        que_next.append((new_i, new_j))
                        available[new_i][new_j] = False
        que = que_next
    return step_doubled // 2


initialize()
fprint(bfs())
# Code end
