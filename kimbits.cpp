/*
ID: totheso1
LANG: C++14
TASK: kimbits
*/

#include <algorithm>
#include <fstream>
#include <iterator>
#include <limits>
#include <vector>

using namespace std;

static ifstream fin("kimbits.in");
static ofstream fout("kimbits.out");

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

static const auto LENGTH = fin_get<int>();
static const auto MAX_BIT_COUNT = fin_get<int>();
static const auto RANK = fin_get<unsigned>();
static vector<vector<unsigned>> count_collection(
    LENGTH + 1, vector<unsigned>(MAX_BIT_COUNT + 1, 1));

static void initialize() {
  for (int length = 1; length <= LENGTH; ++length) {
    for (int max_bit_count = 1; max_bit_count <= MAX_BIT_COUNT;
         ++max_bit_count) {
      count_collection[length][max_bit_count] =
          count_collection[length - 1][max_bit_count] +
          count_collection[length - 1][max_bit_count - 1];
    }
  }
}

static void print_bits(int length, int max_bit_count, unsigned rank) {
  while (length > 0) {
    const auto tmp = count_collection[length - 1][max_bit_count];
    if (rank <= tmp) {
      fout << 0;
    } else {
      fout << 1;
      --max_bit_count;
      rank -= tmp;
    }
    --length;
  }
  fout << endl;
}

int main() {
  initialize();
  print_bits(LENGTH, MAX_BIT_COUNT, RANK);
}
