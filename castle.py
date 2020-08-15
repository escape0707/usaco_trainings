"""
ID: totheso1
LANG: PYTHON3
TASK: castle
NOTE:
    With so many global variables and methods to modify them,
    I could have encapsulated them into a `Solution` class.
    But I don't have to this for all these simple OI problems, at least for now.
    BTW, there is a `print_human_readable_map` function giveaway.
"""

from math import inf
from typing import Any, List, Tuple

fin = open("castle.in", "r")
fout = open("castle.out", "w")


def fprint(*args: Any, **kwargs: Any) -> None:
    print(*args, file=fout, **kwargs)


# Code start
ROW_CNT: int
COL_CNT: int
component_id_by_index: List[List[int]]
component_size: List[int] = []
castle_map: Tuple[Tuple[int, ...], ...]


def solve_components() -> None:
    global ROW_CNT
    global COL_CNT
    global component_id_by_index
    global component_size
    global castle_map
    component_cnt: int
    encode: Tuple[int, ...] = (1, 2, 4, 8)
    direction_collection = (
        (0, -1),
        (-1, 0),
        (0, 1),
        (1, 0),
    )

    def flood_fill(i: int, j: int) -> None:
        global component_id_by_index
        global component_size
        global castle_map

        component_id_by_index[i][j] = component_cnt
        component_size[component_cnt] += 1
        for bitmask, (direction_x, direction_y) in zip(encode, direction_collection):
            if ~castle_map[i][j] & bitmask:
                next_i, next_j = i + direction_x, j + direction_y
                if component_id_by_index[next_i][next_j] == -1:
                    flood_fill(next_i, next_j)
            # else:
            #    do_component_adjacent_record_here()

    component_cnt = 0
    component_id_by_index = [[-1] * COL_CNT for _ in range(ROW_CNT)]
    for i in range(ROW_CNT):
        for j in range(COL_CNT):
            if component_id_by_index[i][j] == -1:
                component_size.append(0)
                flood_fill(i, j)
                component_cnt += 1

    fprint(component_cnt)
    fprint(max(component_size))


def solve_wall_removal() -> None:
    global ROW_CNT
    global COL_CNT
    global component_id_by_index
    global component_size
    global castle_map
    largest_room_creatable = -inf
    optimal_wall_to_remove: Tuple[int, int, str]
    encode: Tuple[int, ...] = (2, 4)
    direction_collection = ((-1, 0), (0, 1))
    direction_char = ("N", "E")

    for j in range(COL_CNT):
        for i in reversed(range(ROW_CNT)):
            current_component_id = component_id_by_index[i][j]
            for bitmask, (direction_x, direction_y), direction in zip(
                encode, direction_collection, direction_char
            ):
                if castle_map[i][j] & bitmask:
                    neighbor_i, neighbor_j = i + direction_x, j + direction_y
                    if neighbor_i == -1 or neighbor_j == COL_CNT:
                        continue
                    neighbor_component_id = component_id_by_index[neighbor_i][
                        neighbor_j
                    ]
                    if neighbor_component_id != current_component_id:
                        combined_size = (
                            component_size[current_component_id]
                            + component_size[neighbor_component_id]
                        )
                        if combined_size > largest_room_creatable:
                            largest_room_creatable = combined_size
                            optimal_wall_to_remove = (i + 1, j + 1, direction)

    fprint(largest_room_creatable)
    fprint(" ".join(map(str, optimal_wall_to_remove)))


def print_human_readable_map() -> None:
    global ROW_CNT
    global COL_CNT
    global component_id_by_index
    global castle_map
    encode: Tuple[int, ...] = (1, 2, 4, 8)
    direction_collection = (
        (0, -1),
        (-1, 0),
        (0, 1),
        (1, 0),
    )
    res: List[List[str]] = [[" "] * (COL_CNT * 2 + 1) for _ in range(ROW_CNT * 3 + 1)]
    for i in range(ROW_CNT):
        for j in range(COL_CNT):
            x, y = i * 2 + 1, j * 2 + 1
            res[x][y] = str(component_id_by_index[i][j])
            for bitmask, (direction_x, direction_y) in zip(
                encode, direction_collection
            ):
                if castle_map[i][j] & bitmask:
                    xx, yy = x + direction_x, y + direction_y
                    res[xx - direction_y][yy + direction_x] = res[xx][yy] = res[
                        xx + direction_y
                    ][yy - direction_x] = "*"
    for row in res:
        print("".join(row))


COL_CNT, ROW_CNT = map(int, fin.readline().split())
castle_map = tuple(tuple(map(int, line.split())) for line in fin)

solve_components()
# print_human_readable_map()
solve_wall_removal()
# Code end
