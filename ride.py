"""
ID: totheso1
LANG: PYTHON3
TASK: ride
"""

import functools
import itertools
import operator

fin = open("ride.in", "r")
fout = open("ride.out", "w")


def fprint(*args, **kwargs) -> None:
    print(*args, file=fout, **kwargs)


# Code start
def convert(name: str) -> int:
    return (
        functools.reduce(
            operator.mul,
            map(lambda c: ord(c) - 64, itertools.islice(name, len(name) - 1)),
        )
        % 47
    )


lines = fin.readlines()
fprint("GO" if convert(lines[0]) == convert(lines[1]) else "STAY")
# Code end
