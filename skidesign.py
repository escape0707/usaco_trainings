"""
ID: totheso1
LANG: PYTHON3
TASK: skidesign
"""

from typing import Any
from math import inf

fin = open("skidesign.in", "r")
fout = open("skidesign.out", "w")


def fprint(*args: Any, **kwargs: Any) -> None:
    print(*args, file=fout, **kwargs)


# Code start
hill_count = int(fin.readline())
hill_elevation_collection = tuple(map(int, fin))

min_payment = inf
for high in range(17, 101):
    low = high - 17
    payment = 0
    for hill_elevation in hill_elevation_collection:
        payment += max(0, hill_elevation - high, low - hill_elevation) ** 2
    if payment < min_payment:
        min_payment = payment

fprint(min_payment)
# Code end
