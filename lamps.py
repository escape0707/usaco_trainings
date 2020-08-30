"""
ID: totheso1
LANG: PYTHON3
TASK: lamps
"""

from itertools import combinations, cycle, islice
from typing import Any, Tuple, List

fin = open("lamps.in", "r")
fout = open("lamps.out", "w")


def fprint(*args: Any, **kwargs: Any) -> None:
    print(*args, file=fout, **kwargs)


# Code start
button_effect_collection = [0b111111, 0b101010, 0b010101, 0b100100]


def toggle(state: int, switch_collection: Tuple[int, ...]) -> int:
    for switch in switch_collection:
        state ^= button_effect_collection[switch]
    return state


MAXLAMPS = 6
MAXSWITCH = 4
N = int(fin.readline())
C = int(fin.readline())

bit_mask = 0
bit_requirement = 0
for i in map(int, fin.readline().split()):
    if i != -1:
        bit_mask |= 1 << (-i % MAXLAMPS)
        bit_requirement |= 1 << (-i % MAXLAMPS)
for i in map(int, fin.readline().split()):
    if i != -1:
        bit_mask |= 1 << (-i % MAXLAMPS)

ans: List[int] = []
for cnt in range(C & 1, min(MAXSWITCH + 1, C + 1), 2):
    for switch_collection in combinations(range(0, MAXSWITCH), cnt):
        state = toggle(button_effect_collection[0], switch_collection)
        if state & bit_mask == bit_requirement:
            ans.append(state)
if ans:
    ans.sort()
    for state in ans:
        fprint("".join(islice(cycle(f"{state:0>{MAXLAMPS}b}"), N)))
else:
    fprint("IMPOSSIBLE")
# Code end
