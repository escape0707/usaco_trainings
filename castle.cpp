/*
ID: totheso1
LANG: C++14
TASK: castle
*/

#include <algorithm>
#include <array>
#include <fstream>
#include <iterator>
#include <limits>
#include <tuple>
#include <vector>

using namespace std;

static ifstream fin("castle.in");
static ofstream fout("castle.out");

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

// Initialization start.
static const int COL_CNT = fin_get<int>();
static const int ROW_CNT = fin_get<int>();
static const vector<vector<int>> castle_map = [] {
  vector<vector<int>> res;
  for (int i = 0; i < ROW_CNT; ++i) {
    res.push_back(fin_get_collection<vector<int>>(COL_CNT));
  }
  return res;
}();
static vector<vector<int>> component_id_by_index(ROW_CNT,
                                                 vector<int>(COL_CNT, -1));
static vector<int> component_size;
// Initialization end.

static void flood_fill(const int i, const int j, const int component_id) {
  static constexpr array<int, 4> encode = {1, 2, 4, 8};
  static constexpr array<pair<int, int>, 4> direction_collection = {
      {{0, -1}, {-1, 0}, {0, 1}, {1, 0}}};
  component_id_by_index[i][j] = component_id;
  ++component_size[component_id];
  for (int k = 0; k < 4; ++k) {
    const int bitmask = encode[k];
    const int direction_x = direction_collection[k].first;
    const int direction_y = direction_collection[k].second;
    const bool no_wall_on_direction = (~castle_map[i][j] & bitmask) != 0;
    if (no_wall_on_direction) {
      const int next_i = i + direction_x;
      const int next_j = j + direction_y;
      if (component_id_by_index[next_i][next_j] == -1) {
        flood_fill(next_i, next_j, component_id);
      }
    }
  }
}

static void solve_components() {
  int component_cnt = 0;
  int i = -1;
  for (const auto &row : component_id_by_index) {
    ++i;
    int j = -1;
    for (const auto &component_id : row) {
      ++j;
      if (component_id == -1) {
        component_size.push_back(0);
        flood_fill(i, j, component_cnt);
        ++component_cnt;
      }
    }
  }
  fout << component_cnt << endl;
  fout << *max_element(cbegin(component_size), cend(component_size)) << endl;
}

static void solve_wall_removal() {
  int largest_room_creatable = numeric_limits<int>::min();
  tuple<int, int, char> optimal_wall_to_remove;
  constexpr array<int, 2> encode = {2, 4};
  constexpr array<pair<int, int>, 2> direction_collection = {{{-1, 0}, {0, 1}}};
  constexpr array<char, 2> direction_char = {'N', 'E'};
  for (int j = 0; j < COL_CNT; ++j) {
    for (int i = ROW_CNT - 1; i != -1; --i) {
      const int current_component_id = component_id_by_index[i][j];
      for (int k = 0; k < 2; ++k) {
        const int bitmask = encode[k];
        const int direction_x = direction_collection[k].first;
        const int direction_y = direction_collection[k].second;
        const char direction = direction_char[k];
        if (const bool wall_on_direction = (castle_map[i][j] & bitmask) != 0) {
          const int neighbor_i = i + direction_x;
          const int neighbor_j = j + direction_y;
          if (const bool outbound = neighbor_i == -1 || neighbor_j == COL_CNT) {
            continue;
          }
          const int neighbor_component_id =
              component_id_by_index[neighbor_i][neighbor_j];
          if (neighbor_component_id != current_component_id) {
            const int combined_size = component_size[current_component_id] +
                                      component_size[neighbor_component_id];
            if (combined_size > largest_room_creatable) {
              largest_room_creatable = combined_size;
              optimal_wall_to_remove = {i + 1, j + 1, direction};
            }
          }
        }
      }
    }
  }

  fout << largest_room_creatable << endl;
  fout << get<0>(optimal_wall_to_remove) << ' '
       << get<1>(optimal_wall_to_remove) << ' '
       << get<2>(optimal_wall_to_remove) << endl;
}

int main() {
  solve_components();
  solve_wall_removal();
}
