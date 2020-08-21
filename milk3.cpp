/*
ID: totheso1
LANG: C++14
TASK: milk3
*/

#include <algorithm>
#include <array>
#include <fstream>
#include <iterator>
#include <vector>

using namespace std;

static ifstream fin("milk3.in");
static ofstream fout("milk3.out");

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

static array<int, 3> capacity_collection;
static array<int, 3> milk;
static vector<vector<vector<bool>>> tried;
static vector<bool> possibilities_collection;

static void dfs() {
  const int a = milk[0];
  const int b = milk[1];
  const int c = milk[2];
  if (tried[a][b][c]) {
    return;
  }
  tried[a][b][c] = true;
  if (a == 0) {
    possibilities_collection[c] = true;
  }
  for (int &from_milk : milk) {
    if (from_milk > 0) {
      int to_bucket = -1;
      for (int &to_milk : milk) {
        ++to_bucket;
        const int to_available = capacity_collection[to_bucket] - to_milk;
        if (to_available > 0) {
          const int transfer = min(from_milk, to_available);
          from_milk -= transfer;
          to_milk += transfer;
          dfs();
          to_milk -= transfer;
          from_milk += transfer;
        }
      }
    }
  }
}

int main() {
  copy_n(istream_iterator<int>(fin), 3, begin(capacity_collection));
  tried.assign(
      capacity_collection[0] + 1,
      vector<vector<bool>>(capacity_collection[1] + 1,
                           vector<bool>(capacity_collection[2] + 1, false)));
  possibilities_collection.assign(capacity_collection[2] + 1, false);
  milk[2] = capacity_collection[2];
  dfs();
  bool printed = false;
  int liter = -1;
  for (const bool possible : possibilities_collection) {
    ++liter;
    if (possible) {
      if (printed) {
        fout << ' ';
      }
      printed = true;
      fout << liter;
    }
  }
  fout << endl;
}
