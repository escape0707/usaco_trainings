"""
ID: totheso1
LANG: PYTHON3
TASK: preface
"""

from typing import Any, Counter

fin = open("preface.in", "r")
fout = open("preface.out", "w")


def fprint(*args: Any, **kwargs: Any) -> None:
    print(*args, file=fout, **kwargs)


# Code start
encode = ("I", "V", "X", "L", "C", "D", "M")
counter: Counter[str] = Counter()
TOTAL_PAGES = int(fin.readline())
for i in range(1, TOTAL_PAGES + 1):
    num = i
    order = -2
    while num != 0:
        order += 2
        digit = num % 10
        num //= 10
        if digit == 9:
            counter[encode[order]] += 1
            counter[encode[order + 2]] += 1
            continue
        if digit == 4:
            counter[encode[order + 1]] += 1
            counter[encode[order]] += 1
            continue
        if digit >= 5:
            counter[encode[order + 1]] += 1
            digit -= 5
        counter[encode[order]] += digit
for c, cnt in zip(encode, map(counter.get, encode)):
    if cnt:
        fprint(c, cnt)
# Code end
