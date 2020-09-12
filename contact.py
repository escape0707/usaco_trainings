"""
ID: totheso1
LANG: PYTHON3
TASK: contact
"""

from itertools import islice
from typing import Any, Counter

fin = open("contact.in", "r")
fout = open("contact.out", "w")


def fprint(*args: Any, **kwargs: Any) -> None:
    print(*args, file=fout, **kwargs)


# Code start
LOW, UP, OUTPUT_COUNT = map(int, fin.readline().split())


def solve() -> None:
    counter = Counter[int]()
    pattern_collection = [0] * 13
    bitmask_collection = tuple((1 << i) - 1 for i in range(13))
    ord_0 = ord("0")
    read_count = 0
    for line in fin:
        for c in islice(line, len(line) - 1):
            read_count += 1
            for i, pattern in enumerate(islice(pattern_collection, LOW, UP + 1), LOW):
                pattern = pattern << 1 & bitmask_collection[i] | 1 << i | ord(c) - ord_0
                if read_count >= i:
                    counter[pattern] += 1
                pattern_collection[i] = pattern

    record_collection = sorted(
        ((-count, pattern) for pattern, count in counter.items())
    )
    i = 0
    length = len(record_collection)
    for frequency_count in range(OUTPUT_COUNT):
        if i >= length:
            break
        count_opposite = record_collection[i][0]
        j = i + 1
        while j < length:
            if record_collection[j][0] != count_opposite:
                break
            j += 1
        fprint(-count_opposite)
        for start in range(i, j, 6):
            fprint(
                *(
                    f"{pattern:b}"[1:]
                    for _, pattern in islice(
                        record_collection, start, min(start + 6, j)
                    )
                )
            )
        i = j
        frequency_count += 1


solve()
# Code end
