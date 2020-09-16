"""
ID: totheso1
LANG: PYTHON3
TASK: butter
NOTE:
    I once implemented my own LinkedList to store the paths.
    But I got Time Limit Exceeded.
    Using a python List is fine instead.
    Speechless.
    By the way, SPFA is faster than Dijkstra + Heap for this problem.
"""

from collections import deque
from heapq import heappop, heappush
from math import inf
from typing import Any, List, Tuple, cast

fin = open("butter.in", "r")
fout = open("butter.out", "w")


def fprint(*args: Any, **kwargs: Any) -> None:
    print(*args, file=fout, **kwargs)


# Code start
COW_COUNT, PASTURE_COUNT, PATH_COUNT = map(int, fin.readline().split())
pasture_by_cow_collection = tuple(int(fin.readline()) - 1 for _ in range(COW_COUNT))
path_collection_by_pasture_collection: List[List[Tuple[int, int]]] = [
    [] for _ in range(PASTURE_COUNT)
]


def initialize() -> None:
    def add_edge(f: int, t: int, length: int) -> None:
        path_collection_by_pasture_collection[f].append((t, length))

    for line in fin:
        pasture_a, pasture_b, length = map(int, line.split())
        pasture_a -= 1
        pasture_b -= 1
        add_edge(pasture_a, pasture_b, length)
        add_edge(pasture_b, pasture_a, length)


def solve() -> None:
    def dijkstra(source: int) -> None:
        solved = [False] * PASTURE_COUNT
        heap = [(0, source)]
        for solved_count in range(PASTURE_COUNT):
            while True:
                curr_dist, curr_pasture = heappop(heap)
                if not solved[curr_pasture]:
                    break
            dist[curr_pasture] = curr_dist
            solved[curr_pasture] = True
            for to, length in path_collection_by_pasture_collection[curr_pasture]:
                if not solved[to]:
                    heappush(heap, (curr_dist + length, to))

    def spfa(source: int) -> None:
        dist[source] = 0
        in_queue = [False] * PASTURE_COUNT
        queue = deque((source,))
        in_queue[source] = True
        for relax_count in range(PASTURE_COUNT * (PASTURE_COUNT - 1) + 1):
            if not queue:
                return
            curr_pasture = queue.popleft()
            in_queue[curr_pasture] = False
            curr_dist = dist[curr_pasture]
            for to, length in path_collection_by_pasture_collection[curr_pasture]:
                new_dist = curr_dist + length
                if new_dist < dist[to]:
                    dist[to] = new_dist
                    if not in_queue[to]:
                        queue.append(to)
                        in_queue[to] = True
        raise ValueError("Graph contains negative circuit.")

    ans = cast(int, inf)
    for sugar_pasture in range(PASTURE_COUNT):
        dist = [cast(int, inf)] * PASTURE_COUNT
        spfa(sugar_pasture)
        ans = min(ans, sum(map(dist.__getitem__, pasture_by_cow_collection)))
    fprint(ans)


initialize()
solve()
# Code end
