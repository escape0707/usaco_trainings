/*
ID: totheso1
LANG: C++14
TASK: fence
*/

#include <algorithm>
#include <forward_list>
#include <fstream>
#include <iterator>
#include <stack>
#include <stdexcept>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

static ifstream fin("fence.in");
static ofstream fout("fence.out");

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

static const int FENCE_COUNT = fin_get<int>();
static unordered_map<int, int> degree_by_point_collection;
static unordered_map<int, forward_list<pair<int, int>>>
    edge_collection_by_point_collection;

static void initialize() {
  const auto add_edge = [](const int f, const int t, const int idx) {
    edge_collection_by_point_collection[f].emplace_front(t, idx);
  };

  for (int edge_id = 0; edge_id < FENCE_COUNT; ++edge_id) {
    const int point_a = fin_get<int>();
    const int point_b = fin_get<int>();
    ++degree_by_point_collection[point_a];
    ++degree_by_point_collection[point_b];
    add_edge(point_a, point_b, edge_id);
    add_edge(point_b, point_a, edge_id);
  }
}

static void solve() {
  vector<bool> traveled(FENCE_COUNT, false);
  vector<int> sequence_reversed;

  const auto recursive_find_path = [&](const int curr_point) {
    const auto impl = [&](const auto &self, const int curr_point) -> void {
      for (const auto &p : edge_collection_by_point_collection[curr_point]) {
        const int to = p.first;
        const int edge_id = p.second;
        if (!traveled[edge_id]) {
          traveled[edge_id] = true;
          self(self, to);
        }
      }
      sequence_reversed.push_back(curr_point);
    };
    return impl(impl, curr_point);
  };

  const auto non_recursive_find_path = [&](const int start_point) {
    auto b = cbegin(edge_collection_by_point_collection[start_point]);
    const auto e = cend(edge_collection_by_point_collection[start_point]);
    using iter_type = decltype(b);
    stack<pair<int, pair<iter_type, const iter_type>>> stk;

    const auto in_the_loop = [&](const int curr_point, auto &b, const auto &e) {
      for (; b != e; ++b) {
        const int to = b->first;
        const int edge_id = b->second;
        if (!traveled[edge_id]) {
          traveled[edge_id] = true;
          stk.emplace(to,
                      make_pair(cbegin(edge_collection_by_point_collection[to]),
                                cend(edge_collection_by_point_collection[to])));
          return;
        }
      }
      sequence_reversed.push_back(curr_point);
      stk.pop();
    };

    stk.emplace(start_point, make_pair(b, e));
    while (!stk.empty()) {
      in_the_loop(stk.top().first, stk.top().second.first,
                  stk.top().second.second);
    }
  };

  vector<int> ending_point_collection;
  for (const auto &p : degree_by_point_collection) {
    const int point = p.first;
    const int degree = p.second;
    if (degree & 1) {
      ending_point_collection.push_back(point);
    }
  }
  int start;
  if (!ending_point_collection.empty()) {
    if (ending_point_collection.size() != 2) {
      throw invalid_argument("No possible Eulerian circuit.");
    }
    start =
        min(ending_point_collection.front(), ending_point_collection.back());
  } else {
    start = min_element(cbegin(degree_by_point_collection),
                        cend(degree_by_point_collection))
                ->first;
  }

  for (auto &p : edge_collection_by_point_collection) {
    p.second.sort();
  }
  non_recursive_find_path(start);
  copy(crbegin(sequence_reversed), crend(sequence_reversed),
       ostream_iterator<int>(fout, "\n"));
}

int main() {
  initialize();
  solve();
}
