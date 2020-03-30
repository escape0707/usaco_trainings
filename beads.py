"""
ID: totheso1
LANG: PYTHON3
TASK: beads
"""

fin = open("beads.in", "r")
fout = open("beads.out", "w")


def fprint(*args, **kwargs):
    print(*args, file=fout, **kwargs)


# Code start
number_of_beads = int(fin.readline())
beads = fin.readline()[:-1] * 2

# DP solution start
# available_left = [0] * number_of_beads * 2
# available_right = available_left[:]


# def count_available_beads(start, stop, step, store):
#     previous_color = beads[start - step]
#     continuous_white = int(previous_color == "w")
#     for i in range(start, stop, step):
#         if beads[i] == "w":
#             continuous_white += 1
#             store[i] = store[i - step] + 1
#         else:
#             if "w" != previous_color != beads[i]:
#                 store[i] = continuous_white
#             else:
#                 store[i] = store[i - step] + 1
#             previous_color = beads[i]
#             continuous_white = 0


# count_available_beads(1, len(beads), 1, available_left)
# count_available_beads(len(beads) - 2, -1, -1, available_right)
# fprint(
#     min(
#         number_of_beads,
#         2
#         + max(
#             available_left[i - 1 + number_of_beads] + available_right[i]
#             for i in range(number_of_beads)
#         ),
#     )
# )
# DP solution end

# One pass solution start
right_color = None
left_count = left_white = right_count = right_white = 0
current_split_count = left_count + left_white + right_count + right_white
max_split_count = 0
for bead in beads:
    if bead == "w":
        right_white += 1
        current_split_count += 1
    else:
        if bead == right_color:
            right_count += right_white + 1
            right_white = 0
            current_split_count += 1
        else:
            if current_split_count > max_split_count:
                max_split_count = current_split_count
            # same result as re-compute current_split_count
            current_split_count -= left_count - 1
            right_color = bead
            left_count = left_white + right_count
            left_white = right_white
            right_count = 1
            right_white = 0
max_split_count = min(number_of_beads, max(max_split_count, current_split_count))
fprint(max_split_count)
# One pass solution end
# Code end
