"""
ID: totheso1
LANG: PYTHON3
TASK: lgame
NOTE:
    There are two ways to solve this problem.
    We can enumerate through all possibility of the two words
    formable from input file,
    then check whether both of them exist in the dictionary file
    (using Trie or Binary Search or hashmap).
    Or we check all possible pairs of word formable from dictionary file,
    then check whether we can use the input to make the pair up.

    Noticing that since there will at most be 7 characters in input file,
    they can span no more than "Sigma(A(7, i) for i in [1-7])" whole words.
    This number is 13699, a lot smaller that 40000,
    so we could filter invalid words out in the dictionary out first.

    And a word must have at least 3 characters.
    So there could only be about
    A(7, 4) * (A(4, 3) + A(4, 4)) == 40320 possible pairs. (Not a concise calculation.)

    The time complexity of method 1 is (count off possibility * lookup time),
    which is no more than (13699 + 40320).
    The time complexity of method 2 is (13699 * 13699 / 2 * 26).
    Method 2 is slower and risks a Time Limit Exceeded.
    Since we can use hashmap in Python and C++ as of 2020 today,
    I'll chose method 1 here.
"""

from itertools import permutations
from typing import Any, Set

fin = open("lgame.in", "r")
fdict = open("lgame.dict", "r")
fout = open("lgame.out", "w")


def fprint(*args: Any, **kwargs: Any) -> None:
    print(*args, file=fout, **kwargs)


# Code start
value_collection = (
    2,
    5,
    4,
    4,
    1,
    6,
    5,
    5,
    1,
    7,
    6,
    3,
    5,
    2,
    3,
    5,
    7,
    2,
    1,
    2,
    4,
    6,
    6,
    7,
    5,
    7,
)

given_charactor_collection = "".join(sorted(fin.readline().strip()))

dictionary = set(line.strip() for line in fdict)
dictionary.discard(".")


def solve() -> None:
    ord_a = ord("a")

    def compute_score(s: str) -> int:
        return sum(value_collection[ord(c) - ord_a] for c in s)

    ans_score = 0
    ans_str_collection: Set[str] = set()
    prev = ""
    for s in map("".join, permutations(given_charactor_collection)):
        if s == prev:
            continue
        for right in range(3, len(s) + 1):
            for mid in range(3, right + 1):
                total = s[:mid]
                if total not in dictionary:
                    continue
                score = compute_score(total)
                if right - mid >= 3:
                    second = s[mid:right]
                    if second not in dictionary:
                        continue
                    score += compute_score(second)
                    if total > second:
                        total, second = second, total
                    total = total + " " + second
                if total not in ans_str_collection:
                    if score > ans_score:
                        ans_score = score
                        ans_str_collection.clear()
                    if score == ans_score:
                        ans_str_collection.add(total)
        prev = s

    fprint(ans_score)
    fprint(*sorted(ans_str_collection), sep="\n")


solve()
# Code end
