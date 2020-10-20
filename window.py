"""
ID: totheso1
LANG: PYTHON3
TASK: window
"""

from __future__ import annotations

from dataclasses import dataclass
from typing import Any, OrderedDict

fin = open("window.in", "r")
fout = open("window.out", "w")


def fprint(*args: Any, **kwargs: Any) -> None:
    print(*args, file=fout, **kwargs)


# Code start
@dataclass
class Window:
    top: int
    right: int
    bottom: int
    left: int

    def area(self) -> int:
        return (self.bottom - self.top) * (self.right - self.left)


def solve() -> None:
    window_by_id_collection = OrderedDict[str, Window]()

    def extract_window_id(command: str) -> str:
        return command[2]

    def create_window(command: str) -> None:
        i1, j1, i2, j2 = map(int, command[3:].split(","))
        top, right, bottom, left = min(i1, i2), max(j1, j2), max(i1, i2), min(j1, j2)
        window_by_id_collection[extract_window_id(command)] = Window(
            top, right, bottom, left
        )

    def move_window_to_top(command: str) -> None:
        window_by_id_collection.move_to_end(extract_window_id(command))

    def move_window_to_bottom(command: str) -> None:
        window_by_id_collection.move_to_end(extract_window_id(command), False)

    def destroy_window(command: str) -> None:
        del window_by_id_collection[extract_window_id(command)]

    def output_window_percentage_visible(command: str) -> None:
        current_window_id = extract_window_id(command)
        window = window_by_id_collection[current_window_id]
        area = window.area()
        window_id_collection = tuple(window_by_id_collection)
        uncovered_area = calculate_window_uncovered_area(window_id_collection.find)

    function_by_operation_collection = {
        "w": create_window,
        "t": move_window_to_top,
        "b": move_window_to_bottom,
        "d": destroy_window,
        "s": output_window_percentage_visible,
    }
    for line in fin:
        function_by_operation_collection[line[0]](line)


solve()
# Code end
