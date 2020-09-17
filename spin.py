"""
ID: totheso1
LANG: PYTHON3
TASK: spin
"""

from itertools import count, islice
from typing import Any

fin = open("spin.in", "r")
fout = open("spin.out", "w")


def fprint(*args: Any, **kwargs: Any) -> None:
    print(*args, file=fout, **kwargs)


# Code start
wheel_collection = []


def initialize() -> None:
    for line in fin:
        int_iter = map(int, line.split())
        wheel_speed = next(int_iter)
        next(int_iter)
        opaque_collection = [True] * 360
        for start, extent in zip(int_iter, int_iter):
            for i in range(start, start + extent + 1):
                opaque_collection[i % 360] = False
        wheel_collection.append((wheel_speed, opaque_collection))


def solve() -> None:
    for time in range(360):
        overall_opaque_collection = [False] * 360
        for wheel_speed, wheel_opaque_collection in wheel_collection:
            for opaque, degree in zip(
                wheel_opaque_collection, count(time * wheel_speed)
            ):
                if opaque:
                    overall_opaque_collection[degree % 360] = True
        if not all(overall_opaque_collection):
            fprint(time)
            return
    fprint("none")


initialize()
solve()
# Code end
