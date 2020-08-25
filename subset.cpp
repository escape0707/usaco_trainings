/*
ID: totheso1
LANG: C++14
TASK: subset
NOTE:
    You at least need `unsigned` to compute the DP array without overflow.
*/

#include <algorithm>
#include <fstream>
#include <iterator>
#include <vector>

using namespace std;

static ifstream fin("subset.in");
static ofstream fout("subset.out");

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

static const int NUMBER_COUNT = fin_get<int>();
static const int TOTAL = (1 + NUMBER_COUNT) * NUMBER_COUNT / 2;

int main() {
  if ((TOTAL & 1) == 1) {
    fout << 0 << endl;
    return 0;
  }
  const int HALF_TOTAL = TOTAL / 2;
  vector<unsigned> cnt(HALF_TOTAL + 1, 0);
  cnt[0] = 1;
  for (int number = 1; number <= NUMBER_COUNT; ++number) {
    for (int total = min(HALF_TOTAL, (1 + number) * number / 2);
         total >= number; --total) {
      cnt[total] += cnt[total - number];
    }
  }
  fout << cnt[HALF_TOTAL] / 2 << endl;
}
