"""
ID: totheso1
LANG: PYTHON3
TASK: concom
NOTE:
    I find this solution in USACO analysis is more complex
    and harder to prove and debug.
    It isn't necessarily faster than
    the "read all and find all" method below, too.
    So I'll stick with my method for now.
"""

from typing import Any

fin = open("concom.in", "r")
fout = open("concom.out", "w")


def fprint(*args: Any, **kwargs: Any) -> None:
    print(*args, file=fout, **kwargs)


# Code start
MAX_COMPANY = 100
own = [[0] * MAX_COMPANY for _ in range(MAX_COMPANY)]
control = [[False] * MAX_COMPANY for _ in range(MAX_COMPANY)]
for i in range(MAX_COMPANY):
    control[i][i] = True


def add_control(i: int, j: int) -> None:
    if control[i][j]:
        return
    control[i][j] = True
    for k in range(MAX_COMPANY):
        own[i][k] += own[j][k]
    for k in range(MAX_COMPANY):
        if control[k][i]:
            add_control(k, j)
    # I don't understand why this third loop
    # can't be placed before the second loop,
    # or combined in the first loop.
    for k in range(MAX_COMPANY):
        if own[i][k] > 50:
            add_control(i, k)


def add_own(i: int, j: int, percentage: int) -> None:
    for k in range(MAX_COMPANY):
        if control[k][i]:
            own[k][j] += percentage
            if own[k][j] > 50:
                add_control(k, j)


fin.readline()
for line in fin:
    i, j, percentage = map(int, line.split())
    # add_own(i - 1, j - 1, percentage)
    own[i - 1][j - 1] = percentage

for root in range(MAX_COMPANY):
    stack = [root]
    total_percentage = [[0] * MAX_COMPANY for _ in range(MAX_COMPANY)]
    while stack:
        curr = stack.pop()
        for other in range(MAX_COMPANY):
            if not control[root][other]:
                total_percentage[root][other] += own[curr][other]
                if total_percentage[root][other] > 50:
                    control[root][other] = True
                    stack.append(other)

for i, row in enumerate(control):
    for j, is_controlling in enumerate(row):
        if is_controlling and i != j:
            fprint(i + 1, j + 1)
# Code end
