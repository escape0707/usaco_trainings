/*
ID: totheso1
LANG: C++14
TASK: stall4
*/

#include <algorithm>
#include <forward_list>
#include <fstream>
#include <iterator>
#include <queue>
#include <vector>

using namespace std;

static ifstream fin("stall4.in");
static ofstream fout("stall4.out");

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

static const int COW_COUNT = fin_get<int>();
static const int STALL_COUNT = fin_get<int>();
static vector<int> to;
static vector<forward_list<int>> adjacency_list(COW_COUNT + STALL_COUNT);

static void initialize() {
  const auto add_edge = [&](const int f, const int t) -> void {
    adjacency_list[f].push_front(to.size());
    to.push_back(t);
    adjacency_list[t].push_front(to.size());
    to.push_back(f);
  };

  for (int cow = 0; cow < COW_COUNT; ++cow) {
    for (int stall_for_cow_count = fin_get<int>(); stall_for_cow_count--;) {
      const int stall = fin_get<int>();
      add_edge(cow, stall - 1 + COW_COUNT);
    }
  }
}

static void solve() {
  vector<bool> edge_in_match(to.size());
  vector<bool> vertex_in_match(COW_COUNT + STALL_COUNT);
  vector<int> edge_to(COW_COUNT + STALL_COUNT);

  const auto find_augmenting_path = [&](const int start) {
    vector<bool> visited(COW_COUNT + STALL_COUNT, false);
    queue<int> que({start});
    visited[start] = true;
    while (!que.empty()) {
      const int curr_vertex = que.front();
      que.pop();
      for (const int edge : adjacency_list[curr_vertex]) {
        if ((curr_vertex >= COW_COUNT) == edge_in_match[edge >> 1]) {
          const int other = to[edge];
          if (visited[other]) {
            continue;
          }
          edge_to[other] = edge;
          if (!vertex_in_match[other]) {
            return other;
          }
          que.push(other);
          visited[other] = true;
        }
      }
    }
    return -1;
  };

  int ans = 0;
  for (int start = 0; start < COW_COUNT; ++start) {
    int curr_vertex = find_augmenting_path(start);
    if (curr_vertex == -1) {
      continue;
    }
    vertex_in_match[start] = vertex_in_match[curr_vertex] = true;
    ++ans;
    while (curr_vertex != start) {
      const int edge = edge_to[curr_vertex];
      edge_in_match[edge >> 1].flip();
      curr_vertex = to[edge ^ 1];
    }
  }
  fout << ans << endl;
}

int main() {
  initialize();
  solve();
}
