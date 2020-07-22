/*
ID: totheso1
LANG: C++14
TASK: dualpal
*/

#include <fstream>
#include <iterator>
#include <vector>

using namespace std;

static ifstream fin("dualpal.in");
static ofstream fout("dualpal.out");

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

static vector<int> base10_to_baseN(int num, const int base) {
  vector<int> ret;
  while (num) {
    ret.push_back(num % base);
    num /= base;
  }
  return ret;
}

static bool is_pal(const vector<int> &digits) {
  return equal(cbegin(digits), cbegin(digits) + digits.size() / 2, crbegin(digits));
}

static bool check_dual_pal(const int num) {
  int sum = 0;
  for (int base = 2; base <= 10; ++base) {
    if (is_pal(base10_to_baseN(num, base))) {
      ++sum;
      if (sum == 2) {
        return true;
      }
    }
  }
  return false;
}

int main() {
  const int N = fin_get<int>();
  const int S = fin_get<int>();

  for (int num = S + 1, remain = N; remain > 0; ++num) {
    if (check_dual_pal(num)) {
      fout << num << endl;
      --remain;
    }
  }
}
