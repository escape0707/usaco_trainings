/*
ID: totheso1
LANG: C++14
TASK: numtri
*/

#include <algorithm>
#include <fstream>
#include <iterator>
#include <limits>
#include <vector>

using namespace std;

static ifstream fin("numtri.in");
static ofstream fout("numtri.out");

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

int main() {
  const int number_of_rows = fin_get<int>();
  vector<int> dp(number_of_rows, 0);
  for (int i = 0; i < number_of_rows; ++i) {
    for (int j = i; j != -1; --j) {
      const int num = fin_get<int>();
      dp[j] = max(dp[j], dp[j] + num);
      if (j > 0) {
        dp[j] = max(dp[j], dp[j - 1] + num);
      }
    }
  }
  fout << *max_element(cbegin(dp), cend(dp)) << endl;
}
