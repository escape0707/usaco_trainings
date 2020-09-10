/*
ID: totheso1
LANG: C++14
TASK: fracdec
*/

#include <algorithm>
#include <fstream>
#include <iterator>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

static ifstream fin("fracdec.in");
static ofstream fout("fracdec.out");

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

static string solve(int numerator, int denominator) {
  ostringstream oss;
  oss << numerator / denominator;
  numerator %= denominator;

  vector<int> fraction_collection;
  unordered_map<int, int> remainder_collection;
  for (int i = 0; true; ++i) {
    const auto iter = remainder_collection.find(numerator);
    const auto e = cend(remainder_collection);
    if (iter != e) {
      const auto loop_start = cbegin(fraction_collection) + iter->second;
      oss << '.';
      copy(cbegin(fraction_collection), loop_start, ostream_iterator<int>(oss));
      oss << '(';
      copy(loop_start, cend(fraction_collection), ostream_iterator<int>(oss));
      oss << ')';
      break;
    }
    remainder_collection[numerator] = i;
    numerator *= 10;
    fraction_collection.push_back(numerator / denominator);
    numerator %= denominator;
    if (numerator == 0) {
      oss << '.';
      for (const int digit : fraction_collection) {
        oss << digit;
      }
      break;
    }
  }
  return oss.str();
}

int main() {
  const int numerator = fin_get<int>();
  const int denominator = fin_get<int>();
  string res = solve(numerator, denominator);
  int i = 0;
  for (const char c : res) {
    fout << c;
    ++i;
    if (i % 76 == 0) {
      fout << endl;
    }
  }
  if (res.length() % 76 != 0) {
    fout << endl;
  }
}
