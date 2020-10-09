"""
ID: totheso1
LANG: PYTHON3
TASK: frameup
"""

from collections import defaultdict
from dataclasses import dataclass
from typing import Any, DefaultDict, List, Set, cast

fin = open("frameup.in", "r")
fout = open("frameup.out", "w")


def fprint(*args: Any, **kwargs: Any) -> None:
    print(*args, file=fout, **kwargs)


# Code start
HEIGHT, WIDTH = map(int, fin.readline().split())
ord_A = ord("A")
picture = tuple(
    tuple(ord(c) - ord_A if c.isupper() else -1 for c in row)
    for row in map(str.strip, fin)
)


def solve() -> None:
    @dataclass
    class Frame:
        top: int = cast(int, 30)
        right: int = cast(int, -1)
        bottom: int = cast(int, -1)
        left: int = cast(int, 30)

        def adjust_to_include(self, i: int, j: int) -> None:
            self.top = min(self.top, i)
            self.right = max(self.right, j)
            self.bottom = max(self.bottom, i)
            self.left = min(self.left, j)

    def check_frame_not_covered(c: int) -> bool:
        frame = frame_by_char_collection[c]
        for i in range(frame.top, frame.bottom + 1):
            for j in (frame.left, frame.right):
                if picture[i][j] not in uncovered:
                    return False
        for i in (frame.top, frame.bottom):
            for j in range(frame.left, frame.right + 1):
                if picture[i][j] not in uncovered:
                    return False
        return True

    def dfs() -> None:
        if len(sequence) == len(frame_by_char_collection):
            ans_sequence_collection.append(
                "".join(chr(i + ord_A) for i in reversed(sequence))
            )
            return
        for c in frame_char_collection:
            if c not in uncovered:
                uncovered.add(c)
                if check_frame_not_covered(c):
                    sequence.append(c)
                    dfs()
                    sequence.pop()
                uncovered.remove(c)

    frame_by_char_collection: DefaultDict[int, Frame] = defaultdict(Frame)
    for i, row in enumerate(picture):
        for j, c in enumerate(row):
            if c != -1:
                frame_by_char_collection[c].adjust_to_include(i, j)

    frame_char_collection = sorted(frame_by_char_collection.keys())
    sequence: List[int] = []
    ans_sequence_collection: List[str] = []
    uncovered: Set[int] = set()
    dfs()
    ans_sequence_collection.sort()
    fprint(*ans_sequence_collection, sep="\n")


solve()
# Code end
