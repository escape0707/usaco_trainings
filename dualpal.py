"""
ID: totheso1
LANG: PYTHON3
TASK: dualpal
NOTE: Actually, there exists a faster algorithm, which construct every palindrome for each base for small ones to larger ones, and use heap to track the least two of them to see if they are equal. But it might not worth to be implemented.
"""
from typing import List
from itertools import islice

fin = open("dualpal.in", "r")
fout = open("dualpal.out", "w")


def fprint(*args, **kwargs) -> None:
    print(*args, file=fout, **kwargs)


# Code start
def base10_to_baseN(number: int, base: int) -> List[int]:
    # if not 2 <= base <= 10:
    #     raise ValueError("Convertion base should settle between 2 to 10 inclusively.")
    res = []
    while number:
        res.append(number % base)
        number //= base
    return res


def is_pal(digits: List[int]) -> bool:
    return all(
        left == right
        for left, right in zip(
            islice(digits, len(digits) // 2), islice(reversed(digits), len(digits) // 2)
        )
    )


def check_dual_pal(number: int) -> bool:
    return sum(is_pal(base10_to_baseN(number, base)) for base in range(2, 11)) >= 2


N, S = map(int, fin.read().split())

S += 1
while N != 0:
    if check_dual_pal(S):
        fprint(S)
        N -= 1
    S += 1
# Code end
