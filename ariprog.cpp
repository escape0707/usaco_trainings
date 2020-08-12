/*
ID: totheso1
LANG: C++14
TASK: ariprog
*/

#include <algorithm>
#include <fstream>
#include <iterator>
#include <utility>
#include <vector>

using namespace std;

static ifstream fin("ariprog.in");
static ofstream fout("ariprog.out");

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
  const int LENGTH_OF_PROGRESSION = fin_get<int>();
  const int MAX_FACTOR = fin_get<int>();
  const int MAX_NUMBER = MAX_FACTOR * MAX_FACTOR * 2;

  vector<bool> available(MAX_NUMBER + 1, false);
  vector<int> number_collection;
  number_collection.reserve(MAX_NUMBER + 1);
  for (int i = 0; i <= MAX_FACTOR; ++i) {
    for (int j = 0; j <= i; ++j) {
      const int number = i * i + j * j;
      if (!available[number]) {
        available[number] = true;
        number_collection.push_back(number);
      }
    }
  }
  sort(begin(number_collection), end(number_collection));

  const int back = number_collection.back();
  vector<pair<int, int>> result;
  for (auto i = cbegin(number_collection), e = cend(number_collection); i < e;
       ++i) {
    const int num_a = *i;
    for (auto j = i + 1; j < e; ++j) {
      const int num_b = *j;
      const int diff = num_b - num_a;
      const int last_num = num_a + diff * (LENGTH_OF_PROGRESSION - 1);
      if (back < last_num) {
        break;
      }
      bool found = true;
      for (int next_num = num_b + diff; next_num <= last_num;
           next_num += diff) {
        if (!available[next_num]) {
          found = false;
          break;
        }
      }
      if (found) {
        result.emplace_back(diff, num_a);
      }
    }
  }
  sort(begin(result), end(result));

  if (result.empty()) {
    fout << "NONE" << endl;
  } else {
    for (const auto &p : result) {
      fout << p.second << ' ' << p.first << endl;
    }
  }
}
