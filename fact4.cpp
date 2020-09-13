/*
ID: totheso1
LANG: C++14
TASK: fact4
*/

#include <algorithm>
#include <fstream>
#include <iterator>

using namespace std;

static ifstream fin("fact4.in");
static ofstream fout("fact4.out");

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

static const int N = fin_get<int>();

int main() {
  int ans = 1;
  int cnt_2 = 0;
  int cnt_5 = 0;
  for (int i = 2; i <= N; ++i) {
    int j = i;
    while (j % 2 == 0) {
      ++cnt_2;
      j /= 2;
    }
    while (j % 5 == 0) {
      ++cnt_5;
      j /= 5;
    }
    ans = ans * j % 10;
  }

  for (int i = cnt_2 - cnt_5; i; --i) {
    ans = ans * 2 % 10;
  }
  fout << ans << endl;
}
