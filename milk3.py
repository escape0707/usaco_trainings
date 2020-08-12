"""
ID: totheso1
LANG: PYTHON3
TASK: milk3
"""

from typing import Any

fin = open("milk3.in", "r")
fout = open("milk3.out", "w")


def fprint(*args: Any, **kwargs: Any) -> None:
    print(*args, file=fout, **kwargs)


# Code start
def dfs() -> None:
    a, b, c = milk
    if tried[a][b][c]:
        return
    tried[a][b][c] = True
    if a == 0:
        possibilities_collection[c] = True
    for from_bucket, from_milk in enumerate(milk):
        if from_milk > 0:
            for to_bucket, to_milk in enumerate(milk):
                to_available = CAPACITY_COLLECTION[to_bucket] - to_milk
                if to_available > 0:
                    transfer = min(from_milk, to_available)
                    milk[from_bucket] -= transfer
                    milk[to_bucket] += transfer
                    dfs()
                    milk[to_bucket] -= transfer
                    milk[from_bucket] += transfer


CAPACITY_COLLECTION = tuple(map(int, fin.readline().split()))
CAPACITY_A, CAPACITY_B, CAPACITY_C = CAPACITY_COLLECTION

tried = [
    [[False] * (CAPACITY_C + 1) for j in range(CAPACITY_B + 1)]
    for i in range(CAPACITY_A + 1)
]
possibilities_collection = [False] * (CAPACITY_C + 1)
milk = [0, 0, CAPACITY_C]
dfs()

fprint(*(liter for liter, possible in enumerate(possibilities_collection) if possible))
# Code end
