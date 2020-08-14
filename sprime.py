"""
ID: totheso1
LANG: PYTHON3
TASK: sprime
"""

from typing import Any
from math import floor, sqrt

fin = open("sprime.in", "r")
fout = open("sprime.out", "w")


def fprint(*args: Any, **kwargs: Any) -> None:
    print(*args, file=fout, **kwargs)


# Code start
def is_prime(num: int) -> bool:
    if num <= 1:
        return False
    return all(num % i != 0 for i in range(2, floor(sqrt(num)) + 1))


def dfs(num: int, need_to_append_count: int) -> None:
    if need_to_append_count == 0:
        fprint(num)
        return
    num *= 10
    for i in (1, 3, 7, 9):
        new_num = num + i
        if is_prime(new_num):
            dfs(new_num, need_to_append_count - 1)


N = int(fin.readline())
for begin_with in (2, 3, 5, 7):
    dfs(begin_with, N - 1)
# Code end
