/*
ID: totheso1
LANG: C++14
TASK: range
*/

#include <algorithm>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>

using namespace std;

static ifstream fin("range.in");
static ofstream fout("range.out");

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

static const int SIDE_SIZE = fin_get<int>();
static auto dp = []() {
  vector<vector<bool>> res;
  res.reserve(SIDE_SIZE);
  for (string s; fin >> s;) {
    vector<bool> row;
    row.reserve(SIDE_SIZE);
    transform(cbegin(s), cend(s), back_inserter(row),
              [](const char c) { return c == '1'; });
    res.push_back(move(row));
  }
  return res;
}();

int main() {
  for (int square_side_size = 2; square_side_size <= SIDE_SIZE;
       ++square_side_size) {
    int count = 0;
    for (int i = 0, ei = SIDE_SIZE - square_side_size + 1; i < ei; ++i) {
      for (int j = 0, ej = SIDE_SIZE - square_side_size + 1; j < ej; ++j) {
        dp[i][j] = dp[i][j] && dp[i + 1][j] && dp[i][j + 1] && dp[i + 1][j + 1];
        count += dp[i][j];
      }
    }
    if (count == 0) {
      break;
    }
    fout << square_side_size << ' ' << count << endl;
  }
}
