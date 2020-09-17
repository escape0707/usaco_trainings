"""
ID: totheso1
LANG: PYTHON3
TASK: shopping
"""

from itertools import islice
from math import inf
from typing import Any, Tuple, cast

fin = open("shopping.in", "r")
fout = open("shopping.out", "w")


def fprint(*args: Any, **kwargs: Any) -> None:
    print(*args, file=fout, **kwargs)


# Code start
OFFER_COUNT: int
offer_collection = []
REQUIREMENT_COUNT: int
product_collection: Tuple[Tuple[int, int, int], ...]


def initialize() -> None:
    global OFFER_COUNT
    global offer_collection
    global REQUIREMENT_COUNT
    global product_collection

    OFFER_COUNT = int(fin.readline())
    for line in islice(fin, OFFER_COUNT):
        int_iter = map(int, line.split())
        offer_size = next(int_iter)
        offer_content = {
            product_code: product_count
            for product_code, product_count in islice(
                zip(int_iter, int_iter), offer_size
            )
        }
        reduced_price = next(int_iter)
        offer_collection.append((offer_content, reduced_price))

    REQUIREMENT_COUNT = int(fin.readline())
    product_collection = tuple(
        cast(Tuple[int, int, int], tuple(map(int, line.split()))) for line in fin
    )


def solve() -> None:
    def less_equal(state_a: int, state_b: int) -> bool:
        while state_a or state_b:
            if state_a % 6 > state_b % 6:
                return False
            state_a //= 6
            state_b //= 6
        return True

    power_6_collection = (1, 6, 36, 216, 1296, 7776)

    power_6_by_product_code_collection = {}
    for power_6, (product_code, _, regular_price) in zip(
        power_6_collection, product_collection
    ):
        power_6_by_product_code_collection[product_code] = power_6
        offer_collection.append(({product_code: 1}, regular_price))

    STATE_COUNT = power_6_collection[5]
    dp = [0] + [cast(int, inf)] * (STATE_COUNT - 1)
    for offer_content, price in offer_collection:
        min_state = 0
        for product_code, product_count in offer_content.items():
            if product_code not in power_6_by_product_code_collection:
                break
            min_state += (
                power_6_by_product_code_collection[product_code] * product_count
            )
        else:
            for state in range(STATE_COUNT):
                if less_equal(min_state, state):
                    dp[state] = min(dp[state], dp[state - min_state] + price)

    target_state = 0
    for power_6, (_, requirement, _) in zip(power_6_collection, product_collection):
        target_state += power_6 * requirement
    fprint(dp[target_state])


initialize()
solve()
# Code end
