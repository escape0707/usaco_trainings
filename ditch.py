"""
ID: totheso1
LANG: PYTHON3
TASK: ditch
NOTE:
    This is a typical maxflow problem.
    And there exists many algorithm and implementation to solve a maxflow problem.
    I'll primarily give a Procedure Oriented method utilizing adjacency list
    and breadth first search (shortest augmenting path first)
    as this might require the least language specific knowledge for any reader,
    not that hard to code, space efficient, quick enough for a contest.
    I'll also implement this method in Object Oriented way in Python
    (but not C++ to save my time...) as it's clearer.
    But you can always find a pure Procedure Oriented, adjacency matrix based,
    Dijkstra based C implementation in the official Analysis to this problem.
    And also a pure Object Oriented, adjacency list based,
    Breath First Search based Java implementation in the book "Algorithms".
    Take whatever you like!
"""

from collections import deque
from math import inf
from typing import Any, List, cast

fin = open("ditch.in", "r")
fout = open("ditch.out", "w")


def fprint(*args: Any, **kwargs: Any) -> None:
    print(*args, file=fout, **kwargs)


# Code start
EDGE_COUNT, VERTEX_COUNT = map(int, fin.readline().split())
adjacency_list: List[List[int]] = [[] for _ in range(VERTEX_COUNT)]
capacity = []
flow = []
to = []


def initialize() -> None:
    for i, line in enumerate(fin):
        f, t, c = map(int, line.split())
        f -= 1
        t -= 1
        adjacency_list[f].append(i << 1)
        adjacency_list[t].append(i << 1 | 1)
        capacity.append(c)
        flow.append(0)
        flow.append(c)
        to.append(t)
        to.append(f)


def solve() -> None:
    def residual_capacity(edge: int) -> int:
        return capacity[edge >> 1] - flow[edge]

    def find_augmenting_path() -> bool:
        visited = [False] * VERTEX_COUNT
        que = deque((0,))
        visited[0] = True
        while que:
            curr_vertex = que.popleft()
            for edge in adjacency_list[curr_vertex]:
                next_vertex = to[edge]
                if residual_capacity(edge) != 0 and not visited[next_vertex]:
                    visited[next_vertex] = True
                    edge_to[next_vertex] = edge
                    if next_vertex == (VERTEX_COUNT - 1):
                        return True
                    que.append(next_vertex)
        return False

    edge_to = [-1] * VERTEX_COUNT
    maxflow = 0
    while find_augmenting_path():
        bottleneck = cast(int, inf)
        curr_vertex = VERTEX_COUNT - 1
        while curr_vertex != 0:
            edge = edge_to[curr_vertex]
            bottleneck = min(bottleneck, residual_capacity(edge))
            curr_vertex = to[edge ^ 1]
        curr_vertex = VERTEX_COUNT - 1
        maxflow += bottleneck
        while curr_vertex != 0:
            edge = edge_to[curr_vertex]
            flow[edge] += bottleneck
            flow[edge ^ 1] -= bottleneck
            curr_vertex = to[edge ^ 1]
    fprint(maxflow)


initialize()
solve()
# Code end


# # Code start
# from collections import deque
# from dataclasses import dataclass
# from math import inf
# from typing import Any, Final, List, cast, Optional


# @dataclass
# class FlowEdge:
#     capacity: int
#     flow: int
#     f: int
#     t: int

#     def add_residual_flow_to(self, vertex: int, delta: int) -> None:
#         if vertex == self.f:
#             self.flow -= delta
#         elif vertex == self.t:
#             self.flow += delta
#         else:
#             raise ValueError("Inconsistent edge.")

#     def other(self, vertex: int) -> int:
#         if vertex == self.f:
#             return self.t
#         if vertex == self.t:
#             return self.f
#         raise ValueError("Inconsistent edge.")

#     def residual_capacity_to(self, vertex: int) -> int:
#         if vertex == self.f:
#             return self.flow
#         if vertex == self.t:
#             return self.capacity - self.flow
#         raise ValueError("Inconsistent edge.")


# class FlowNetwork:
#     VERTEX_COUNT: Final[int]
#     edge_count: int
#     adjacency_list_collection: List[List[FlowEdge]]

#     def __init__(self, vertex_count: int) -> None:
#         self.VERTEX_COUNT = vertex_count
#         self.edge_count = 0
#         self.adjacency_list_collection = [[] for _ in range(vertex_count)]

#     def add_edge(self, edge: FlowEdge) -> None:
#         self.edge_count += 1
#         self.adjacency_list_collection[edge.f].append(edge)
#         self.adjacency_list_collection[edge.t].append(edge)

#     def adjacency_list_of(self, vertex: int) -> List[FlowEdge]:
#         return self.adjacency_list_collection[vertex]

#     def vertex_count(self) -> int:
#         return self.VERTEX_COUNT


# class FordFulkerson:
#     visited: List[bool]
#     edge_to: List[FlowEdge]
#     value: int

#     def __init__(self, G: FlowNetwork, s: int, t: int) -> None:
#         self.value = 0
#         while self.find_augmenting_path(G, s, t):
#             bottleneck = cast(int, inf)
#             vertex = t
#             while vertex != s:
#                 edge = self.edge_to[vertex]
#                 bottleneck = min(bottleneck, edge.residual_capacity_to(vertex))
#                 vertex = edge.other(vertex)
#             vertex = t
#             self.value += bottleneck
#             while vertex != s:
#                 edge = self.edge_to[vertex]
#                 edge.add_residual_flow_to(vertex, bottleneck)
#                 vertex = edge.other(vertex)

#     def find_augmenting_path(self, G: FlowNetwork, s: int, t: int) -> bool:
#         self.visited = [False] * G.vertex_count()
#         self.edge_to = [cast(FlowEdge, None)] * G.vertex_count()
#         que = deque((s,))
#         self.visited[s] = True
#         while que:
#             vertex = que.popleft()
#             for edge in G.adjacency_list_of(vertex):
#                 other = edge.other(vertex)
#                 if edge.residual_capacity_to(other) != 0 and not self.visited[other]:
#                     self.visited[other] = True
#                     self.edge_to[other] = edge
#                     if other == t:
#                         return True
#                     que.append(other)
#         return False

#     def overall_flow(self) -> int:
#         return self.value


# def main() -> None:
#     ditch_count, vertex_count = map(int, fin.readline().split())
#     flow_network = FlowNetwork(vertex_count)

#     for i, line in enumerate(fin):
#         f, t, capacity = map(int, line.split())
#         f -= 1
#         t -= 1
#         flow_network.add_edge(FlowEdge(capacity, 0, f, t))

#     maxflow = FordFulkerson(flow_network, 0, vertex_count - 1)
#     fprint(maxflow.overall_flow())


# main()
# # Code end
