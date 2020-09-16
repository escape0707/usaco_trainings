"""
ID: totheso1
LANG: PYTHON3
TASK: fence
NOTE:
    Python3 will get
    "RecursionError:_maximum_recursion_depth_exceeded_in_comparison"
    if use a naive recursive depth-first-search.
    Rewrite a non-recursive version or use C++/Java/Pascal instead.
"""

from itertools import islice
from typing import Any, Counter, DefaultDict, List, Tuple

fin = open("fence.in", "r")
fout = open("fence.out", "w")


def fprint(*args: Any, **kwargs: Any) -> None:
    print(*args, file=fout, **kwargs)


# Code start
FENCE_COUNT = int(fin.readline())
degree_by_point_collection = Counter[int]()
edge_collection_by_point_collection = DefaultDict[int, List[Tuple[int, int]]](list)


def initialize() -> None:
    def add_edge(f: int, t: int, idx: int) -> None:
        edge_collection_by_point_collection[f].append((t, idx))

    for edge_id, line in enumerate(fin):
        point_a, point_b = map(int, line.split())
        degree_by_point_collection[point_a] += 1
        degree_by_point_collection[point_b] += 1
        add_edge(point_a, point_b, edge_id)
        add_edge(point_b, point_a, edge_id)


def solve() -> None:
    def recursive_find_path(curr_point: int) -> None:
        for to, edge_id in edge_collection_by_point_collection[curr_point]:
            if not traveled[edge_id]:
                traveled[edge_id] = True
                recursive_find_path(to)
        sequence_reversed.append(curr_point)

    def non_recursive_find_path(start_point: int) -> None:
        def in_the_loop(curr_point: int, i: int) -> None:
            for to, edge_id in islice(
                edge_collection_by_point_collection[curr_point], i, None
            ):
                stack[-1][1] += 1
                if not traveled[edge_id]:
                    traveled[edge_id] = True
                    stack.append([to, 0])
                    return
            sequence_reversed.append(curr_point)
            stack.pop()

        stack = [[start_point, 0]]
        while stack:
            in_the_loop(*stack[-1])

    ending_point_collection = []
    for point, degree in degree_by_point_collection.items():
        if degree & 1:
            ending_point_collection.append(point)
    if ending_point_collection:
        if len(ending_point_collection) != 2:
            raise ValueError("No possible Eulerian circuit.")
        start = min(ending_point_collection)
    else:
        start = min(degree_by_point_collection)

    for edge_collection in edge_collection_by_point_collection.values():
        edge_collection.sort()
    sequence_reversed: List[int] = []
    traveled = [False] * FENCE_COUNT
    non_recursive_find_path(start)
    fprint(*reversed(sequence_reversed), sep="\n")


initialize()
solve()
# Code end
