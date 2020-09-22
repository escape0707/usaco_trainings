"""
ID: totheso1
LANG: PYTHON3
TASK: rockers
"""

from typing import Any

fin = open("rockers.in", "r")
fout = open("rockers.out", "w")


def fprint(*args: Any, **kwargs: Any) -> None:
    print(*args, file=fout, **kwargs)


# Code start
SONG_COUNT, DISK_SIZE, DISK_COUNT = map(int, fin.readline().split())


def solve() -> None:
    dp = [[0] * (DISK_SIZE + 1) for _ in range(DISK_COUNT + 1)]
    for song_length in map(int, fin.readline().split()):
        for disk in reversed(range(1, DISK_COUNT + 1)):
            for curr_size in reversed(range(song_length, DISK_SIZE + 1)):
                dp[disk][curr_size] = max(
                    dp[disk][curr_size],
                    dp[disk][curr_size - song_length] + 1,
                    dp[disk - 1][DISK_SIZE] + 1,
                )
    fprint(dp[DISK_COUNT][DISK_SIZE])


solve()
# Code end
