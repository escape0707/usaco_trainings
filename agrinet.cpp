/*
ID: totheso1
LANG: C++14
TASK: agrinet
*/

#include <algorithm>
#include <fstream>
#include <iterator>
#include <vector>

using namespace std;

static ifstream fin("agrinet.in");
static ofstream fout("agrinet.out");

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

static const int FARM_COUNT = fin_get<int>();
static vector<vector<int>> dist(FARM_COUNT);

static void initialize() {
  for (vector<int> &row : dist) {
    for (int j = 0; j < FARM_COUNT; ++j) {
      row.push_back(fin_get<int>());
    }
  }
}

static void solve() {
  vector<int> closest(FARM_COUNT, numeric_limits<int>::max());
  closest[0] = 0;
  vector<bool> in_tree(FARM_COUNT, false);
  int ans = 0;
  for (int tree_size = 0; tree_size < FARM_COUNT; ++tree_size) {
    int i = -1;
    int dist_i = numeric_limits<int>::max();
    int curr = -1;
    for (const int d : closest) {
      ++curr;
      if (!in_tree[curr] && d < dist_i) {
        i = curr;
        dist_i = d;
      }
    }
    ans += dist_i;
    in_tree[i] = true;
    transform(cbegin(closest), cend(closest), cbegin(dist[i]), begin(closest),
              [](const int closest_j, const int dist_ij) {
                return min(closest_j, dist_ij);
              });
  }
  fout << ans << endl;
}

int main() {
  initialize();
  solve();
}
