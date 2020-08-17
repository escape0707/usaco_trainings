/*
ID: totheso1
LANG: C++14
TASK: frac1
*/

#include <algorithm>
#include <fstream>
#include <iterator>
#include <utility>
#include <vector>

using namespace std;

static ifstream fin("frac1.in");
static ofstream fout("frac1.out");

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

using fraction = pair<int, int>;

static int gcd(int a, int b) {
  if (b == 0) {
    return 0;
  }
  a = abs(a);
  b = abs(b);
  while (b != 0) {
    a = exchange(b, a % b);
  }
  return a;
}

static bool coprime(const int a, const int b) {
  return gcd(a, b) == 1;
}

static bool fraction_less(const fraction &p1, const fraction &p2) {
  return p1.first * p2.second < p2.first * p1.second;
}

int main() {
  const int MAX_DENOMINATOR = fin_get<int>();
  vector<fraction> fraction_collection;
  for (int denominator = 1; denominator <= MAX_DENOMINATOR; ++denominator) {
    for (int numerator = 0; numerator <= denominator; ++numerator) {
      if (coprime(numerator, denominator))
      fraction_collection.emplace_back(numerator, denominator);
    }
  }
  sort(begin(fraction_collection), end(fraction_collection), fraction_less);
  for (const auto &fraction : fraction_collection) {
    fout << fraction.first << '/' << fraction.second << endl;
  }
}
