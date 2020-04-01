/*
ID: totheso1
LANG: C++14
TASK: milk2
*/

#include <algorithm>
#include <fstream>
#include <iterator>
#include <utility>
#include <vector>

using namespace std;

static ifstream fin("milk2.in");
static ofstream fout("milk2.out");

template <typename T>
T fin_get() {
    return *istream_iterator<T>(fin);
}

template <typename C>
C fin_get_collection(int size) {
    C ret;
    copy_n(istream_iterator<typename C::value_type>(fin), size,
           back_inserter(ret));
    return ret;
}

struct milking_event : pair<int, int> {
    using pair<int, int>::pair;
};

static bool operator<(const milking_event &p1, const milking_event &p2) {
    if (p1.first != p2.first) {
        return p1.first < p2.first;
    }
    return p1.second > p2.second;
}

int main() {
    const int number_of_milkings = fin_get<int>();
    vector<milking_event> events;
    for (int i = 0; i < number_of_milkings; ++i) {
        events.emplace_back(fin_get<int>(), 1);
        events.emplace_back(fin_get<int>(), -1);
    }
    sort(begin(events), end(events));

    int longest_milking = 0;
    int longest_idleing = 0;
    int start = 0;
    int end = 0;
    int milking = 0;
    for (const milking_event &event : events) {
        int time = event.first;
        int change_of_people_count = event.second;
        if (milking == 0 && change_of_people_count == 1) {
            start = time;
            if (end) {
                longest_idleing = max(longest_idleing, start - end);
            }
        }
        if (milking == 1 && change_of_people_count == -1) {
            end = time;
            longest_milking = max(longest_milking, end - start);
        }
        milking += change_of_people_count;
    }
    fout << longest_milking << ' ' << longest_idleing << endl;
}
