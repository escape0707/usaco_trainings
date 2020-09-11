/*
ID: totheso1
LANG: C++14
TASK: inflate
*/

#include <algorithm>
#include <fstream>
#include <iterator>
#include <vector>

using namespace std;

static ifstream fin("inflate.in");
static ofstream fout("inflate.out");

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

static const int TIME_TOTAL = fin_get<int>();
static const int CATEGORY_COUNT = fin_get<int>();
static vector<int> max_point(TIME_TOTAL + 1, 0);

int main() {
  for (int point, minute; fin >> point >> minute;) {
    for (auto b = begin(max_point) + minute, e = end(max_point); b < e; ++b) {
      *b = max(*b, *(b - minute) + point);
    }
  }
  fout << max_point.back() << endl;
}
