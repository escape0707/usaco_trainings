"""
ID: totheso1
LANG: PYTHON3
TASK: fence6
NOTE:
    Classic problem of shortest circle for a undirected graph.
"""

from copy import deepcopy
from heapq import heappop, heappush
from math import inf
from typing import Any, Dict, List, Tuple, cast

fin = open("fence6.in", "r")
fout = open("fence6.out", "w")


def fprint(*args: Any, **kwargs: Any) -> None:
    print(*args, file=fout, **kwargs)


# Code start
MAX_EDGE_COUNT = 100
vertex_count = 0
direct_dist: List[List[int]]
edge_by_vertex_collection: List[List[Tuple[int, int]]]


def initialize_adjacent_matrix() -> None:
    global vertex_count
    global direct_dist

    direct_dist = [
        [cast(int, inf)] * (MAX_EDGE_COUNT * 2) for _ in range(MAX_EDGE_COUNT * 2)
    ]

    def add_undirected_edge(f: int, t: int, length: int) -> None:
        direct_dist[f][t] = direct_dist[t][f] = length

    segment_total = int(fin.readline())
    vertex_by_joint_collection: List[Dict[int, int]] = [
        {} for _ in range(segment_total)
    ]
    for segment_count in range(segment_total):
        segment_id, length, first_ending_degree, second_ending_degree = map(
            int, fin.readline().split()
        )
        segment_id -= 1
        endpoint_collection = []
        for endpoint_count in range(2):
            connected_segment_collection = tuple(
                int(s) - 1 for s in fin.readline().split()
            )
            for connected_segment_id in connected_segment_collection:
                if segment_id in vertex_by_joint_collection[connected_segment_id]:
                    endpoint = vertex_by_joint_collection[connected_segment_id][
                        segment_id
                    ]
                    break
            else:
                endpoint = vertex_count
                vertex_count += 1
                for connected_segment_id in connected_segment_collection:
                    vertex_by_joint_collection[segment_id][
                        connected_segment_id
                    ] = endpoint
            endpoint_collection.append(endpoint)
        add_undirected_edge(endpoint_collection[0], endpoint_collection[1], length)


def solve_with_floyd_warshall() -> None:
    dist = deepcopy(direct_dist)
    ans = cast(int, inf)
    for k in range(vertex_count):
        for i in range(k):
            for j in range(i):
                ans = min(ans, dist[i][j] + direct_dist[i][k] + direct_dist[k][j])
        for i in range(vertex_count):
            for j in range(i):
                dist[i][j] = dist[j][i] = min(dist[i][j], dist[i][k] + dist[k][j])
    fprint(ans)


def initialize_adjacent_list() -> None:
    global vertex_count
    global edge_by_vertex_collection

    edge_by_vertex_collection = []

    def add_directed_edge(f: int, t: int, length: int) -> None:
        edge_by_vertex_collection[f].append((length, t))

    segment_total = int(fin.readline())
    vertex_by_joint_collection: List[Dict[int, int]] = [
        {} for _ in range(segment_total)
    ]
    for segment_count in range(segment_total):
        segment_id, length, first_ending_degree, second_ending_degree = map(
            int, fin.readline().split()
        )
        segment_id -= 1
        endpoint_collection = []
        for endpoint_count in range(2):
            connected_segment_collection = tuple(
                int(s) - 1 for s in fin.readline().split()
            )
            for connected_segment_id in connected_segment_collection:
                if segment_id in vertex_by_joint_collection[connected_segment_id]:
                    endpoint = vertex_by_joint_collection[connected_segment_id][
                        segment_id
                    ]
                    break
            else:
                endpoint = vertex_count
                vertex_count += 1
                edge_by_vertex_collection.append([])
                for connected_segment_id in connected_segment_collection:
                    vertex_by_joint_collection[segment_id][
                        connected_segment_id
                    ] = endpoint
            endpoint_collection.append(endpoint)
        add_directed_edge(endpoint_collection[0], endpoint_collection[1], length)
        add_directed_edge(endpoint_collection[1], endpoint_collection[0], length)


def solve_with_dijkstra() -> None:
    def dijkstra(start: int) -> None:
        heap = list(edge_by_vertex_collection[start])
        while heap:
            while heap:
                curr_dist, curr = heappop(heap)
                if dist[curr] == inf:
                    break
            else:
                return
            dist[curr] = curr_dist
            for length_to in edge_by_vertex_collection[curr]:
                heappush(heap, (curr_dist + length_to[0], length_to[1]))

    ans = cast(int, inf)
    for start, edge_collection in enumerate(edge_by_vertex_collection):
        for index, length_to in zip(
            reversed(range(len(edge_collection))), reversed(edge_collection)
        ):
            edge_collection[index] = edge_collection[-1]
            edge_collection.pop()
            dist = [cast(int, inf)] * vertex_count
            dijkstra(start)
            edge_collection.append(length_to)
            ans = min(ans, length_to[0] + dist[length_to[1]])
    fprint(ans)


# initialize_adjacent_matrix()
# solve_with_floyd_warshall()
initialize_adjacent_list()
solve_with_dijkstra()
# Code end
