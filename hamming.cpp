/*
ID: totheso1
LANG: C++14
TASK: hamming
*/

#include <algorithm>
#include <bitset>
#include <fstream>
#include <iterator>
#include <vector>

using namespace std;

static ifstream fin("hamming.in");
static ofstream fout("hamming.out");

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

static constexpr int MAX_LENGTH_OF_BITS = 8;
static const int CODEWORD_COUNT = fin_get<int>();
static const int LENGTH_OF_BITS = fin_get<int>();
static const int HAMMING_DISTANCE = fin_get<int>();

static vector<bitset<MAX_LENGTH_OF_BITS>> codeword_collection = {0};

static void print_codeword_collection() {
  int i = -1;
  for (const auto &codeword : codeword_collection) {
    ++i;
    if (i != 0) {
      if (i % 10 == 0) {
        fout << endl;
      } else {
        fout << ' ';
      }
    }
    fout << codeword.to_ulong();
  }
  fout << endl;
}

static void solve_codeword_collection() {
  for (int number = 1, e = 1 << LENGTH_OF_BITS; number < e; ++number) {
    if (all_of(
            cbegin(codeword_collection), cend(codeword_collection),
            [number](const auto &codeword) {
              return (bitset<MAX_LENGTH_OF_BITS>(number) ^ codeword).count() >=
                     HAMMING_DISTANCE;
            })) {
      codeword_collection.emplace_back(number);
      if (codeword_collection.size() == CODEWORD_COUNT) {
        break;
      }
    }
  }
  print_codeword_collection();
}

int main() {
  solve_codeword_collection();
}
