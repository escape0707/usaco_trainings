"""
ID: totheso1
LANG: PYTHON3
TASK: subset
"""

from typing import Any

fin = open("subset.in", "r")
fout = open("subset.out", "w")


def fprint(*args: Any, **kwargs: Any) -> None:
    print(*args, file=fout, **kwargs)


# Code start
NUMBER_COUNT = int(fin.readline())
TOTAL = (1 + NUMBER_COUNT) * NUMBER_COUNT // 2
if TOTAL & 1 == 1:
    fprint(0)
else:
    HALF_TOTAL = TOTAL // 2
    cnt = [1] + [0] * HALF_TOTAL
    for number in range(1, NUMBER_COUNT + 1):
        for total in range(min(HALF_TOTAL, (1 + number) * number // 2), number - 1, -1):
            cnt[total] += cnt[total - number]
    fprint(cnt[HALF_TOTAL] // 2)
# Code end
