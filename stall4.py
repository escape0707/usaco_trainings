"""
ID: totheso1
LANG: PYTHON3
TASK: stall4
"""

from collections import deque
from itertools import islice
from typing import Any, List

fin = open("stall4.in", "r")
fout = open("stall4.out", "w")


def fprint(*args: Any, **kwargs: Any) -> None:
    print(*args, file=fout, **kwargs)


# Code start
COW_COUNT, STALL_COUNT = map(int, fin.readline().split())
to: List[int] = []
adjacency_list: List[List[int]] = [[] for _ in range(COW_COUNT + STALL_COUNT)]


def initialize() -> None:
    def add_edge(f: int, t: int) -> None:
        adjacency_list[f].append(len(to))
        to.append(t)
        adjacency_list[t].append(len(to))
        to.append(f)

    for cow, line in enumerate(fin):
        for stall in islice(map(int, line.split()), 1, None):
            add_edge(cow, stall - 1 + COW_COUNT)


def solve() -> None:
    edge_in_match = [False] * (len(to) // 2)
    vertex_in_match = [False] * (COW_COUNT + STALL_COUNT)
    edge_to = [-1] * (COW_COUNT + STALL_COUNT)

    def find_augmenting_path(start: int) -> int:  # return path end
        visited = [False] * (COW_COUNT + STALL_COUNT)
        que = deque((start,))
        visited[start] = True
        while que:
            curr_vertex = que.popleft()
            for edge in adjacency_list[curr_vertex]:
                if (curr_vertex >= COW_COUNT) == edge_in_match[edge >> 1]:
                    other = to[edge]
                    if visited[other]:
                        continue
                    edge_to[other] = edge
                    if not vertex_in_match[other]:
                        return other
                    que.append(other)
                    visited[other] = True
        return -1

    ans = 0
    for start in range(COW_COUNT):
        curr_vertex = find_augmenting_path(start)
        if curr_vertex == -1:
            continue
        vertex_in_match[start] = vertex_in_match[curr_vertex] = True
        ans += 1
        while curr_vertex != start:
            edge = edge_to[curr_vertex]
            edge_in_match[edge >> 1] = not edge_in_match[edge >> 1]
            curr_vertex = to[edge ^ 1]
    fprint(ans)


initialize()
solve()
# Code end
