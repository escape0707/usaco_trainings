"""
ID: totheso1
LANG: PYTHON3
TASK: transform
"""

from itertools import chain, islice

fin = open("transform.in", "r")
fout = open("transform.out", "w")


def fprint(*args, **kwargs) -> None:
    print(*args, file=fout, **kwargs)


# Code start
def equal(start, step_outer, step_inner):
    start = list(start)
    for origin_row in origin:
        x, y = start[0], start[1]
        for tile in origin_row:
            if tile != target[x][y]:
                return False
            x += step_inner[0]
            y += step_inner[1]
        for i, step_i in enumerate(step_outer):
            start[i] += step_i
    return True


def find_transformation():
    def rotate_90(trans):
        start, step_outer, step_inner = trans
        return (
            (start[1], side - 1 - start[0]),
            (step_outer[1], -step_outer[0]),
            (step_inner[1], -step_inner[0]),
        )

    def reflect(trans):
        start, step_outer, step_inner = trans
        return (
            (start[0], side - 1 - start[1]),
            (step_outer[0], -step_outer[1]),
            (step_inner[0], -step_inner[1]),
        )

    identity_trans = ((0, 0), (1, 0), (0, 1))
    transformations = [(rotate_90(identity_trans),)]
    for _ in range(2):
        transformations.append(tuple(map(rotate_90, transformations[-1])))
    transformations.append((reflect(identity_trans),))
    transformations.append(
        tuple(
            map(
                reflect,
                chain.from_iterable(islice(transformations, len(transformations) - 1)),
            ),
        )
    )
    transformations.append((identity_trans,))
    for i, trans in enumerate(transformations):
        for view in trans:
            if equal(*view):
                return i + 1
    return i + 2


side = int(fin.readline())
origin = tuple(fin.readline()[:-1] for _ in range(side))
target = tuple(fin.readline()[:-1] for _ in range(side))
fprint(find_transformation())
# Code end
