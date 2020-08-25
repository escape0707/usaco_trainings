/*
ID: totheso1
LANG: C++14
TASK: preface
*/

#include <algorithm>
#include <array>
#include <fstream>
#include <iterator>
#include <unordered_map>

using namespace std;

static ifstream fin("preface.in");
static ofstream fout("preface.out");

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

static constexpr array<char, 7> encode = {'I', 'V', 'X', 'L', 'C', 'D', 'M'};
static const int TOTAL_PAGES = fin_get<int>();
static unordered_map<char, int> counter;

int main() {
  for (int i = 1; i <= TOTAL_PAGES; ++i) {
    for (int num = i, order = 0; num != 0; num /= 10, order += 2) {
      int digit = num % 10;
      if (digit == 9) {
        ++counter[encode[order]];
        ++counter[encode[order + 2]];
        continue;
      }
      if (digit == 4) {
        ++counter[encode[order + 1]];
        ++counter[encode[order]];
        continue;
      }
      if (digit >= 5) {
        ++counter[encode[order + 1]];
        digit -= 5;
      }
      counter[encode[order]] += digit;
    }
  }
  for (const char c : encode) {
    const int cnt = counter[c];
    if (cnt != 0) {
      fout << c << ' ' << cnt << endl;
    }
  }
}
