#include <ostream>
#include <vector>

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
