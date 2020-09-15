"""
ID: totheso1
LANG: PYTHON3
TASK: milk2
"""

fin = open("milk2.in", "r")
fout = open("milk2.out", "w")


def fprint(*args, **kwargs) -> None:
    print(*args, file=fout, **kwargs)


# Code start
# Simple event counting with bucket sort, O(t), start
# TIME_MAX = 1000000
# new_beginner_count_by_time = [0] * TIME_MAX
# number_of_milkings = int(fin.readline())
# for line in fin:
#     start, end = map(int, line.split())
#     new_beginner_count_by_time[start] += 1
#     new_beginner_count_by_time[end] -= 1

# longest_milking = longest_idling = 0
# start = end = 0
# milking = 0
# for i, count in enumerate(new_beginner_count_by_time):
#     if milking == 0 and count:
#         start = i
#         if end:
#             longest_idling = max(longest_idling, start - end)
#     if milking and milking == -count:
#         end = i
#         longest_milking = max(longest_milking, end - start)
#     milking += count

# fprint(longest_milking, longest_idling)
# Simple event counting with bucket sort, O(N + t), end

# Same event counting with discretization and system sort, O(NlogN), start
number_of_milkings = int(fin.readline())
events = []
for line in fin:
    start, end = map(int, line.split())
    events.append((start, False))
    events.append((end, True))
events.sort()

longest_milking = longest_idling = 0
start = end = 0
milking = 0
for time, farmer_leaving in events:
    if milking == 0 and not farmer_leaving:
        start = time
        if end:
            longest_idling = max(longest_idling, start - end)
    if milking == 1 and farmer_leaving:
        end = time
        longest_milking = max(longest_milking, end - start)
    milking -= farmer_leaving * 2 - 1

fprint(longest_milking, longest_idling)
# Same event counting with discretization and system sort, O(NlogN), end
# Code end
