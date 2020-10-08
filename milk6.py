"""
ID: totheso1
LANG: PYTHON3
TASK: milk6
NOTE:
    This time I learned and tried Dinic's Algorithm.
"""

from copy import deepcopy
from math import inf
from typing import Any, cast

fin = open("milk6.in", "r")
fout = open("milk6.out", "w")


def fprint(*args: Any, **kwargs: Any) -> None:
    print(*args, file=fout, **kwargs)


# Code start
WAREHOUSE_COUNT, ROUTE_COUNT = map(int, fin.readline().split())
origin_network = [[0] * WAREHOUSE_COUNT for _ in range(WAREHOUSE_COUNT)]
edge_collection = []


def initialize() -> None:
    for line in fin:
        start, end, route_cost = map(int, line.split())
        start -= 1
        end -= 1
        route_cost = route_cost * 1001 + 1
        origin_network[start][end] += route_cost
        edge_collection.append((start, end, route_cost))


def solve() -> None:
    def dinic() -> int:
        residual_network = deepcopy(origin_network)
        level = []

        def build_level_graph(start: int) -> bool:
            nonlocal level
            level = [-1] * WAREHOUSE_COUNT
            que = [start]
            next_level = 0
            level[que[0]] = next_level
            while que and level[WAREHOUSE_COUNT - 1] == -1:
                next_que = []
                next_level += 1
                for curr_warehouse in que:
                    for next_warehouse in range(WAREHOUSE_COUNT):
                        if (
                            level[next_warehouse] == -1
                            and residual_network[curr_warehouse][next_warehouse] > 0
                        ):
                            next_que.append(next_warehouse)
                            level[next_warehouse] = next_level
                que = next_que
            return level[WAREHOUSE_COUNT - 1] != -1

        def augment(curr_warehouse: int, bottleneck: int) -> int:
            if curr_warehouse == WAREHOUSE_COUNT - 1:
                return bottleneck
            blocking_flow = 0
            next_level = level[curr_warehouse] + 1
            for next_warehouse in range(WAREHOUSE_COUNT):
                if level[next_warehouse] == next_level and not deadend[next_warehouse]:
                    residual = residual_network[curr_warehouse][next_warehouse]
                    if residual > 0:
                        flow = augment(
                            next_warehouse, min(bottleneck - blocking_flow, residual)
                        )
                        if flow > 0:
                            blocking_flow += flow
                            residual_network[curr_warehouse][next_warehouse] -= flow
                            residual_network[next_warehouse][curr_warehouse] += flow
                            if blocking_flow == bottleneck:
                                break
            deadend[curr_warehouse] = blocking_flow != bottleneck
            return blocking_flow

        maxflow = 0
        while build_level_graph(0):
            deadend = [False] * WAREHOUSE_COUNT
            maxflow += augment(0, cast(int, inf))
        return maxflow

    maxflow = dinic()
    ans = maxflow // 1001
    ans_collection = []
    for i, (start, end, cost) in enumerate(edge_collection, start=1):
        origin_network[start][end] -= cost
        new_maxflow = dinic()
        if new_maxflow + cost == maxflow:
            maxflow = new_maxflow
            ans_collection.append(i)
            if maxflow == 0:
                break
        else:
            origin_network[start][end] += cost
    fprint(ans, len(ans_collection))
    if ans_collection:
        fprint(*ans_collection, sep="\n")


initialize()
solve()
# Code end
