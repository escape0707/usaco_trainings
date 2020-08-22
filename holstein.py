"""
ID: totheso1
LANG: PYTHON3
TASK: holstein
"""

from typing import Any
from collections import deque
from operator import add, ge

fin = open("holstein.in", "r")
fout = open("holstein.out", "w")


def fprint(*args: Any, **kwargs: Any) -> None:
    print(*args, file=fout, **kwargs)


# Code start
def print_feed_bitset(feed_bitset: int) -> None:
    count = 0
    feed_type_collection = []
    current_feed_type = 0
    while feed_bitset != 0:
        current_feed_type += 1
        if feed_bitset & 1 == 1:
            count += 1
            feed_type_collection.append(current_feed_type)
        feed_bitset >>= 1
    fprint(count, *feed_type_collection)


def solve_feed() -> None:
    que = deque(((0, 0, (0,) * VITAMIN_COUNT),))
    while que:
        next_feed_id, feed_bitset, vitamin_collection = que.popleft()
        for feed_id in range(next_feed_id, FEED_COUNT):
            new_feed_bitset = feed_bitset | (1 << feed_id)
            new_vitamin_collection = tuple(
                map(add, vitamin_collection, ingredient_table_collection[feed_id])
            )
            if all(map(ge, new_vitamin_collection, requirement_collection)):
                print_feed_bitset(new_feed_bitset)
                return
            que.append((feed_id + 1, new_feed_bitset, new_vitamin_collection))


VITAMIN_COUNT = int(fin.readline())
requirement_collection = tuple(map(int, fin.readline().split()))
FEED_COUNT = int(fin.readline())
ingredient_table_collection = tuple(tuple(map(int, line.split())) for line in fin)
solve_feed()
# Code end
