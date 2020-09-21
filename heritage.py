"""
ID: totheso1
LANG: PYTHON3
TASK: heritage
"""

from __future__ import annotations

from dataclasses import dataclass
from itertools import islice
from typing import Any, Optional

fin = open("heritage.in", "r")
fout = open("heritage.out", "w")


def fprint(*args: Any, **kwargs: Any) -> None:
    print(*args, file=fout, **kwargs)


# Code start
in_order = fin.readline().strip()
pre_order = fin.readline().strip()


def solve() -> None:
    def print_post_order_recursive(
        in_l: int, in_r: int, pre_l: int, pre_r: int
    ) -> None:
        if in_l == in_r and pre_l == pre_r:
            return
        root_in = in_order.find(pre_order[pre_l], in_l, in_r)
        right_pre = pre_l + root_in - in_l + 1
        print_post_order_recursive(in_l, root_in, pre_l + 1, right_pre)
        print_post_order_recursive(root_in + 1, in_r, right_pre, pre_r)
        fprint(pre_order[pre_l], end="")

    print_post_order_recursive(0, len(in_order), 0, len(pre_order))
    fprint()


solve()
# Code end
