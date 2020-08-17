"""
ID: totheso1
LANG: PYTHON3
TASK: frac1
"""

from functools import cmp_to_key
from math import gcd
from typing import Any, Tuple

fin = open("frac1.in", "r")
fout = open("frac1.out", "w")


def fprint(*args: Any, **kwargs: Any) -> None:
    print(*args, file=fout, **kwargs)


# Code start
def fraction_less(p1: Tuple[int, int], p2: Tuple[int, int]) -> int:
    return p1[0] * p2[1] - p2[0] * p1[1]


MAX_DENOMINATOR = int(fin.readline())
fraction_collection = [
    (numerator, denominator)
    for denominator in range(1, MAX_DENOMINATOR + 1)
    for numerator in range(denominator + 1)
    if gcd(numerator, denominator) == 1
]
fraction_collection.sort(key=cmp_to_key(fraction_less))
for numerator, denominator in fraction_collection:
    fprint(f"{numerator}/{denominator}")
# Code end
