/*
ID: totheso1
LANG: C++14
TASK: butter
NOTE:
    SPFA is almost 4 times faster than Dijkstra for this problem.
*/

#include <algorithm>
#include <forward_list>
#include <fstream>
#include <iterator>
#include <limits>
#include <queue>
#include <stdexcept>
#include <vector>

using namespace std;

static ifstream fin("butter.in");
static ofstream fout("butter.out");

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
static const int PASTURE_COUNT = fin_get<int>();
static const int PATH_COUNT = fin_get<int>();
static vector<int> pasture_by_cow_collection;
static vector<forward_list<pair<int, int>>>
    path_collection_by_pasture_collection(PASTURE_COUNT);

static void add_edge(const int f, const int t, const int length) {
  path_collection_by_pasture_collection[f].emplace_front(t, length);
}

static void initialize() {
  for (int i = 0; i < COW_COUNT; ++i) {
    pasture_by_cow_collection.push_back(fin_get<int>() - 1);
  }
  for (int i = 0; i < PATH_COUNT; ++i) {
    const int pasture_a = fin_get<int>() - 1;
    const int pasture_b = fin_get<int>() - 1;
    const int length = fin_get<int>();
    add_edge(pasture_a, pasture_b, length);
    add_edge(pasture_b, pasture_a, length);
  }
}

static void dijkstra(const int source, vector<int> &dist) {
  vector<bool> solved(PASTURE_COUNT, false);
  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> heap;
  heap.emplace(0, source);
  for (int solve_count = 0; solve_count < PASTURE_COUNT; ++solve_count) {
    int curr_dist, curr_pasture;
    while (true) {
      curr_dist = heap.top().first;
      curr_pasture = heap.top().second;
      heap.pop();
      if (!solved[curr_pasture]) {
        break;
      }
    }
    dist[curr_pasture] = curr_dist;
    solved[curr_pasture] = true;
    for (const auto &p : path_collection_by_pasture_collection[curr_pasture]) {
      const int to = p.first;
      const int length = p.second;
      if (!solved[to]) {
        heap.emplace(curr_dist + length, to);
      }
    }
  }
}

static void spfa(const int source, vector<int> &dist) {
  dist[source] = 0;
  vector<bool> in_queue(PASTURE_COUNT, false);
  queue<int> que({source});
  in_queue[source] = true;
  for (int relax_count = 0, e = PASTURE_COUNT * (PATH_COUNT - 1) + 1;
       relax_count < e; ++relax_count) {
    if (que.empty()) {
      return;
    }
    const int curr_pasture = que.front();
    que.pop();
    in_queue[curr_pasture] = false;
    const int curr_dist = dist[curr_pasture];
    for (const auto &p : path_collection_by_pasture_collection[curr_pasture]) {
      const int to = p.first;
      const int length = p.second;
      const int new_dist = curr_dist + length;
      if (new_dist < dist[to]) {
        dist[to] = new_dist;
        if (!in_queue[to]) {
          que.push(to);
          in_queue[to] = true;
        }
      }
    }
  }
  throw invalid_argument("Graph contains negative circuit.");
}

static void solve() {
  int ans = numeric_limits<int>::max();
  for (int sugar_pasture = 0; sugar_pasture < PASTURE_COUNT; ++sugar_pasture) {
    vector<int> dist(PASTURE_COUNT, numeric_limits<int>::max());
    spfa(sugar_pasture, dist);
    int sum = 0;
    for (const int pasture : pasture_by_cow_collection) {
      sum += dist[pasture];
    }
    ans = min(ans, sum);
  }
  fout << ans << endl;
}

int main() {
  initialize();
  solve();
}
