"""
ID: totheso1
LANG: PYTHON3
TASK: crypt1
"""
from typing import Tuple, Iterator, Iterable
from itertools import product
from functools import reduce

fin = open("crypt1.in", "r")
fout = open("crypt1.out", "w")


def fprint(*args, **kwargs) -> None:
    print(*args, file=fout, **kwargs)


# Code start
def digits_to_int(digits: Tuple[int, ...]) -> int:
    return reduce(lambda high, low: high * 10 + low, digits)


def digits_Cartesian_product(digit_set: Iterable[int], length: int) -> Tuple[int, ...]:
    return tuple(map(digits_to_int, product(digit_set, repeat=length)))


def digitize(number: int) -> Iterator[int]:
    while True:
        yield number % 10
        number //= 10
        if number == 0:
            return


N = int(fin.readline())
digit_set = set(map(int, fin.readline().split()))

multiplicand_collection = digits_Cartesian_product(digit_set, 3)
multiplier_collection = digits_Cartesian_product(digit_set, 2)

solution_count = 0


def valid(x: int) -> bool:
    return all(digit in digit_set for digit in digitize(x))


for multiplicand in multiplicand_collection:
    for multiplier in multiplier_collection:
        partial_product_1 = multiplicand * (multiplier % 10)
        if partial_product_1 < 1000 and valid(partial_product_1):
            partial_product_2 = multiplicand * (multiplier // 10)
            if partial_product_2 < 1000 and valid(partial_product_2):
                whole_product = multiplicand * multiplier
                if whole_product < 10000 and valid(whole_product):
                    solution_count += 1
fprint(solution_count)
# Code end
