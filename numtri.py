"""
ID: totheso1
LANG: PYTHON3
TASK: numtri
"""

from typing import Any, List

fin = open("numtri.in", "r")
fout = open("numtri.out", "w")


def fprint(*args: Any, **kwargs: Any) -> None:
    print(*args, file=fout, **kwargs)


# Code start
number_of_rows = int(fin.readline())
dp: List[int] = [0] * number_of_rows
for i, line in enumerate(fin):
    for j, num in zip(reversed(range(i + 1)), map(int, line.split())):
        dp[j] = max(dp[j], dp[j] + num)
        if j > 0:
            dp[j] = max(dp[j], dp[j - 1] + num)
fprint(max(dp))
# Code end
