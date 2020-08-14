/*
ID: totheso1
LANG: C++14
TASK: pprime
*/

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iterator>
#include <string>

using namespace std;

static ifstream fin("pprime.in");
static ofstream fout("pprime.out");

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

static int next_palindrome(const int num) {
  string s = to_string(num);
  if (all_of(cbegin(s), cend(s), [](const char c) { return c == '9'; })) {
    return num + 2;
  }
  const int length = s.length();
  const int half = (length + 1) / 2;
  const auto rb_first_half = rend(s) - half;
  const auto re_first_half = rend(s);
  const auto b_last_half = end(s) - half;
  const auto e_last_half = end(s);
  if (!lexicographical_compare(b_last_half, e_last_half, rb_first_half,
                               re_first_half)) {
    auto iter = rb_first_half;
    while (*iter == '9') {
      *iter = '0';
      ++iter;
    }
    ++*iter;
  }
  copy(rb_first_half, re_first_half, b_last_half);
  return stoi(s);
}

static bool is_prime(const int num) {
  if (num <= 1) {
    return false;
  }
  const int square_root_truncated = static_cast<int>(sqrt(num));
  for (int i = 2; i <= square_root_truncated; ++i) {
    if (num % i == 0) {
      return false;
    }
  }
  return true;
}

int main() {
  const int a = fin_get<int>();
  const int b = fin_get<int>();
  for (int palindrome = next_palindrome(a - 1); palindrome <= b;
       palindrome = next_palindrome(palindrome)) {
    if (is_prime(palindrome)) {
      fout << palindrome << endl;
    }
  }
}
