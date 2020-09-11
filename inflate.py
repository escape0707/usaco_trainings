"""
ID: totheso1
LANG: PYTHON3
TASK: inflate
NOTE:
    Python3 will get Time Limit Exceeded.
    Please use C++, Java, Pascal instead.
"""

from typing import Any

fin = open("inflate.in", "r")
fout = open("inflate.out", "w")


def fprint(*args: Any, **kwargs: Any) -> None:
    print(*args, file=fout, **kwargs)


# Code start
TIME_TOTAL, CATEGORY_COUNT = map(int, fin.readline().split())
max_point = [0] * (TIME_TOTAL + 1)
for line in fin:
    point, minute = map(int, line.split())
    for i in range(minute, TIME_TOTAL + 1):
        max_point[i] = max(max_point[i], max_point[i - minute] + point)
fprint(max_point[-1])
# Code end
