/*
ID: totheso1
LANG: C++14
TASK: theme
*/

#include <algorithm>
#include <fstream>
#include <iterator>
#include <vector>

using namespace std;

static ifstream fin("theme.in");
static ofstream fout("theme.out");

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

static const int NOTE_COUNT = fin_get<int>();
static const vector<int> arr = []() {
  vector<int> res;
  res.reserve(NOTE_COUNT - 1);
  istream_iterator<int> b(fin), e;
  for (int prev = *b++; b != e; ++b) {
    res.push_back(*b - prev);
    prev = *b;
  }
  return res;
}();

static void solve() {
  int ans = 0;
  for (int offset = 0, diff_count = NOTE_COUNT - 1; offset < diff_count;
       ++offset) {
    int same_count = 0;
    for (int i = 0, e = diff_count - offset; i < e; ++i) {
      if (arr[i] == arr[i + offset]) {
        ++same_count;
        if (offset <= same_count) {
          break;
        }
        ans = max(ans, same_count);
      } else {
        same_count = 0;
      }
    }
  }
  fout << (ans >= 4 ? ans + 1 : 0) << endl;
}

int main() {
  solve();
}
