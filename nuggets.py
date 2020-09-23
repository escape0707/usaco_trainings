"""
ID: totheso1
LANG: PYTHON3
TASK: nuggets
NOTE:
    Just a classical Frobenius coin problem.
    Don't know why you are required to think up an algorithm by your own in a contest,
    because it's a NP-hard problem,
    and probably hard to find and prove a lower-bound,
    although it's not that hard to try to come up with an acceptable upper-bound.
    You can prove that for the N = 2 situation,
    the two numbers must be co-prime for a solution to exist.
    (Just associate this with Euclidean Greatest Common Divisor algorithm.)
    And the answer must be less than their Least Common Multiplyer doubled.
    (Actually the answer for N = 2 is A*B-A-B.)
    So you can do it with a simple Dynamic Programming, since the answer will be less than 2*255*256.

    Also, we can further optimize the `purchase_collection` to cut off it's memory usage,
    but I won't bother this time.
"""

from functools import reduce
from heapq import heappop, heappushpop
from math import gcd
from typing import Any

fin = open("nuggets.in", "r")
fout = open("nuggets.out", "w")


def fprint(*args: Any, **kwargs: Any) -> None:
    print(*args, file=fout, **kwargs)


# Code start
OPTION_COUNT = int(fin.readline())
option_colletion = tuple(map(int, fin))


def find_max_int_not_makeable() -> int:
    if reduce(gcd, option_colletion) != 1:
        return 0
    purchase_collection = [0]
    heap = [(option, option, -1) for option in sorted(option_colletion)]
    min_option = heap[0][0]
    max_consecutive_purchase = 0
    while True:  # heap will not be empty
        while heap[0][0] == purchase_collection[-1]:
            total, option, index = heap[0]
            if index == -1:
                heappop(heap)
                continue
            heappushpop(heap, (option + purchase_collection[index], option, index + 1))
        total, option, index = heap[0]
        purchase_collection.append(total)
        if total - purchase_collection[-2] == 1:
            max_consecutive_purchase += 1
            if max_consecutive_purchase == min_option:
                return purchase_collection[-max_consecutive_purchase] - 1
        else:
            max_consecutive_purchase = 1
        if index == -1:
            heappushpop(heap, (2 * option, option, len(purchase_collection)))
        else:
            heappushpop(heap, (option + purchase_collection[index], option, index + 1))


fprint(find_max_int_not_makeable())
# Code end
