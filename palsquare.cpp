/*
ID: totheso1
LANG: C++14
TASK: palsquare
*/

#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iterator>
#include <string>

using namespace std;

static ifstream fin("palsquare.in");
static ofstream fout("palsquare.out");

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

static string base_repr(int number, const int base = 2) {
  static const string digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

  string res;
  while (number) {
    res.push_back(digits[number % base]);
    number /= base;
  }
  reverse(begin(res), end(res));
  return res;
}

static bool is_palindrome(const string &s) {
  auto rb = crbegin(s);
  for (auto b = cbegin(s), e = b + (s.size() >> 1); b != e; ++b, ++rb) {
    if (*b != *rb) {
      return false;
    }
  }
  return true;
}

int main() {
  const int BASE = fin_get<int>();
  for (int num = 1; num <= 300; ++num) {
    const string square = base_repr(num * num, BASE);
    if (is_palindrome(square)) {
      fout << base_repr(num, BASE) << ' ' << square << endl;
    }
  }
}
