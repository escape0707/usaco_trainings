"""
ID: totheso1
LANG: PYTHON3
TASK: namenum
"""
from itertools import islice

fin = open("namenum.in", "r")
fout = open("namenum.out", "w")


def fprint(*args, **kwargs):
    print(*args, file=fout, **kwargs)


# Code start
fdict = open("dict.txt", "r")

# hashmap = list(chain.from_iterable(map(partial(repeat, times=3), range(2, 10))))
# hashmap.append(0)
# hashmap.insert(ord("Q") - ord("A"), 0)
# print(*map(chr, range(ord("A"), ord("A") + 26)), sep=", ")
#  A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z
# print(hashmap)
# [2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 0, 7, 7, 8, 8, 8, 9, 9, 9, 0]
hashmap = [2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 0, 7, 7, 8, 8, 8, 9, 9, 9, 0]


def hash_char(char: str) -> int:
    return hashmap[ord(char) - 65]


brand_number = int(fin.read())
found_match = False
for valid_name_with_lf in fdict:
    hashcode = 0
    for c in islice(valid_name_with_lf, len(valid_name_with_lf) - 1):
        hashcode = hashcode * 10 + hash_char(c)
    if hashcode == brand_number:
        found_match = True
        fprint(valid_name_with_lf, end="")
if not found_match:
    fprint("NONE")
# Code end
