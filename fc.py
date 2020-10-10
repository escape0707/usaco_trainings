"""
ID: totheso1
LANG: PYTHON3
TASK: fc
"""

from math import sqrt
from itertools import islice
from functools import cmp_to_key
from typing import Any, List, Tuple, cast

fin = open("fc.in", "r")
fout = open("fc.out", "w")


def fprint(*args: Any, **kwargs: Any) -> None:
    print(*args, file=fout, **kwargs)


# Code start
POINT_COUNT = int(fin.readline())
point_collection: List[Tuple[float, float]] = [
    cast(Tuple[float, float], tuple(map(float, line.split()))) for line in fin
]

Point = Tuple[float, float]


def solve() -> None:
    # return { -1, 0, +1 } if a→b→c is a { countereclockwise, collinear; clockwise } turn.
    def polar_order(a: Point, b: Point, c: Point) -> int:
        def sign(num: Any) -> int:
            return 1 if 0 < num else (-1 if num < 0 else 0)

        area2 = (b[0] - a[0]) * (c[1] - a[1]) - (b[1] - a[1]) * (c[0] - a[0])
        return -sign(area2)

    def dist(a: Point, b: Point) -> float:
        return sqrt(sum((i - j) ** 2 for i, j in zip(a, b)))

    convex_hull = []
    if point_collection:  # else, no point at all
        point_collection.sort()
        first_point = point_collection[-1]
        convex_hull.append(first_point)
        while point_collection and point_collection[-1] == first_point:
            point_collection.pop()
        if point_collection:  # else, only one unique point
            point_collection.sort(
                key=cmp_to_key(lambda b, c: polar_order(first_point, b, c))
            )
            second_point = point_collection[0]
            convex_hull.append(second_point)
            not_all_points_collinear = False
            for i in range(1, len(point_collection)):
                if polar_order(first_point, second_point, point_collection[i]) == 0:
                    if point_collection[i][0] < second_point[0]:
                        second_point = point_collection[i]
                else:
                    not_all_points_collinear = True
                    break
            if not_all_points_collinear:  # else, all points are collinear
                point_collection.append(first_point)
                for next_point in islice(point_collection, i, None):
                    while not polar_order(next_point, convex_hull[-2], convex_hull[-1]) < 0:
                        convex_hull.pop()
                    convex_hull.append(next_point)

    ans = 0.0
    for point_a, point_b in zip(convex_hull, islice(convex_hull, 1, None)):
        ans += dist(point_a, point_b)
    fprint(f"{ans:.2f}")


solve()
# Code end
