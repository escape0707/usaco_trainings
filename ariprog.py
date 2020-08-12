"""
ID: totheso1
LANG: PYTHON3
TASK: ariprog
NOTE:
    This task can't be done in python in time limit. Use C++14 instead.
    The following program is correct,
    but will take about 10 seconds and get TLE when M is 250.
"""

from time import time

start_time = time()

from itertools import islice
from typing import Any, List

fin = open("ariprog.in", "r")
fout = open("ariprog.out", "w")


def fprint(*args: Any, **kwargs: Any) -> None:
    print(*args, file=fout, **kwargs)


# Code start
LENGTH_OF_PROGRESSION = int(fin.readline())
MAX_FACTOR = int(fin.readline())
MAX_NUMBER = MAX_FACTOR * MAX_FACTOR * 2

available = [False] * (MAX_NUMBER + 1)
number_collection: List[int] = []
for i in range(MAX_FACTOR + 1):
    for j in range(i + 1):
        number = i * i + j * j
        if not available[number]:
            available[number] = True
            number_collection.append(number)
number_collection.sort()

back = number_collection[-1]
result = []
for i, num_a in enumerate(number_collection):
    for j, num_b in enumerate(islice(number_collection, i + 1, None)):
        diff = num_b - num_a
        last_num = num_a + diff * (LENGTH_OF_PROGRESSION - 1)
        if back < last_num:
            break
        for next_num in range(num_b + diff, last_num + 1, diff):
            if not available[next_num]:
                break
        else:
            result.append((diff, num_a))
result.sort()

if not result:
    fprint("NONE")
else:
    for diff, num_a in result:
        fout.write(f"{num_a} {diff}\n")
# Code end
print(time() - start_time)
