"""
ID: totheso1
LANG: PYTHON3
TASK: friday
"""

fin = open("friday.in", "r")
fout = open("friday.out", "w")


def fprint(*args, **kwargs) -> None:
    print(*args, file=fout, **kwargs)


# Code start
# These integers represent the number of times the 13th falls on
# Saturday, Sunday, Monday, Tuesday, Tuesday, Wednesday, Thursday, Friday.
# Shit. USACO Training don't support `typing` module. Lost my 1-pass AC again.
DAYS_OF_MONTH = (
    31,
    28,
    31,
    30,
    31,
    30,
    31,
    31,
    30,
    31,
    30,
    31,
)


def is_leap_year(year: int) -> bool:
    if year % 4 != 0:
        return False
    if year % 100 != 0:
        return True
    return year % 400 == 0


frequency = [0] * 7

day_of_13th: int = 0  # (2 + 13 - 1) % 7
years: int = int(fin.read())
for year in range(1900, 1900 + years):
    for month in range(12):
        frequency[day_of_13th] += 1
        day_of_13th = (
            day_of_13th + DAYS_OF_MONTH[month] + (month == 1 and is_leap_year(year))
        ) % 7

fprint(*frequency)
# Code end
