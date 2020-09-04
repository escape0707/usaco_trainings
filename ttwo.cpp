/*
ID: totheso1
LANG: C++14
TASK: ttwo
*/

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iterator>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

static ifstream fin("ttwo.in");
static ofstream fout("ttwo.out");

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

static constexpr int EDGE_LENGTH = 10;
static constexpr int DIRECTION_COUNT = 4;
static vector<vector<bool>> is_obstacle = {vector<bool>(EDGE_LENGTH + 2, true)};
static tuple<int, int, int> farmer;
static tuple<int, int, int> cow;

static void initialize() {
  for (int i = 0; i < EDGE_LENGTH; ++i) {
    vector<bool> row = {true};
    for (int j = 0; j < EDGE_LENGTH; ++j) {
      const char c = fin_get<char>();
      if (c == '*') {
        row.push_back(true);
      } else {
        row.push_back(false);
        if (c == 'F') {
          farmer = {i + 1, j + 1, 0};
        } else if (c == 'C') {
          cow = {i + 1, j + 1, 0};
        }
      }
    }
    row.push_back(true);
    is_obstacle.push_back(move(row));
  }
  is_obstacle.emplace_back(EDGE_LENGTH + 2, true);
}

static tuple<int, int, int> next_state(const tuple<int, int, int> &state) {
  static constexpr array<pair<int, int>, DIRECTION_COUNT> direction_collection =
      {{{-1, 0}, {0, 1}, {1, 0}, {0, -1}}};
  const int i = get<0>(state);
  const int j = get<1>(state);
  const int direction = get<2>(state);
  const pair<int, int> &diff = direction_collection[direction];
  const int new_i = i + diff.first;
  const int new_j = j + diff.second;
  if (is_obstacle[new_i][new_j]) {
    return {i, j, (direction + 1) % DIRECTION_COUNT};
  }
  return {new_i, new_j, direction};
}

static void solve() {
  int ans = 0;
  for (int step = 0, e = static_cast<int>(
                         pow((EDGE_LENGTH * EDGE_LENGTH) * DIRECTION_COUNT, 2));
       step < e; ++step) {
    if (get<0>(farmer) == get<0>(cow) && get<1>(farmer) == get<1>(cow)) {
      ans = step;
      break;
    }
    farmer = next_state(farmer);
    cow = next_state(cow);
  }
  fout << ans << endl;
}

int main() {
  initialize();
  solve();
}
