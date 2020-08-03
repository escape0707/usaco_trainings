/*
ID: totheso1
LANG: C++14
TASK: combo
*/

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iterator>
#include <vector>

using namespace std;

static ifstream fin("combo.in");
static ofstream fout("combo.out");

#define endl '\n'

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

static constexpr int TOLERANCE = 2;
static constexpr int TOLERANCE_SPAN = TOLERANCE * 2 + 1;
static constexpr int DIALS_COUNT = 3;

static int N;

static int overlap(int i, int j) {
  if (N <= TOLERANCE_SPAN) {
    return N;
  }
  if (i > j) {
    swap(i, j);
  }
  return max(0, TOLERANCE_SPAN - min(j - i, i + N - j));
}

int main() {
  N = fin_get<int>();
  const auto john_combo = fin_get_collection<vector<int>>(DIALS_COUNT);
  const auto master_combo = fin_get_collection<vector<int>>(DIALS_COUNT);

  const int full_span_count =
      static_cast<int>(pow(min(N, TOLERANCE_SPAN), DIALS_COUNT)) * 2;
  int overlap_count = 1;
  for (int i = 0; i < DIALS_COUNT; ++i) {
    overlap_count *= overlap(john_combo[i], master_combo[i]);
  }
  fout << full_span_count - overlap_count << endl;
}
