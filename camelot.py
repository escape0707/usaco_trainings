"""
ID: totheso1
LANG: PYTHON3
TASK: camelot
NOTE:
    Python3 will get a Time Limit Exceeded.
    Use C++ / Java / Pascal instead.
"""

from math import inf
from operator import sub
from typing import Any, Iterable, List, Tuple, cast

fin = open("camelot.in", "r")
fout = open("camelot.out", "w")


def fprint(*args: Any, **kwargs: Any) -> None:
    print(*args, file=fout, **kwargs)


# Code start
ROW_COUNT, COLUMN_COUNT = map(int, fin.readline().split())
king_location: Tuple[int, int]
knight_location_collection = []


def initialize() -> None:
    global king_location
    ord_A = ord("A")
    king_col, king_row = fin.readline().split()
    king_location = (int(king_row) - 1, ord(king_col) - ord_A)
    for line in fin:
        input_iter = iter(line.split())
        for knight_col, knight_row in zip(input_iter, input_iter):
            knight_location_collection.append(
                (int(knight_row) - 1, ord(knight_col) - ord_A)
            )


def solve() -> None:
    knight_move_collection = (
        (-2, 1),
        (-1, 2),
        (1, 2),
        (2, 1),
        (2, -1),
        (1, -2),
        (-1, -2),
        (-2, -1),
    )

    def chebyshev_distance(vector_a: Iterable[int], vector_b: Iterable[int]) -> int:
        return cast(int, max(map(abs, map(sub, vector_a, vector_b))))

    def bfs_dist(start_i: int, start_j: int) -> List[List[int]]:
        res = [[cast(int, inf)] * COLUMN_COUNT for _ in range(ROW_COUNT)]
        visited = [[False] * COLUMN_COUNT for _ in range(ROW_COUNT)]
        visited[start_i][start_j] = True
        que = [(start_i, start_j)]
        step_count = -1
        while que:
            step_count += 1
            next_que = []
            for curr_i, curr_j in que:
                res[curr_i][curr_j] = step_count
                for move_i, move_j in knight_move_collection:
                    new_i, new_j = curr_i + move_i, curr_j + move_j
                    if (
                        0 <= new_i < ROW_COUNT
                        and 0 <= new_j < COLUMN_COUNT
                        and not visited[new_i][new_j]
                    ):
                        visited[new_i][new_j] = True
                        next_que.append((new_i, new_j))
            que = next_que
        return res

    def bfs_find_max_step_reduce() -> int:
        visited = [[False] * COLUMN_COUNT for _ in range(ROW_COUNT)]
        knight_collection = sorted(
            (
                king_direct_dist + dist[knight_location[0]][knight_location[1]],
                knight_location,
            )
            for knight_location in knight_location_collection
        )
        max_step_reduced = 0
        que = []
        if not knight_collection:
            return 0
        direct_dist_minus_step_count = knight_collection[-1][0] + 1
        # +1 because I prefer to decrease it at the beginning of the while loop.
        # That way I don't easily forget I need to manipulate this counter.
        while True:
            direct_dist_minus_step_count -= 1
            while (
                knight_collection
                and knight_collection[-1][0] == direct_dist_minus_step_count
            ):
                knight_location = knight_collection.pop()[1]
                que.append(knight_location)
                knight_i, knight_j = knight_location
                visited[knight_i][knight_j] = True
            if not que:
                break
            next_que = []
            for curr_location in que:
                curr_i, curr_j = curr_location
                max_step_reduced = max(
                    max_step_reduced,
                    direct_dist_minus_step_count
                    - (
                        chebyshev_distance(curr_location, king_location)
                        + dist[curr_i][curr_j]
                    ),
                )
                for move_i, move_j in knight_move_collection:
                    new_i, new_j = curr_i + move_i, curr_j + move_j
                    if (
                        0 <= new_i < ROW_COUNT
                        and 0 <= new_j < COLUMN_COUNT
                        and not visited[new_i][new_j]
                    ):
                        visited[new_i][new_j] = True
                        next_que.append((new_i, new_j))
            que = next_que
        return max_step_reduced

    ans = cast(int, inf)
    for gathering_point_i in range(ROW_COUNT):
        for gathering_point_j in range(COLUMN_COUNT):
            king_direct_dist = chebyshev_distance(
                king_location, (gathering_point_i, gathering_point_j)
            )
            dist = bfs_dist(gathering_point_i, gathering_point_j)
            step = king_direct_dist
            for knight_i, knight_j in knight_location_collection:
                knight_dist = dist[knight_i][knight_j]
                if knight_dist == inf:
                    break
                step += knight_dist
            else:
                step -= bfs_find_max_step_reduce()
                ans = min(ans, step)
    fprint(ans)


initialize()
solve()
# Code end
