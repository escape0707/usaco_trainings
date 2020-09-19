/*
ID: totheso1
LANG: C++14
TASK: camelot
*/

#include <algorithm>
#include <array>
#include <cstdlib>
#include <fstream>
#include <iterator>
#include <limits>
#include <numeric>
#include <utility>
#include <vector>

using namespace std;

static ifstream fin("camelot.in");
static ofstream fout("camelot.out");

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

static const int ROW_COUNT = fin_get<int>();
static const int COLUMN_COUNT = fin_get<int>();
static const auto king_location = []() -> array<int, 2> {
  const int i = fin_get<char>();
  const int j = fin_get<int>();
  return {j - 1, i - 'A'};
}();
static const auto knight_location_collection = []() {
  vector<array<int, 2>> res;
  char king_col;
  int king_row;
  while (fin >> king_col >> king_row) {
    res.push_back({king_row - 1, king_col - 'A'});
  }
  return res;
}();

static void solve() {
  constexpr array<array<int, 2>, 8> knight_move_collection = {
      {{-2, 1}, {-1, 2}, {1, 2}, {2, 1}, {2, -1}, {1, -2}, {-1, -2}, {-2, -1}}};

  const auto chebyshev_distance = [](const auto &vector_a,
                                     const auto &vector_b) {
    return inner_product(
        cbegin(vector_a), cend(vector_a), cbegin(vector_b), 0,
        [](const auto &a, const auto &b) { return max(a, b); },
        [](const auto &a, const auto &b) { return abs(a - b); });
  };

  const auto bfs_dist = [&](const int start_i,
                            const int start_j) -> vector<vector<int>> {
    vector<vector<int>> res(
        ROW_COUNT, vector<int>(COLUMN_COUNT, numeric_limits<int>::max()));
    vector<vector<bool>> visited(ROW_COUNT, vector<bool>(COLUMN_COUNT, false));
    visited[start_i][start_j] = true;
    vector<array<int, 2>> que = {{start_i, start_j}};
    for (int step_count = 0; !que.empty(); ++step_count) {
      decltype(que) next_que;
      for (const auto &arr : que) {
        const int curr_i = get<0>(arr);
        const int curr_j = get<1>(arr);
        res[curr_i][curr_j] = step_count;
        for (const auto &arr : knight_move_collection) {
          const int new_i = curr_i + get<0>(arr);
          const int new_j = curr_j + get<1>(arr);
          if (0 <= new_i && new_i < ROW_COUNT && 0 <= new_j &&
              new_j < COLUMN_COUNT && !visited[new_i][new_j]) {
            visited[new_i][new_j] = true;
            next_que.push_back({new_i, new_j});
          }
        }
      }
      que = move(next_que);
    }
    return res;
  };

  const auto bfs_find_max_step_reduce = [&](const vector<vector<int>> &dist,
                                            const int king_direct_dist) -> int {
    vector<vector<bool>> visited(ROW_COUNT, vector<bool>(COLUMN_COUNT, false));
    vector<pair<int, array<int, 2>>> knight_collection;
    for (const auto &knight_location : knight_location_collection) {
      knight_collection.emplace_back(
          king_direct_dist +
              dist[get<0>(knight_location)][get<1>(knight_location)],
          knight_location);
    }
    sort(begin(knight_collection), end(knight_collection));
    int max_step_reduced = 0;
    vector<array<int, 2>> que;
    if (knight_location_collection.empty()) {
      return 0;
    }
    for (int direct_dist_minus_step_count = knight_collection.back().first;
         true; --direct_dist_minus_step_count) {
      while (!knight_collection.empty() &&
             knight_collection.back().first == direct_dist_minus_step_count) {
        auto &knight_location = knight_collection.back().second;
        visited[get<0>(knight_location)][get<1>(knight_location)] = true;
        que.push_back(move(knight_location));
        knight_collection.pop_back();
      }
      if (que.empty()) {
        break;
      }
      decltype(que) next_que;
      for (const auto &curr_location : que) {
        const int curr_i = get<0>(curr_location);
        const int curr_j = get<1>(curr_location);
        max_step_reduced =
            max(max_step_reduced,
                direct_dist_minus_step_count -
                    (chebyshev_distance(curr_location, king_location) +
                     dist[curr_i][curr_j]));
        for (const auto &arr : knight_move_collection) {
          const int new_i = curr_i + get<0>(arr);
          const int new_j = curr_j + get<1>(arr);
          if (0 <= new_i && new_i < ROW_COUNT && 0 <= new_j &&
              new_j < COLUMN_COUNT && !visited[new_i][new_j]) {
            visited[new_i][new_j] = true;
            next_que.push_back({new_i, new_j});
          }
        }
      }
      que = move(next_que);
    }
    return max_step_reduced;
  };

  int ans = numeric_limits<int>::max();
  for (int gathering_point_i = 0; gathering_point_i < ROW_COUNT;
       ++gathering_point_i) {
    for (int gathering_point_j = 0; gathering_point_j < COLUMN_COUNT;
         ++gathering_point_j) {
      const int king_direct_dist = chebyshev_distance(
          king_location, array<int, 2>{gathering_point_i, gathering_point_j});
      vector<vector<int>> dist = bfs_dist(gathering_point_i, gathering_point_j);
      int step = king_direct_dist;
      for (const auto &knight_location : knight_location_collection) {
        const int knight_dist =
            dist[get<0>(knight_location)][get<1>(knight_location)];
        if (knight_dist == numeric_limits<int>::max()) {
          step = -1;
          break;
        }
        step += knight_dist;
      }
      if (step == -1) {
        continue;
      }
      step -= bfs_find_max_step_reduce(dist, king_direct_dist);
      ans = min(ans, step);
    }
  }
  fout << ans << endl;
}

int main() {
  solve();
}
