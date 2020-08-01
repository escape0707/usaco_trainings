/*
ID: totheso1
LANG: C++14
TASK: barn1
*/

#include <algorithm>
#include <fstream>
#include <iterator>
#include <numeric>
#include <vector>

using namespace std;

static ifstream fin("barn1.in");
static ofstream fout("barn1.out");

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

int main() {
  const int max_purchase = fin_get<int>();
  const int total_stall = fin_get<int>();
  const int total_cow = fin_get<int>();
  auto occupied_stall = fin_get_collection<vector<int>>(total_cow);

  sort(begin(occupied_stall), end(occupied_stall));

  vector<int> gap_length_collection;
  adjacent_difference(cbegin(occupied_stall), cend(occupied_stall),
                      back_inserter(gap_length_collection));
  swap(gap_length_collection.front(), gap_length_collection.back());
  gap_length_collection.pop_back();
  for (int &gap_length : gap_length_collection) {
    --gap_length;
  }
  sort(begin(gap_length_collection), end(gap_length_collection));

  fout << total_cow + accumulate(cbegin(gap_length_collection),
                                 cbegin(gap_length_collection) +
                                     max(0, total_cow - max_purchase),
                                 0)
       << endl;
}
