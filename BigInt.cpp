#include "BigInt.h"

#include <iomanip>
#include <limits>
#include <stdexcept>

using namespace std;

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
