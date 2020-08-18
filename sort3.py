"""
ID: totheso1
LANG: PYTHON3
TASK: sort3
"""

from typing import Any, Counter, List
from itertools import islice

fin = open("sort3.in", "r")
fout = open("sort3.out", "w")


def fprint(*args: Any, **kwargs: Any) -> None:
    print(*args, file=fout, **kwargs)


# Code start
MAX_NUMBER = int(fin.readline())
number_collection = tuple(map(int, fin))
number_counter = Counter(number_collection)
section_counter_collection: List[Counter[int]] = [Counter()]
b = 0
e = b
for i in range(1, 4):
    e += number_counter[i]
    section_counter_collection.append(Counter(islice(number_collection, b, e)))
    b += number_counter[i]
answer = 0
for i in range(1, 4):
    for j in range(1, i):
        answer += min(
            section_counter_collection[i][j], section_counter_collection[j][i]
        )
answer += 2 * (
    max(section_counter_collection[1][2], section_counter_collection[2][1])
    - min(section_counter_collection[1][2], section_counter_collection[2][1])
)
fprint(answer)
# Code end
