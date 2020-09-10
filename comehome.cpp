/*
ID: totheso1
LANG: C++14
TASK: comehome
*/

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iterator>
#include <limits>
#include <utility>
#include <vector>

using namespace std;

static ifstream fin("comehome.in");
static ofstream fout("comehome.out");

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

static constexpr int PASTURE_COUNT = 26;
static const int PATH_COUNT = fin_get<int>();
static vector<vector<int>> shortest(
    PASTURE_COUNT * 2,
    vector<int>(PASTURE_COUNT * 2,
                numeric_limits<int>::max() /
                    2));  // Big enough, max_dist is 26 * 1000
static constexpr int ord_A = 'A';

static void initialize() {
  for (int i = 0, e = PASTURE_COUNT * 2; i < e; ++i) {
    shortest[i][i] = 0;
  }
  for (int i = 0; i < PATH_COUNT; ++i) {
    char a = fin_get<char>();
    char b = fin_get<char>();
    const int dist = fin_get<int>();
    bool test = isupper(a);
    a = toupper(a) - ord_A + static_cast<bool>(isupper(a)) * PASTURE_COUNT;
    b = toupper(b) - ord_A + static_cast<bool>(isupper(b)) * PASTURE_COUNT;
    shortest[a][b] = shortest[b][a] = min(shortest[a][b], dist);
  }
}

static pair<char, int> solve_with_floyd_warshell() {
  for (int k = 0, e = PASTURE_COUNT * 2; k < e; ++k) {
    for (int i = 0; i < e; ++i) {
      for (int j = 0; j < i; ++j) {
        shortest[i][j] = shortest[j][i] =
            min(shortest[i][j], shortest[i][k] + shortest[k][j]);
      }
    }
  }

  int who = -1;
  int ans = numeric_limits<int>::max();
  int i = 0;
  for (auto b = cbegin(shortest.back()) + PASTURE_COUNT,
            e = cend(shortest.back()) - 1;
       b < e; ++i, ++b) {
    const int dist = *b;
    if (dist < ans) {
      who = i;
      ans = dist;
    }
  }
  return {who + ord_A, ans};
}

static pair<char, int> solve_with_basic_dijkstra() {
  vector<bool> visited(PASTURE_COUNT * 2, false);
  for (int visited_count = 0, e = PASTURE_COUNT * 2; visited_count < e;
       ++visited_count) {
    int i = -1;
    int dist_si = numeric_limits<int>::max();
    int curr = -1;
    vector<int> &shortest_back = shortest.back();
    for (const int dist : shortest_back) {
      ++curr;
      if (!visited[curr] && dist < dist_si) {
        i = curr;
        dist_si = dist;
      }
    }
    if (PASTURE_COUNT <= i && i < PASTURE_COUNT * 2 - 1) {
      return {i - PASTURE_COUNT + ord_A, dist_si};
    }
    visited[i] = true;
    auto b = begin(shortest_back);
    for (const int dist_ij : shortest[i]) {
      *b = min(*b, dist_si + dist_ij);
      ++b;
    }
  }
}

int main() {
  initialize();
  const pair<char, int> p = solve_with_basic_dijkstra();
  fout << p.first << ' ' << p.second << endl;
}
