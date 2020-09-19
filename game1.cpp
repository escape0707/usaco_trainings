/*
ID: totheso1
LANG: C++14
TASK: game1
*/

#include <algorithm>
#include <array>
#include <fstream>
#include <iterator>
#include <vector>

using namespace std;

static ifstream fin("game1.in");
static ofstream fout("game1.out");

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

static const int INT_COUNT = fin_get<int>();
static const auto int_collection = fin_get_collection<vector<int>>(INT_COUNT);

int main() {
  vector<array<int, 2>> dp;
  dp.reserve(INT_COUNT);
  for (const int i : int_collection) {
    dp.push_back({i, 0});
  }
  for (int length = 2; length <= INT_COUNT; ++length) {
    for (int left = 0, e = INT_COUNT - length + 1; left < e; ++left) {
      const int right = left + length - 1;
      dp[left] = max<array<int, 2>>(
          {int_collection[left] + dp[left + 1][1], dp[left + 1][0]},
          {int_collection[right] + dp[left][1], dp[left][0]});
    }
  }
  fout << get<0>(dp[0]) << ' ' << get<1>(dp[0]) << endl;
}
