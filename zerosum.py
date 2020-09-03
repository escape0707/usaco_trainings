"""
ID: totheso1
LANG: PYTHON3
TASK: zerosum
"""

from itertools import count
from typing import Any, List

fin = open("zerosum.in", "r")
fout = open("zerosum.out", "w")


def fprint(*args: Any, **kwargs: Any) -> None:
    print(*args, file=fout, **kwargs)


# Code start
def generate(i: int) -> List[int]:
    res = []
    for j in range(N - 1):
        res.append(i % 3)
        i //= 3
    return res


def sum_to_zero(N: int, sequence: List[int]) -> bool:
    total = 0
    current_term = 1
    sign = 1
    for digit, opt_id in zip(count(2), reversed(sequence)):
        if opt_id == 0:  # ' '
            current_term = current_term * 10 + digit
        else:
            total += sign * current_term
            current_term = digit
            sign = 1 if opt_id == 1 else -1
    return total + sign * current_term == 0


def output(N: int, sequence: List[int]) -> None:
    opt_table = " +-"
    for digit, opt_id in zip(count(1), reversed(sequence)):
        fprint(f"{digit}{opt_table[opt_id]}", end="")
    fprint(N)


N = int(fin.readline())
possibility_count = 3 ** (N - 1)
for i in range(possibility_count):
    sequence = generate(i)
    if sum_to_zero(N, sequence):
        output(N, sequence)
# Code end
