"""
ID: totheso1
LANG: PYTHON3
TASK: fact4
"""

from typing import Any

fin = open("fact4.in", "r")
fout = open("fact4.out", "w")


def fprint(*args: Any, **kwargs: Any) -> None:
    print(*args, file=fout, **kwargs)


# Code start
N = int(fin.readline())
ans = 1
cnt_2, cnt_5 = 0, 0
for i in range(2, N + 1):
    j = i
    while j % 2 == 0:
        cnt_2 += 1
        j //= 2
    while j % 5 == 0:
        cnt_5 += 1
        j //= 5
    ans = ans * j % 10

for i in range(cnt_2 - cnt_5):
    ans = ans * 2 % 10
fprint(ans)
# Code end
