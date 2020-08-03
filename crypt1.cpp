/*
ID: totheso1
LANG: C++14
TASK: crypt1
*/

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iterator>
#include <unordered_set>
#include <vector>

using namespace std;

static ifstream fin("crypt1.in");
static ofstream fout("crypt1.out");

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

static unordered_set<int> digit_set;

static vector<int> digits_Cartesian_product(const unordered_set<int> &digit_set,
                                            int length) {
  const int digit_cnt = digit_set.size();
  const int total = static_cast<int>(pow(digit_cnt, length));
  vector<int> res(total);
  for (int i = 1; i <= length; ++i) {
    for (auto b = begin(res), e = end(res); b != e;) {
      for (const int digit : digit_set) {
        for (int j = total / static_cast<int>(pow(digit_cnt, i)); j > 0; --j) {
          *b = *b * 10 + digit;
          ++b;
        }
      }
    }
  }
  return res;
}

static bool valid(int number) {
  const auto e = cend(digit_set);
  while (true) {
    if (digit_set.find(number % 10) == e) {
      return false;
    }
    number /= 10;
    if (number == 0) {
      return true;
    }
  }
}

int main() {
  int N = fin_get<int>();
  while (N--) {
    digit_set.emplace(fin_get<int>());
  }
  vector<int> multiplicand_collection = digits_Cartesian_product(digit_set, 3);
  vector<int> multiplier_collection = digits_Cartesian_product(digit_set, 2);

  int solution_count = 0;

  for (const int multiplicand : multiplicand_collection) {
    for (const int multiplier : multiplier_collection) {
      const int partial_product_1 = multiplicand * (multiplier % 10);
      if (partial_product_1 < 1000 && valid(partial_product_1)) {
        const int partial_product_2 = multiplicand * (multiplier / 10);
        if (partial_product_2 < 1000 and valid(partial_product_2)) {
          const int whole_product = multiplicand * multiplier;
          if (whole_product < 10000 and valid(whole_product)) {
            ++solution_count;
          }
        }
      }
    }
  }
  fout << solution_count << endl;
}
