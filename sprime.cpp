/*
ID: totheso1
LANG: C++14
TASK: sprime
*/

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iterator>

using namespace std;

static ifstream fin("sprime.in");
static ofstream fout("sprime.out");

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

static bool is_prime(const int num) {
  if (num <= 1) {
    return false;
  }
  const int square_root_truncated = static_cast<int>(sqrt(num));
  for (int i = 2; i <= square_root_truncated; ++i) {
    if (num % i == 0) {
      return false;
    }
  }
  return true;
}

static void dfs(int num, const int need_to_append_count) {
  if (need_to_append_count == 0) {
    fout << num << endl;
    return;
  }
  num *= 10;
  for (const int i : {1, 3, 7, 9}) {
    const int new_num = num + i;
    if (is_prime(new_num)) {
      dfs(new_num, need_to_append_count - 1);
    }
  }
}

int main() {
  const int N = fin_get<int>();
  for (const int begin_with : {2, 3, 5, 7}) {
    dfs(begin_with, N - 1);
  }
}
