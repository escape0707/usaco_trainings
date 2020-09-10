"""
ID: totheso1
LANG: PYTHON3
TASK: fracdec
NOTE:
    It's worth noting that you could only spend O(1) storage
    if you know where the loop will begin.
    And you CAN know where the loop will begin by calculate
    the maximum of the difference between the power of 2 and 5
    in the numerator and denominator.
    We can then remember the first remainder
    and output each digit as we calculate them.
    (See that code in the official Analysis, please.
    I found I quickly lost my pashion for an adhoc-problem
    after I get Accepted using
    a rather intuitive algorithm of the same time complexity...)
"""

from itertools import count, islice
from typing import Any, Dict, List

fin = open("fracdec.in", "r")
fout = open("fracdec.out", "w")


def fprint(*args: Any, **kwargs: Any) -> None:
    print(*args, file=fout, **kwargs)


# Code start
numerator, denominator = map(int, fin.readline().split())


def solve() -> str:
    global numerator, denominator

    res = str(numerator // denominator)
    numerator %= denominator

    fraction_collection: List[int] = []
    remainder_collection: Dict[int, int] = {}
    for i in count():
        if numerator in remainder_collection:
            loop_start = remainder_collection[numerator]
            res += (
                "."
                + "".join(map(str, islice(fraction_collection, loop_start)))
                + "("
                + "".join(map(str, islice(fraction_collection, loop_start, None)))
                + ")"
            )
            break
        remainder_collection[numerator] = i
        numerator *= 10
        fraction_collection.append(numerator // denominator)
        numerator %= denominator
        if numerator == 0:
            res += "." + "".join(map(str, fraction_collection))
            break
    return res


ans = solve()
for i in range(0, len(ans), 76):
    fprint(ans[i : i + 76])
# Code end
