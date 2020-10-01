"""
ID: totheso1
LANG: PYTHON3
TASK: race3
"""

from collections import deque
from typing import Any

fin = open("race3.in", "r")
fout = open("race3.out", "w")


def fprint(*args: Any, **kwargs: Any) -> None:
    print(*args, file=fout, **kwargs)


# Code start
adjacency_list = []


def initialize() -> None:
    for f, line in enumerate(fin):
        int_collection = list(map(int, line.split()))
        if int_collection[0] != -1:
            int_collection.pop()
            adjacency_list.append(int_collection)


def solve() -> None:
    def bfs_avoid(avoid: int) -> bool:
        que = deque((0,))
        first_bfs_visited[0] = True
        while que:
            curr_vertex = que.popleft()
            for to in adjacency_list[curr_vertex]:
                if first_bfs_visited[to] or to == avoid:
                    continue
                if to == vertex_count - 1:
                    return True
                que.append(to)
                first_bfs_visited[to] = True
        return False

    def bfs_can_go_back(start: int) -> bool:
        visited = [False] * vertex_count
        que = deque((start,))
        visited[start] = True
        while que:
            curr_vertex = que.popleft()
            for to in adjacency_list[curr_vertex]:
                if visited[to]:
                    continue
                if first_bfs_visited[to]:
                    return True
                que.append(to)
                visited[to] = True
        return False

    unavoidable_point_collection = []
    splitting_point_collection = []
    vertex_count = len(adjacency_list)
    for vertex in range(vertex_count - 1):
        first_bfs_visited = [False] * vertex_count
        if not bfs_avoid(vertex):
            unavoidable_point_collection.append(vertex)
            if not bfs_can_go_back(vertex):
                splitting_point_collection.append(vertex)
    fprint(len(unavoidable_point_collection), *unavoidable_point_collection)
    fprint(len(splitting_point_collection), *splitting_point_collection)


initialize()
solve()
# Code end
