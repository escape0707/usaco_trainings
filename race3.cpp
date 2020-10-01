/*
ID: totheso1
LANG: C++14
TASK: race3
*/

#include <algorithm>
#include <fstream>
#include <iterator>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

static ifstream fin("race3.in");
static ofstream fout("race3.out");

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

static vector<vector<int>> adjacency_list(1);

static void initialize() {
  for (int input; fin >> input, input != -1;) {
    if (input == -2) {
      adjacency_list.emplace_back();
    } else {
      adjacency_list.back().push_back(input);
    }
  }
  adjacency_list.pop_back();
}

static void solve() {
  const int vertex_count = adjacency_list.size();
  vector<bool> first_bfs_visited;
  const auto bfs_avoid = [&](const int avoid) -> bool {
    queue<int> que({0});
    first_bfs_visited[0] = true;
    while (!que.empty()) {
      const int curr_vertex = que.front();
      que.pop();
      for (const int to : adjacency_list[curr_vertex]) {
        if (first_bfs_visited[to] || to == avoid) {
          continue;
        }
        if (to == vertex_count - 1) {
          return true;
        }
        que.push(to);
        first_bfs_visited[to] = true;
      }
    }
    return false;
  };

  const auto bfs_can_go_back = [&](const int start) -> bool {
    vector<bool> visited(vertex_count, false);
    queue<int> que({start});
    visited[start] = true;
    while (!que.empty()) {
      const int curr_vertex = que.front();
      que.pop();
      for (const int to : adjacency_list[curr_vertex]) {
        if (visited[to]) {
          continue;
        }
        if (first_bfs_visited[to]) {
          return true;
        }
        que.push(to);
        visited[to] = true;
      }
    }
    return false;
  };

  vector<int> unavoidable_point_collection;
  vector<int> splitting_point_collection;
  for (int vertex = 0; vertex < vertex_count - 1; ++vertex) {
    first_bfs_visited.assign(vertex_count, false);
    if (!bfs_avoid(vertex)) {
      unavoidable_point_collection.push_back(vertex);
      if (!bfs_can_go_back(vertex)) {
        splitting_point_collection.push_back(vertex);
      }
    }
  }
  fout << unavoidable_point_collection.size();
  for (const int v : unavoidable_point_collection) {
    fout << ' ' << v;
  }
  fout << endl << splitting_point_collection.size();
  for (const int v : splitting_point_collection) {
    fout << ' ' << v;
  }
  fout << endl;
}

int main() {
  initialize();
  solve();
}
