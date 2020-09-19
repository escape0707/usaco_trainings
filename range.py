"""
ID: totheso1
LANG: PYTHON3
TASK: range
NOTE:
    Python3 will get Time Limit Exceeded.
    Use C++ / Java / Pascal instead.
"""

from itertools import islice
from typing import Any

fin = open("range.in", "r")
fout = open("range.out", "w")


def fprint(*args: Any, **kwargs: Any) -> None:
    print(*args, file=fout, **kwargs)


# Code start
SIDE_SIZE = int(fin.readline())
dp = [[c == "1" for c in islice(line, len(line) - 1)] for line in fin]
for square_side_size in range(2, SIDE_SIZE + 1):
    count = 0
    for i in range(SIDE_SIZE - square_side_size + 1):
        for j in range(SIDE_SIZE - square_side_size + 1):
            dp[i][j] = dp[i][j] and dp[i + 1][j] and dp[i][j + 1] and dp[i + 1][j + 1]
            count += dp[i][j]
    if count == 0:
        break
    fprint(square_side_size, count)
# Code end
