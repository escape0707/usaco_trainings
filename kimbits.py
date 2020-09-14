"""
ID: totheso1
LANG: PYTHON3
TASK: kimbits
"""

from typing import Any

fin = open("kimbits.in", "r")
fout = open("kimbits.out", "w")


def fprint(*args: Any, **kwargs: Any) -> None:
    print(*args, file=fout, **kwargs)


# Code start
LENGTH, MAX_BIT_COUNT, RANK = map(int, fin.readline().split())
count_collection = [[1] * (MAX_BIT_COUNT + 1) for _ in range(LENGTH + 1)]


def initialize() -> None:
    for length in range(1, LENGTH + 1):
        for max_bit_count in range(1, MAX_BIT_COUNT + 1):
            count_collection[length][max_bit_count] = (
                count_collection[length - 1][max_bit_count]
                + count_collection[length - 1][max_bit_count - 1]
            )


def print_bits(length: int, max_bit_count: int, rank: int) -> None:
    while length > 0:
        tmp = count_collection[length - 1][max_bit_count]
        if rank <= tmp:
            fprint(0, end="")
        else:
            fprint(1, end="")
            max_bit_count -= 1
            rank -= tmp
        length -= 1
    fprint()


initialize()
print_bits(LENGTH, MAX_BIT_COUNT, RANK)
# Code end
