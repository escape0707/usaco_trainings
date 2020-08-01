"""
ID: totheso1
LANG: PYTHON3
TASK: barn1
"""
from itertools import islice

fin = open("barn1.in", "r")
fout = open("barn1.out", "w")


def fprint(*args, **kwargs) -> None:
    print(*args, file=fout, **kwargs)


# Code start
max_purchase, total_stall, total_cow = map(int, fin.readline().split())
occupied_stall = list(map(int, fin))
occupied_stall.sort()
gap_length_collection = [
    right - left - 1
    for left, right in zip(occupied_stall, islice(occupied_stall, 1, None))
]
gap_length_collection.sort()
fprint(total_cow + sum(islice(gap_length_collection, max(0, total_cow - max_purchase))))
# Code end
