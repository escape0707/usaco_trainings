"""
ID: totheso1
LANG: PYTHON3
TASK: test
"""

fin = open("test.in", "r")
fout = open("test.out", "w")


def fprint(*args, **kwargs):
    print(*args, file=fout, **kwargs)


# Code start
fprint(sum(map(int, fin.readline().split())))
# Code end
