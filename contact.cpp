/*
ID: totheso1
LANG: C++14
TASK: contact
*/

#include <algorithm>
#include <bitset>
#include <fstream>
#include <iterator>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

static ifstream fin("contact.in");
static ofstream fout("contact.out");

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

static constexpr int MAX_LENGTH = 12;
static const int LOW = fin_get<int>();
static const int UP = fin_get<int>();
static const int OUTPUT_COUNT = fin_get<int>();

static void print_pattern(int pattern) {
  vector<bool> digit_reversed_collection;
  while (true) {
    const int digit = pattern & 1;
    pattern >>= 1;
    if (pattern == 0) {
      break;
    }
    digit_reversed_collection.push_back(digit);
  }
  copy(crbegin(digit_reversed_collection), crend(digit_reversed_collection),
       ostream_iterator<bool>(fout));
}

static void solve() {
  unordered_map<int, int> counter;
  vector<int> pattern_collection(MAX_LENGTH + 1, 0);
  vector<int> bitmask_collection;
  for (int i = 0; i < 13; ++i) {
    bitmask_collection.push_back((1 << i) - 1);
  }
  int read_count = 0;
  for (char c; fin >> c;) {
    ++read_count;
    for (int i = LOW; i <= UP; ++i) {
      int &pattern = pattern_collection[i];
      pattern = pattern << 1 & bitmask_collection[i] | 1 << i | c - '0';
      if (read_count >= i) {
        ++counter[pattern];
      }
    }
  }

  vector<pair<int, int>> record_collection;
  for (const auto &p : counter) {
    record_collection.emplace_back(-p.second, p.first);
  }
  sort(begin(record_collection), end(record_collection));
  auto i = cbegin(record_collection);
  const auto e = cend(record_collection);
  for (int frequency_count = 0; frequency_count < OUTPUT_COUNT;
       ++frequency_count) {
    if (i == e) {
      break;
    }
    const int count_opposite = i->first;
    auto j = find_if(next(i), e, [count_opposite](const auto &p) {
      return p.first != count_opposite;
    });
    fout << -count_opposite;
    for (int pattern_count = 0; i < j; ++i, ++pattern_count) {
      fout << (pattern_count % 6 == 0 ? endl : ' ');
      print_pattern(i->second);
    }
    fout << endl;
  }
}

int main() {
  solve();
}
