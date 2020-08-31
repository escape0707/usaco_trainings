"""
ID: totheso1
LANG: PYTHON3
TASK: nocows
"""

from typing import Any

fin = open("nocows.in", "r")
fout = open("nocows.out", "w")


def fprint(*args: Any, **kwargs: Any) -> None:
    print(*args, file=fout, **kwargs)


# Code start
def max_node_count_in_tree_of_height(height: int) -> int:
    # return 2 ** height - 1
    return (1 << height) - 1


def min_node_count_in_tree_of_height(height: int) -> int:
    # return 2 * height - 1
    return max((height << 1) - 1, 0)


MODULO = 9901
NODE_TOTAL, MAX_HEIGHT = map(int, fin.readline().split())
if (NODE_TOTAL & 1) == 0:
    fprint(0)
    raise SystemExit

dp_no_more_than = [[0] * (NODE_TOTAL + 1) for _ in range(MAX_HEIGHT + 1)]
dp_exact = [[0] * (NODE_TOTAL + 1) for _ in range(MAX_HEIGHT + 1)]
dp_exact[1][1] = 1
for height in range(2, MAX_HEIGHT + 1):
    for node_count in range(1, NODE_TOTAL + 1, 2):
        half_node_count = (node_count - 1) // 2
        for left_child_node_count in range(1, half_node_count + 1, 2):
            right_child_node_count = node_count - 1 - left_child_node_count
            multiplier = 1 + int(left_child_node_count != half_node_count)
            dp_exact[height][node_count] += multiplier * (
                dp_exact[height - 1][left_child_node_count]
                * dp_no_more_than[height - 2][right_child_node_count]
                + dp_exact[height - 1][right_child_node_count]
                * dp_no_more_than[height - 2][left_child_node_count]
                + dp_exact[height - 1][left_child_node_count]
                * dp_exact[height - 1][right_child_node_count]
            )
            dp_exact[height][node_count] %= MODULO
    for node_count in range(1, NODE_TOTAL + 1, 2):
        dp_no_more_than[height - 1][node_count] = (
            dp_exact[height - 1][node_count] + dp_no_more_than[height - 2][node_count]
        ) % MODULO
fprint(dp_exact[MAX_HEIGHT][NODE_TOTAL])
# Code end


# # Original, longer but accurately explains-itself-code
# dp_no_more_than = [[0] * (NODE_TOTAL + 1) for _ in range(MAX_HEIGHT + 1)]
# for height in range(1, MAX_HEIGHT):
#     dp_no_more_than[height][1] = 1
#     for node_count in range(
#         3, min(NODE_TOTAL, max_node_count_in_tree_of_height(height)) + 1, 2
#     ):
#         for left_child_node_count in range(
#             max(1, node_count - 1 - max_node_count_in_tree_of_height(height - 1)),
#             min(max_node_count_in_tree_of_height(height - 1), node_count - 1 - 1) + 1,
#             2,
#         ):
#             right_child_node_count = node_count - 1 - left_child_node_count
#             dp_no_more_than[height][node_count] += (
#                 dp_no_more_than[height - 1][left_child_node_count]
#                 * dp_no_more_than[height - 1][right_child_node_count]
#             ) % MODULO
#             dp_no_more_than[height][node_count] %= MODULO

# dp_exact = [[0] * (NODE_TOTAL + 1) for _ in range(MAX_HEIGHT + 1)]
# dp_exact[1][1] = 1
# for height in range(2, MAX_HEIGHT + 1):
#     for node_count in range(
#         min_node_count_in_tree_of_height(height),
#         min(NODE_TOTAL, max_node_count_in_tree_of_height(height)) + 1,
#         2,
#     ):
#         for left_child_node_count in range(
#             max(
#                 min_node_count_in_tree_of_height(height - 1),
#                 node_count - 1 - max_node_count_in_tree_of_height(height - 2),
#             ),
#             min(max_node_count_in_tree_of_height(height - 1), node_count - 1 - 1) + 1,
#             2,
#         ):
#             right_child_node_count = node_count - 1 - left_child_node_count
#             dp_exact[height][node_count] += (
#                 dp_exact[height - 1][left_child_node_count]
#                 * dp_no_more_than[height - 2][right_child_node_count]
#                 % MODULO
#             )
#             dp_exact[height][node_count] %= MODULO
#         dp_exact[height][node_count] <<= 1
#         dp_exact[height][node_count] %= MODULO
#         for left_child_node_count in range(
#             max(
#                 min_node_count_in_tree_of_height(height - 1),
#                 node_count - 1 - max_node_count_in_tree_of_height(height - 1),
#             ),
#             min(
#                 max_node_count_in_tree_of_height(height - 1),
#                 node_count - 1 - min_node_count_in_tree_of_height(height - 1),
#             )
#             + 1,
#             2,
#         ):
#             right_child_node_count = node_count - 1 - left_child_node_count
#             dp_exact[height][node_count] += (
#                 dp_exact[height - 1][left_child_node_count]
#                 * dp_exact[height - 1][right_child_node_count]
#                 % MODULO
#             )
#             dp_exact[height][node_count] %= MODULO
# # fprint(tuple(range(NODE_TOTAL + 1)))
# # fprint(*enumerate(dp_no_more_than), sep="\n")
# # fprint()
# # fprint(*enumerate(dp_exact), sep="\n")
# fprint(dp_exact[MAX_HEIGHT][NODE_TOTAL])
# # Code end
