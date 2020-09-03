"""
ID: totheso1
LANG: PYTHON3
TASK: money
"""

from typing import Any
from itertools import chain

fin = open("money.in", "r")
fout = open("money.out", "w")


def fprint(*args: Any, **kwargs: Any) -> None:
    print(*args, file=fout, **kwargs)


# Code start
COIN_COUNT, TARGET = map(int, fin.readline().split())
count_collection = [1] + [0] * TARGET
coin_collection = tuple(chain.from_iterable(map(int, line.split()) for line in fin))
for coin in coin_collection:
    for i in range(TARGET + 1):
        if coin <= i:
            count_collection[i] += count_collection[i - coin]
fprint(count_collection[TARGET])
# Code end
