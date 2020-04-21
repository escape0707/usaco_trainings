"""
ID: totheso1
LANG: PYTHON3
TASK: palsquare
"""
import operator
import itertools

fin = open("palsquare.in", "r")
fout = open("palsquare.out", "w")


def fprint(*args, **kwargs):
    print(*args, file=fout, **kwargs)


# Code start
digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"


def base_repr(number: int, base: int = 2, padding: int = 0) -> str:
    # if base > len(digits):
    #     raise ValueError("Bases greater than 36 not handled in base_repr.")
    # elif base < 2:
    #     raise ValueError("Bases less than 2 not handled in base_repr.")

    num = abs(number)
    res = []
    while num:
        res.append(digits[num % base])
        num //= base
    if padding:
        res.append("0" * padding)
    if number < 0:
        res.append("-")
    return "".join(reversed(res or "0"))


BASE = int(fin.read())
for num in range(1, 301):
    square = base_repr(num * num, BASE)
    if all(map(operator.eq, itertools.islice(square, len(square) >> 1), reversed(square))):
        fprint(base_repr(num, BASE), square)
# Code end
