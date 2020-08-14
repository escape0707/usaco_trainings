"""
ID: totheso1
LANG: PYTHON3
TASK: pprime
NOTE:
    There are lots of ways to optimize this solution.
    See Analysis in USACO training site.
    Possible ways include use pure arithmetic to process palindrome,
    enumerate all first part and generate palindrome continuously,
    all even length palindrome can be divide by 11 so don't generate,
    use faster prime test, etc.
    But, I prefer my `next_palindrome` function way
    as it covers some more general problems,
    and this solution is fast enough.
    This also follows the KISS principle.
"""

from itertools import islice
from typing import Any
from math import sqrt, floor

fin = open("pprime.in", "r")
fout = open("pprime.out", "w")


def fprint(*args: Any, **kwargs: Any) -> None:
    print(*args, file=fout, **kwargs)


# Code start
def next_palindrome(num: int) -> int:
    s = str(num)
    if all(c == "9" for c in s):
        return num + 2
    length = len(s)
    half = (length + 1) // 2
    first_half = s[:half]
    last_half = s[-half:]
    first_half_reversed = first_half[::-1]
    if last_half >= first_half_reversed:
        first_half = str(int(first_half) + 1)
    res = first_half + "".join(islice(reversed(first_half), length & 1, None))
    return int(res)


def is_prime(num: int) -> bool:
    if num <= 1:
        return False
    return all(num % i != 0 for i in range(2, floor(sqrt(num)) + 1))


a, b = map(int, fin.readline().split())
palindrome = next_palindrome(a - 1)
while palindrome <= b:
    if is_prime(palindrome):
        fprint(palindrome)
    palindrome = next_palindrome(palindrome)
# Code end
