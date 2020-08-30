"""
ID: totheso1
LANG: PYTHON3
TASK: prefix
NOTE:
    For this problem,
    you can work out a simple dynamic programing solution easily,
    and it will get accepted in time restriction if implemented in C++.
    That's EXACTLY what you want and should do in a real contest:
    Implement an easy to come up with, debug,
    and cost less time to finish and correct algorithm.
    What you NEVER EVER want to experience is that you realize that
    this problem can be further optimized if you use Trie,
    or, if you are the smartest OI nerd in your class,
    an Aho–Corasick algorithm.
    And you tried hard and spend 20 extra minutes,
    to recall Aho-Corasick algorithm,
    verify it works perfectly for this problem,
    precisely implement it,
    and then don't have enough time for the next problem
    and finally got surpassed by some guy
    who don't even know these "supreme" arts of OI.
    Or even worse, you correctly did every thing else
    but forget that you should not accquire an array of 10,000 by 10,000,
    and got no points on this problem at all.
    NO, YOU DON'T WANT THAT TO HAPPEN!!!
    So, appreciate a simple and stupid solution, work it out,
    then go for a tougher challenge and reach higher.
"""

from __future__ import annotations

from collections import deque
from dataclasses import dataclass, field
from itertools import islice, starmap, zip_longest
from operator import eq
from typing import Any, List, Optional, cast

fin = open("prefix.in", "r")
fout = open("prefix.out", "w")


def fprint(*args: Any, **kwargs: Any) -> None:
    print(*args, file=fout, **kwargs)


# Code start
def solve_with_basic_dynamic_programming() -> int:  # Time Limit Exceeded
    global primitive_collection
    global target
    target_length = len(target)
    matchable_collection = [True] + [False] * target_length
    ans = 0
    for i in range(1, target_length + 1):
        for primitive in primitive_collection:
            primitive_length = len(primitive)
            if (
                all(
                    starmap(
                        eq,
                        zip_longest(
                            primitive,
                            islice(target, max(0, i - primitive_length), i),
                            fillvalue=object(),
                        ),
                    )
                )
                and matchable_collection[i - primitive_length]
            ):
                matchable_collection[i] = True
                ans = i
                break
    return ans


def solve_with_dynamic_programming_and_trie() -> int:  # Accepted
    global primitive_collection
    global target

    @dataclass
    class TrieNode:
        is_ending = False
        next_collection: List[Optional[TrieNode]] = field(
            default_factory=lambda: [None] * 26
        )

    trie_root = TrieNode()
    trie_height = 1
    ord_A = ord("A")  # 65
    for primitive in primitive_collection:
        trie_height = max(trie_height, len(primitive) + 1)
        curr_node = trie_root
        for c in reversed(primitive):
            index_c = ord(c) - ord_A
            next_node = curr_node.next_collection[index_c]
            if next_node is None:
                next_node = curr_node.next_collection[index_c] = TrieNode()
            curr_node = next_node
        curr_node.is_ending = True

    target_length = len(target)
    matchable_by_length_collection = [True] + [False] * target_length
    ans = 0
    for i in range(target_length):
        curr_node = trie_root
        for j in range(min(i + 1, trie_height - 1)):
            index_c = ord(target[i - j]) - ord_A
            next_node = curr_node.next_collection[index_c]
            if next_node is None:
                break
            curr_node = next_node
            if curr_node.is_ending and matchable_by_length_collection[i - j - 1 + 1]:
                matchable_by_length_collection[i + 1] = True
                ans = i + 1
                break
    return ans


def solve_with_dynamic_programming_and_AC_automaton() -> int:  # Accepted
    global primitive_collection
    global target

    @dataclass
    class ACNode:
        end_with_length: List[int] = field(default_factory=lambda: [])
        next_collection: List[Optional[ACNode]] = field(
            default_factory=lambda: [None] * 26
        )
        fail_to: Optional[ACNode] = None

    AC_root = ACNode()
    AC_root.fail_to = AC_root
    ord_A = ord("A")  # 65
    for primitive in primitive_collection:
        curr_node = AC_root
        for c in primitive:
            index_c = ord(c) - ord_A
            next_node = curr_node.next_collection[index_c]
            if next_node is None:
                next_node = curr_node.next_collection[index_c] = ACNode()
            curr_node = next_node
        curr_node.end_with_length.append(len(primitive))

    que = deque(filter(None, AC_root.next_collection))
    for node in que:
        node.fail_to = AC_root
    while que:
        parent_node = que.popleft()
        # for index_c, child_node in filter(
        #     itemgetter(1), enumerate(parent_node.next_collection)
        # ):
        for index_c, child_node in enumerate(parent_node.next_collection):
            if child_node is None:
                continue
            que.append(child_node)
            fail_to = cast(ACNode, parent_node.fail_to)
            while fail_to != AC_root and fail_to.next_collection[index_c] is None:
                fail_to = cast(ACNode, fail_to.fail_to)
            child_node.fail_to = fail_to.next_collection[index_c] or AC_root
            child_node.end_with_length.extend(child_node.fail_to.end_with_length)

    target_length = len(target)
    matchable_by_length_collection = [True] + [False] * target_length
    ans = 0
    curr_node = AC_root
    for i, c in enumerate(target):
        index_c = ord(c) - ord_A
        next_node = curr_node.next_collection[index_c]
        while curr_node != AC_root and next_node is None:
            curr_node = cast(ACNode, curr_node.fail_to)
            next_node = curr_node.next_collection[index_c]
        curr_node = next_node or AC_root
        for length in curr_node.end_with_length:
            if matchable_by_length_collection[i - length + 1]:
                matchable_by_length_collection[i + 1] = True
                ans = i + 1
                break
    return ans


primitive_collection = []
for line in fin:
    if line == ".\n":
        break
    primitive_collection.extend(line.split())
target = "".join(map(str.strip, fin))
fprint(solve_with_dynamic_programming_and_AC_automaton())
# Code end
