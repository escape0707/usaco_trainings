"""
ID: totheso1
LANG: PYTHON3
TASK: wormhole
"""

from typing import Any, List, Tuple
from functools import partial
from itertools import islice

fin = open("wormhole.in", "r")
fout = open("wormhole.out", "w")


def fprint(*args: Any, **kwargs: Any) -> None:
    print(*args, file=fout, **kwargs)


# Code start
def could_get_stuck(pairing: List[Tuple[int, int]]) -> bool:
    entered_from_collection = [-1] * hole_count
    exit_collection = [-1] * hole_count
    for hole_a, hole_b in pairing:
        exit_collection[hole_a] = hole_b
        exit_collection[hole_b] = hole_a
    for entrance, entered_from in enumerate(entered_from_collection):
        if entered_from == -1:
            towards = entrance
            while towards != -1:
                if entered_from_collection[towards] == entrance:
                    return True
                entered_from_collection[towards] = entrance
                towards = right[exit_collection[towards]]
    return False


def dfs() -> int:
    for hole, is_in_pairing in enumerate(in_pairing_collection):
        if not is_in_pairing:
            current_hole = hole
            break
    else:
        return could_get_stuck(pairing)
    in_pairing_collection[current_hole] = True
    result = 0
    for hole, is_in_pairing in enumerate(in_pairing_collection):
        if not is_in_pairing:
            in_pairing_collection[hole] = True
            pairing.append((current_hole, hole))
            result += dfs()
            pairing.pop()
            in_pairing_collection[hole] = False
    in_pairing_collection[current_hole] = False
    return result


hole_count = int(fin.readline())
hole_location_collection = list(
    (y, x, i) for i, (x, y) in enumerate(map(partial(map, int), map(str.split, fin)))
)
hole_location_collection.sort()
right = [-1] * hole_count
for hole_a, hole_b in zip(
    hole_location_collection, islice(hole_location_collection, 1, None)
):
    if hole_a[0] == hole_b[0]:
        right[hole_a[2]] = hole_b[2]
pairing: List[Tuple[int, int]] = []
in_pairing_collection: List[bool] = [False] * hole_count
fprint(dfs())
# Code end
