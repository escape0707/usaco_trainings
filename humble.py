"""
ID: totheso1
LANG: PYTHON3
TASK: humble
NOTE:
    Python3 will get Time Limit Exceeded,
    meanwhile C++ can get Accepted in
    TWO DIFFERENT STYYYYYLE!!!
    (Speechless...
"""

from math import inf
from itertools import islice
from typing import Any, cast

fin = open("humble.in", "r")
fout = open("humble.out", "w")


def fprint(*args: Any, **kwargs: Any) -> None:
    print(*args, file=fout, **kwargs)


# Code start
PRIME_COUNT, ANSWER_ORDER = map(int, fin.readline().split())
prime_collection = tuple(map(int, fin.readline().split()))


def solve_with_greedy() -> None:
    humble_collection = [1]
    try_index_collection = [0] * PRIME_COUNT
    for humble_count in range(ANSWER_ORDER):
        min_product = cast(int, inf)
        last_humble_number = humble_collection[-1]
        for i, (prime, try_index) in enumerate(
            zip(prime_collection, try_index_collection)
        ):
            for j, humble_number in enumerate(
                islice(humble_collection, try_index, None), try_index
            ):
                product = prime * humble_number
                if product > last_humble_number:
                    try_index_collection[i] = j
                    min_product = min(min_product, product)
                    break
        humble_collection.append(min_product)
    fprint(humble_collection[-1])


solve_with_greedy()
# Code end
