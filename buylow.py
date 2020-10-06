"""
ID: totheso1
LANG: PYTHON3
TASK:buylow
NOTE:
    The first part of this problem is easy and has a O(NlogN) solution.
    But the second part forces us to add up all the possibility
    from each available prefix,
    thus we must use a O(N^2) solution for the second part.
    Python will get Time Limit Exceeded,
    although Python will handle bignumber for you automatically.
    Please use C++ etc. with a bignumber implementation instead.
"""

from itertools import chain, islice
from math import inf
from typing import Any, cast

fin = open("buylow.in", "r")
fout = open("buylow.out", "w")


def fprint(*args: Any, **kwargs: Any) -> None:
    print(*args, file=fout, **kwargs)


# Code start
NUMBER_COUNT = int(fin.readline())
number_collection = [cast(int, inf)] + list(
    chain.from_iterable(map(int, line.split()) for line in fin)
)


def solve() -> None:
    # longest_decreasing_sequence_including_current
    dp_length = [0] + [0] * NUMBER_COUNT
    # number_of_longest_sequence_ending_with_current_globally,
    dp_count = [1] + [0] * NUMBER_COUNT
    # if there exists a same element at j after current position i, we set
    # dp_count[i] to 0, and dp_count[j] will be the global sequence count for
    # this element
    for i, ai in enumerate(islice(number_collection, 1, None), start=1):
        # The following three for-loop can be integrated into a single one.
        # But spliting them up is easier to understand and debug.
        for j, aj in enumerate(islice(number_collection, i)):
            if aj > ai:
                dp_length[i] = max(dp_length[i], dp_length[j] + 1)
        for j, aj in enumerate(islice(number_collection, i)):
            if aj > ai and dp_length[j] + 1 == dp_length[i]:
                dp_count[i] += dp_count[j]
        for j, aj in enumerate(islice(number_collection, i)):
            if aj == ai:
                dp_count[j] = 0
    ans_length = max(dp_length)
    ans_count = sum(
        count for i, count in enumerate(dp_count) if dp_length[i] == ans_length
    )
    fprint(ans_length, ans_count)


solve()
# Code end
