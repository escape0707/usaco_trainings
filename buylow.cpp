/*
ID: totheso1
LANG: C++14
TASK: buylow
*/

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iterator>
#include <limits>
#include <ostream>
#include <stdexcept>
#include <vector>

using namespace std;

// BigInt.h & BigInt.cpp Start
class BigInt {
  friend std::ostream &operator<<(std::ostream &os, const BigInt &big);

 public:
  BigInt();
  BigInt(long long i);
  // BigInt(std::string s);
  BigInt &operator+=(const BigInt &other);
  // BigInt &operator-=(const BigInt &other);

 private:
  static constexpr int base = 1000000000;
  bool positive;
  std::vector<int> data;
};

std::ostream &operator<<(std::ostream &os, const BigInt &rhs);
// BigInt operator+(BigInt lhs, BigInt rhs);
// BigInt operator-(BigInt lhs, BigInt rhs);

BigInt::BigInt() : BigInt(0) {}

BigInt::BigInt(long long i) {
  positive = i >= 0;
  if (i == numeric_limits<long long>::min()) {
    throw logic_error("NotImplemented.");  // Delegate to construct from string.
  }
  i = abs(i);
  while (i) {
    data.push_back(i % base);
    i /= base;
  }
}

BigInt &BigInt::operator+=(const BigInt &other) {
  // a += a seems to just work. But it IS dangerous.
  if (positive != other.positive) {
    throw logic_error("NotImplemented.");
  }
  data.resize(max(data.size(), other.data.size()));
  bool carry = false;
  auto b1 = begin(data);
  auto b2 = cbegin(other.data);
  const auto e1 = cend(data), e2 = cend(other.data);
  for (; b1 != e1; ++b1) {
    *b1 += ((b2 == e2) ? 0 : *b2++) + carry;
    carry = *b1 >= base;
    if (carry) {
      *b1 -= base;
    }
  }
  if (carry) {
    data.push_back(1);
  }
  return *this;
}

ostream &operator<<(ostream &os, const BigInt &big) {
  if (!big.positive && !(big.data[0] == 0 && big.data.size() == 1)) {
    os << '-';
  }
  auto b = crbegin(big.data);
  const auto e = crend(big.data);
  os << *b++;
  for (; b != e; ++b) {
    os << setw(9) << setfill('0') << *b;
  }
  return os;
}

// BigInt.h & BigInt.cpp End

static ifstream fin("buylow.in");
static ofstream fout("buylow.out");

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

static const int NUMBER_COUNT = fin_get<int>();
static const vector<int> number_collection = []() {
  vector<int> res = {numeric_limits<int>::max()};
  copy_n(istream_iterator<int>(fin), NUMBER_COUNT, back_inserter(res));
  return res;
}();

static void solve() {
  // longest_decreasing_sequence_including_current
  vector<int> dp_length(NUMBER_COUNT + 1, 0);
  // number_of_longest_sequence_ending_with_current_globally,
  vector<BigInt> dp_count(NUMBER_COUNT + 1, 0);
  dp_count[0] = 1;
  // if there exists a same element at j after current position i, we set
  // dp_count[i] to 0, and dp_count[j] will be the global sequence count for
  // this element
  for (int i = 1, e = number_collection.size(); i < e; ++i) {
    const int ai = number_collection[i];
    for (int j = 0; j < i; ++j) {
      const int aj = number_collection[j];
      if (aj == ai) {
        dp_count[j] = 0;
      }
      if (aj > ai) {
        if (dp_length[j] + 1 > dp_length[i]) {
          dp_length[i] = dp_length[j] + 1;
          dp_count[i] = dp_count[j];
        } else if (dp_length[j] + 1 == dp_length[i]) {
          dp_count[i] += dp_count[j];
        }
      }
    }
  }
  const int ans_length = *max_element(cbegin(dp_length), cend(dp_length));
  BigInt ans_count = 0;
  int i = -1;
  for (const BigInt &count : dp_count) {
    ++i;
    if (dp_length[i] == ans_length) {
      ans_count += count;
    }
  }
  fout << ans_length << ' ' << ans_count << endl;
}

int main() {
  solve();
}
