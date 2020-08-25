"""
ID: totheso1
LANG: PYTHON3
TASK: hamming
"""

from itertools import islice
from typing import Any

fin = open("hamming.in", "r")
fout = open("hamming.out", "w")


def fprint(*args: Any, **kwargs: Any) -> None:
    print(*args, file=fout, **kwargs)


# Code start
def bitset_count(bitset: int) -> int:
    count = 0
    while bitset != 0:
        count += bitset & 1
        bitset >>= 1
    return count


CODEWORD_COUNT, LENGTH_OF_BITS, HAMMING_DISTANCE = map(int, fin.readline().split())
codeword_collection = [0]
for number in range(1, 1 << LENGTH_OF_BITS):
    if all(
        bitset_count(number ^ codeword) >= HAMMING_DISTANCE
        for codeword in codeword_collection
    ):
        codeword_collection.append(number)
        if len(codeword_collection) == CODEWORD_COUNT:
            break
for number in range(0, CODEWORD_COUNT, 10):
    fprint(*islice(codeword_collection, number, min(number + 10, CODEWORD_COUNT)))
# Code end
