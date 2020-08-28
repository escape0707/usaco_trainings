"""
ID: totheso1
LANG: PYTHON3
TASK: runround
"""

from typing import Any, Set, List

fin = open("runround.in", "r")
fout = open("runround.out", "w")


def fprint(*args: Any, **kwargs: Any) -> None:
    print(*args, file=fout, **kwargs)


# Code start
def next_runround(M: int, length: int) -> int:
    digit_collection: List[int] = []
    digit_set: Set[int] = set()

    def check_runround() -> bool:
        i = (0 + digit_collection[0]) % length
        for cnt in range(1, length):
            if i == 0:
                return False
            i = (i + digit_collection[i]) % length
        return i == 0

    def convert_to_int() -> int:
        return int("".join(map(str, digit_collection)))

    def dfs(depth: int = 0) -> bool:
        if depth == length:
            return check_runround() and convert_to_int() > M
        for digit in range(1, 10):
            if digit in digit_set:
                continue
            digit_collection.append(digit)
            digit_set.add(digit)
            if dfs(depth + 1):
                return True
            digit_set.discard(digit)
            digit_collection.pop()
        return False

    if dfs():
        return convert_to_int()
    return 0


M = int(fin.readline())
b = 1
for length in range(1, 10):
    e = b * 10
    if e > M:
        res = next_runround(M, length)
        if res != 0:
            fprint(res)
            break
    b = e
# Code end
