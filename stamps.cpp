/*
ID: totheso1
LANG: C++14
TASK: stamps
NOTE:
    Either use unsigned char, short or use queue-and-pop
    for the Dynamic Programming array to avoid Memory Limit Exceeded.
    But as of 2020, it's very bad to have many different integer type
    to save memory usage,
    so I'll stick with queue-and-pop without using any integer type trick.
*/

#include <algorithm>
#include <deque>
#include <fstream>
#include <iterator>
#include <vector>

using namespace std;

static ifstream fin("stamps.in");
static ofstream fout("stamps.out");

#define endl '\n'

template <typename T>
T fin_get() {
  return *istream_iterator<T>(fin);
}

template <typename C>
C fin_get_collection(const int size) {
  C ret;
  copy_n(istream_iterator<typename C::value_type>(fin), size,
         back_inserter(ret));
  return ret;
}

static const int STAMP_TOTAL = fin_get<int>();
static const int STAMP_TYPE_COUNT = fin_get<int>();
static const vector<int> value_collection =
    fin_get_collection<vector<int>>(STAMP_TYPE_COUNT);

static void solve() {
  const int max_value =
      *max_element(cbegin(value_collection), cend(value_collection));
  deque<int> stamp_needed_collection = {0};
  for (int i = 1; true; ++i) {
    if (i - max_value > 0) {
      stamp_needed_collection.pop_front();
    }
    int min_needed = STAMP_TOTAL + 1;
    for (const int value : value_collection) {
      if (value <= i) {
        min_needed =
            min(min_needed, *prev(cend(stamp_needed_collection), value) + 1);
      }
    }
    if (min_needed == STAMP_TOTAL + 1) {
      fout << i - 1 << endl;
      break;
    }
    stamp_needed_collection.push_back(min_needed);
  }
}

int main() {
  solve();
}
