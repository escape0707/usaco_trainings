/*
ID: totheso1
LANG: C++14
TASK: ditch
*/

#include <algorithm>
#include <forward_list>
#include <fstream>
#include <iterator>
#include <limits>
#include <queue>
#include <vector>

using namespace std;

static ifstream fin("ditch.in");
static ofstream fout("ditch.out");

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

static const int EDGE_COUNT = fin_get<int>();
static const int VERTEX_COUNT = fin_get<int>();
static vector<forward_list<int>> adjacency_list(VERTEX_COUNT);
static vector<int> capacity;
static vector<int> flow;
static vector<int> to;

static void initialize() {
  for (int i = 0; i < EDGE_COUNT; ++i) {
    const int f = fin_get<int>() - 1;
    const int t = fin_get<int>() - 1;
    const int c = fin_get<int>();
    adjacency_list[f].push_front(i << 1);
    adjacency_list[t].push_front(i << 1 | 1);
    capacity.push_back(c);
    flow.push_back(0);
    flow.push_back(c);
    to.push_back(t);
    to.push_back(f);
  }
}

static void solve() {
  vector<int> edge_to(VERTEX_COUNT);

  const auto residual_capacity = [&](const int edge) -> int {
    return capacity[edge >> 1] - flow[edge];
  };

  const auto find_augmenting_path = [&]() -> bool {
    vector<bool> visited(VERTEX_COUNT, false);
    queue<int> que({0});
    visited[0] = true;
    while (!que.empty()) {
      const int curr_vertex = que.front();
      que.pop();
      for (const int edge : adjacency_list[curr_vertex]) {
        const int next_vertex = to[edge];
        if (residual_capacity(edge) != 0 && !visited[next_vertex]) {
          visited[next_vertex] = true;
          edge_to[next_vertex] = edge;
          if (next_vertex == (VERTEX_COUNT - 1)) {
            return true;
          }
          que.push(next_vertex);
        }
      }
    }
    return false;
  };

  int maxflow = 0;
  while (find_augmenting_path()) {
    int bottleneck = numeric_limits<int>::max();
    int curr_vertex = VERTEX_COUNT - 1;
    while (curr_vertex != 0) {
      const int edge = edge_to[curr_vertex];
      bottleneck = min(bottleneck, residual_capacity(edge));
      curr_vertex = to[edge ^ 1];
    }
    curr_vertex = VERTEX_COUNT - 1;
    maxflow += bottleneck;
    while (curr_vertex != 0) {
      const int edge = edge_to[curr_vertex];
      flow[edge] += bottleneck;
      flow[edge ^ 1] -= bottleneck;
      curr_vertex = to[edge ^ 1];
    }
  }
  fout << maxflow << endl;
}

int main() {
  initialize();
  solve();
}
