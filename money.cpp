/*
ID: totheso1
LANG: C++14
TASK: money
*/

#include <algorithm>
#include <fstream>
#include <iterator>
#include <vector>

using namespace std;

static ifstream fin("money.in");
static ofstream fout("money.out");

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

static const int COIN_COUNT = fin_get<int>();
static const int TARGET = fin_get<int>();

int main() {
  vector<unsigned long long> count_collection(TARGET + 1);
  count_collection[0] = 1;
  int coin;
  while (fin >> coin) {
    for (int i = 0; i <= TARGET; ++i) {
      if (coin <= i) {
        count_collection[i] += count_collection[i - coin];
      }
    }
  }
  fout << count_collection[TARGET] << endl;
}
