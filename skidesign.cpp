/*
ID: totheso1
LANG: C++14
TASK: skidesign
*/

#include <algorithm>
#include <fstream>
#include <iterator>
#include <limits>
#include <vector>

using namespace std;

static ifstream fin("skidesign.in");
static ofstream fout("skidesign.out");

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
  const auto hill_count = fin_get<int>();
  const auto hill_elevation_collection =
      fin_get_collection<vector<int>>(hill_count);
  int min_payment = numeric_limits<int>::max();
  for (int low = 0, high = 17; high <= 100; ++low, ++high) {
    int payment = 0;
    for (const int hill_elevation : hill_elevation_collection) {
      const int distance =
          max(0, max(hill_elevation - high, low - hill_elevation));
      payment += distance * distance;
    }
    if (payment < min_payment) {
      min_payment = payment;
    }
  }
  fout << min_payment << endl;
}
