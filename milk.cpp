/*
ID: totheso1
LANG: C++14
TASK: milk
*/

#include <algorithm>
#include <array>
#include <fstream>
#include <iterator>

using namespace std;

static ifstream fin("milk.in");
static ofstream fout("milk.out");

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

static constexpr int MAX_PRICE = 1000;

int main() {
  int N = fin_get<int>();
  int M = fin_get<int>();
  array<int, MAX_PRICE + 1> count_by_cost = {};
  for (int _ = 0; _ < M; ++_) {
    const int cost = fin_get<int>();
    const int count = fin_get<int>();
    count_by_cost[cost] += count;
  }

  int total_cost = 0;
  int current_cost = 0;
  for (const int count : count_by_cost) {
    const int buy_unit = min(count, N);
    total_cost += current_cost++ * buy_unit;
    N -= buy_unit;
    if (N == 0) {
      break;
    }
  }
  fout << total_cost << endl;
}
