/*
ID: totheso1
LANG: C++14
TASK: cowtour
*/

#include <algorithm>
#include <array>
#include <cmath>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iterator>
#include <limits>
#include <numeric>
#include <vector>

using namespace std;

static ifstream fin("cowtour.in");
static ofstream fout("cowtour.out");

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

static const int PASTURE_COUNT = fin_get<int>();
static vector<array<int, 2>> coordinate;
static vector<vector<double>> shortest(
    PASTURE_COUNT,
    vector<double>(PASTURE_COUNT, numeric_limits<double>::max()));
static vector<int> belong;
static vector<int> set_size(PASTURE_COUNT, 1);
static vector<double> farthest(PASTURE_COUNT, 0.0);
static vector<double> diameter(PASTURE_COUNT, 0.0);

static int find(int i) {
  while (i != belong[i]) {
    i = belong[i] = belong[belong[i]];
  }
  return i;
}

static void unite(int i, int j) {
  i = find(i);
  j = find(j);
  if (i == j) {
    return;
  }
  if (set_size[i] < set_size[j]) {
    swap(i, j);
  }
  belong[j] = i;
  set_size[i] += set_size[j];
}

template <typename C>
static auto euclidean_distance(C a, C b) {
  using T = typename C::value_type;
  return sqrt(
      inner_product(cbegin(a), cend(a), cbegin(b), 0, plus<>(),
                    [](const T &i, const T &j) { return (i - j) * (i - j); }));
}

static double dist(const int i, const int j) {
  return euclidean_distance(coordinate[i], coordinate[j]);
}

static void initialize() {
  for (int i = 0; i < PASTURE_COUNT; ++i) {
    shortest[i][i] = 0;
    belong.push_back(i);
    const int x = fin_get<int>();
    const int y = fin_get<int>();
    coordinate.push_back({x, y});
  }
  for (int i = 0; i < PASTURE_COUNT; ++i) {
    fin.ignore(numeric_limits<streamsize>::max(), '\n');
    for (int j = 0; j < i; ++j) {
      if (fin.get() == '1') {
        unite(i, j);
        shortest[i][j] = shortest[j][i] = dist(i, j);
      }
    }
  }
}

static void solve() {
  const auto double_max = numeric_limits<double>::max();
  for (int k = 0; k < PASTURE_COUNT; ++k) {
    for (int i = 0; i < PASTURE_COUNT; ++i) {
      for (int j = 0; j < i; ++j) {
        if (shortest[i][k] == double_max || shortest[k][j] == double_max) {
          continue;
        }
        shortest[i][j] = shortest[j][i] =
            min(shortest[i][j], shortest[i][k] + shortest[k][j]);
      }
    }
  }

  for (int i = 0; i < PASTURE_COUNT; ++i) {
    for (int j = 0; j < PASTURE_COUNT; ++j) {
      if (shortest[i][j] != double_max) {
        farthest[i] = max(farthest[i], shortest[i][j]);
      }
    }
  }

  for (int i = 0; i < PASTURE_COUNT; ++i) {
    const int set_id = find(i);
    diameter[set_id] = max(diameter[set_id], farthest[i]);
  }

  double ans = double_max;
  for (int i = 0; i < PASTURE_COUNT; ++i) {
    for (int j = 0; j < i; ++j) {
      const int set_i = find(i);
      const int set_j = find(j);
      if (set_i != set_j) {
        ans = min(ans, max(max(diameter[set_i], diameter[set_j]),
                           farthest[i] + dist(i, j) + farthest[j]));
      }
    }
  }
  fout << fixed << setprecision(6) << ans << endl;
}

int main() {
  initialize();
  solve();
}
