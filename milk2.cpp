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

using milking_event = pair<int, bool>;

int main() {
  vector<milking_event> events;
  for (int number_of_milkings = fin_get<int>(); number_of_milkings;
       --number_of_milkings) {
    events.emplace_back(fin_get<int>(), false);
    events.emplace_back(fin_get<int>(), true);
  }
  sort(begin(events), end(events));
  int longest_milking = 0;
  int longest_idleing = 0;
  int start = 0;
  int end = 0;
  int milking = 0;
  for (const milking_event &event : events) {
    const int time = event.first;
    const bool farmer_leaving = event.second;
    if (milking == 0 && !farmer_leaving) {
      start = time;
      if (end != 0) {
        longest_idleing = max(longest_idleing, start - end);
      }
    }
    if (milking == 1 && farmer_leaving) {
      end = time;
      longest_milking = max(longest_milking, end - start);
    }
    milking -= farmer_leaving * 2 - 1;
  }
  fout << longest_milking << ' ' << longest_idleing << endl;
}
