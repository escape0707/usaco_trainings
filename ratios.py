"""
ID: totheso1
LANG: PYTHON3
TASK: ratios
"""

from typing import Any, Tuple

fin = open("ratios.in", "r")
fout = open("ratios.out", "w")


def fprint(*args: Any, **kwargs: Any) -> None:
    print(*args, file=fout, **kwargs)


# Code start
goal = tuple(map(int, fin.readline().split()))
mixture_collection = tuple(tuple(map(int, fin.readline().split())) for _ in range(3))


def validate(vector_x: Tuple[int, int, int]) -> int:
    prev_k = -1
    for component_id in range(3):
        inner_product = 0
        for mixture_id in range(3):
            inner_product += (
                mixture_collection[mixture_id][component_id] * vector_x[mixture_id]
            )
        if goal[component_id] == 0:
            if inner_product != 0:
                return 0
        else:
            remainder = inner_product % goal[component_id]
            k = inner_product // goal[component_id]
            if remainder != 0 or k != prev_k and prev_k != -1:
                return 0
            prev_k = k
    return prev_k


def solve() -> None:
    for x1 in range(100):
        for x2 in range(100):
            for x3 in range(100):
                k = validate((x1, x2, x3))
                if k != 0:
                    fprint(x1, x2, x3, k)
                    return
    fprint("NONE")


solve()
# Code end
