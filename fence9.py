"""
ID: totheso1
LANG: PYTHON3
TASK: fence9
"""

from math import ceil, floor, gcd
from typing import Any

fin = open("fence9.in", "r")
fout = open("fence9.out", "w")


def fprint(*args: Any, **kwargs: Any) -> None:
    print(*args, file=fout, **kwargs)


# Code start
X1, Y1, X2 = map(int, fin.readline().split())


def solve_O_N() -> None:
    fprint(
        sum(
            (ceil((X1 - X2) * y / Y1) + X2 - 1) - floor(X1 * y / Y1)
            for y in range(1, Y1)
        )
    )


# Pick's theorem: 2 * Area == 2 * Inside_Lattice_Count + Boundary_Lattice_Count - 2
# Lattice_Count_On_Line_Segment = 1 + gcd(abs(x1 - x2), abs(y1 - y2))
def solve_O_logN() -> None:
    boundary_lattice_count = gcd(X1, Y1) + gcd(abs(X2 - X1), Y1) + X2
    fprint((X2 * Y1 - boundary_lattice_count + 2) // 2)


solve_O_logN()
# Code end
