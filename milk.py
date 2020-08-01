"""
ID: totheso1
LANG: PYTHON3
TASK: milk
"""
from typing import List

fin = open("milk.in", "r")
fout = open("milk.out", "w")


def fprint(*args, **kwargs) -> None:
    print(*args, file=fout, **kwargs)


# Code start
MAX_PRICE = 1000
N, M = map(int, fin.readline().split())

# quotation_collection = list(tuple(map(int, line.split())) for line in fin)
# quotation_collection.sort()

# cost = 0
# for quotation in quotation_collection:
#     buy_unit = min(quotation[1], N)
#     cost += buy_unit * quotation[0]
#     N -= buy_unit
#     if N == 0:
#         break
# fprint(cost)

count_by_cost: List[int] = [0] * (MAX_PRICE + 1)
for line in fin:
    unit_cost, unit_count = map(int, line.split())
    count_by_cost[unit_cost] += unit_count

total_cost = 0
for cost, count in enumerate(count_by_cost):
    buy_unit = min(count, N)
    total_cost += cost * buy_unit
    N -= buy_unit
    if N == 0:
        break
fprint(total_cost)


# Code end
