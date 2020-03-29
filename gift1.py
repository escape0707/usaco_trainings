"""
ID: totheso1
LANG: PYTHON3
TASK: gift1
"""

fin = open("gift1.in", "r")
fout = open("gift1.out", "w")


def fprint(*args, **kwargs):
    print(*args, file=fout, **kwargs)


# Code start
number_of_people = int(fin.readline())

gain_by_name = {fin.readline(): 0 for _ in range(number_of_people)}

for i in range(number_of_people):
    giver_name = fin.readline()
    total, number_of_gifts = map(int, fin.readline().split())
    if number_of_gifts:
        gift = total // number_of_gifts
        gain_by_name[giver_name] -= gift * number_of_gifts
        for j in range(number_of_gifts):
            receiver_name = fin.readline()
            gain_by_name[receiver_name] += gift

for name, gain in gain_by_name.items():
    fprint(name.strip(), gain)
# Code end
