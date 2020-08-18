/*
ID: totheso1
LANG: C++14
TASK: sort3
*/

#include <algorithm>
#include <array>
#include <fstream>
#include <iterator>
#include <vector>

using namespace std;

static ifstream fin("sort3.in");
static ofstream fout("sort3.out");

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

int main() {
  constexpr int MAX_NUMBER = 3;
  const int NUMBER_COUNT = fin_get<int>();
  const auto number_collection = fin_get_collection<vector<int>>(NUMBER_COUNT);
  array<int, MAX_NUMBER + 1> count_by_number_collection = {};
  for (const int number : number_collection) {
    ++count_by_number_collection[number];
  }
  array<array<int, MAX_NUMBER + 1>, MAX_NUMBER + 1>
      count_by_position_then_number_collection = {};
  auto b = cbegin(number_collection), e = b;
  for (int position = 1; position <= 3; ++position) {
    e += count_by_number_collection[position];
    for (; b < e; ++b) {
      ++count_by_position_then_number_collection[position][*b];
    }
  }
  int answer = 0;
  for (int i = 1; i <= 3; ++i) {
    for (int j = 1; j < i; ++j) {
      answer += min(count_by_position_then_number_collection[i][j],
                    count_by_position_then_number_collection[j][i]);
    }
  }
  answer += 2 * (max(count_by_position_then_number_collection[1][2],
                     count_by_position_then_number_collection[2][1]) -
                 min(count_by_position_then_number_collection[1][2],
                     count_by_position_then_number_collection[2][1]));
  fout << answer << endl;
}
