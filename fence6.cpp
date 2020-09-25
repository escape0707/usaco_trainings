/*
ID: totheso1
LANG: C++14
TASK: fence6
*/

#include <algorithm>
#include <fstream>
#include <functional>
#include <iterator>
#include <limits>
#include <queue>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

static ifstream fin("fence6.in");
static ofstream fout("fence6.out");

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

static constexpr int MY_INT_MAX =
    numeric_limits<int>::max() / 3;  // Big enough.
static constexpr int MAX_EDGE_COUNT = 100;
static int vertex_count = 0;
static vector<vector<int>> direct_dist;
static vector<vector<pair<int, int>>> edge_by_vertex_collection;

static void initialize_adjacent_matrix() {
  direct_dist.assign(MAX_EDGE_COUNT * 2,
                     vector<int>(MAX_EDGE_COUNT * 2, MY_INT_MAX));

  const auto add_undirected_edge = [](const int f, const int t,
                                      const int length) {
    direct_dist[f][t] = direct_dist[t][f] = length;
  };

  const int segment_total = fin_get<int>();
  vector<unordered_map<int, int>> vertex_by_joint_collection(segment_total);
  for (int segment_count = 0; segment_count < segment_total; ++segment_count) {
    const int segment_id = fin_get<int>() - 1;
    const int length = fin_get<int>();
    const auto ending_degree_collection = fin_get_collection<vector<int>>(2);
    vector<int> endpoint_collection;
    for (const int ending_degree : ending_degree_collection) {
      auto connected_segment_collection =
          fin_get_collection<vector<int>>(ending_degree);
      int endpoint = -1;
      for (int &connected_segment_id : connected_segment_collection) {
        --connected_segment_id;
        const auto &joint_collection =
            vertex_by_joint_collection[connected_segment_id];
        const auto &lookup_result = joint_collection.find(segment_id);
        if (lookup_result != joint_collection.cend()) {
          endpoint = lookup_result->second;
          break;
        }
      }
      if (endpoint == -1) {
        endpoint = vertex_count++;
        auto &joint_collection = vertex_by_joint_collection[segment_id];
        for (const int connected_segment_id : connected_segment_collection) {
          joint_collection.emplace(connected_segment_id, endpoint);
        }
      }
      endpoint_collection.push_back(endpoint);
    }
    add_undirected_edge(endpoint_collection[0], endpoint_collection[1], length);
  }
}

static void solve_with_floyd_warshall() {
  auto dist = direct_dist;
  int ans = MY_INT_MAX;
  for (int k = 0; k < vertex_count; ++k) {
    for (int i = 0; i < k; ++i) {
      for (int j = 0; j < i; ++j) {
        ans = min(ans, dist[i][j] + direct_dist[i][k] + direct_dist[k][j]);
      }
    }
    for (int i = 0; i < vertex_count; ++i) {
      for (int j = 0; j < i; ++j) {
        dist[i][j] = dist[j][i] = min(dist[i][j], dist[i][k] + dist[k][j]);
      }
    }
  }
  fout << ans << endl;
}

static void initialize_adjacent_list() {
  const auto add_directed_edge = [](const int f, const int t,
                                    const int length) {
    edge_by_vertex_collection[f].emplace_back(length, t);
  };

  const int segment_total = fin_get<int>();
  vector<unordered_map<int, int>> vertex_by_joint_collection(segment_total);
  for (int segment_count = 0; segment_count < segment_total; ++segment_count) {
    const int segment_id = fin_get<int>() - 1;
    const int length = fin_get<int>();
    const auto ending_degree_collection = fin_get_collection<vector<int>>(2);
    vector<int> endpoint_collection;
    for (const int ending_degree : ending_degree_collection) {
      auto connected_segment_collection =
          fin_get_collection<vector<int>>(ending_degree);
      int endpoint = -1;
      for (int &connected_segment_id : connected_segment_collection) {
        --connected_segment_id;
        const auto &joint_collection =
            vertex_by_joint_collection[connected_segment_id];
        const auto &lookup_result = joint_collection.find(segment_id);
        if (lookup_result != joint_collection.cend()) {
          endpoint = lookup_result->second;
          break;
        }
      }
      if (endpoint == -1) {
        endpoint = vertex_count++;
        edge_by_vertex_collection.emplace_back();
        auto &joint_collection = vertex_by_joint_collection[segment_id];
        for (const int connected_segment_id : connected_segment_collection) {
          joint_collection.emplace(connected_segment_id, endpoint);
        }
      }
      endpoint_collection.push_back(endpoint);
    }
    add_directed_edge(endpoint_collection[0], endpoint_collection[1], length);
    add_directed_edge(endpoint_collection[1], endpoint_collection[0], length);
  }
}

static void solve_with_dijkstra() {
  vector<int> dist;

  const auto dijkstra = [&](const int start) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> heap(
        cbegin(edge_by_vertex_collection[start]),
        cend(edge_by_vertex_collection[start]));
    while (!heap.empty()) {
      bool expandable = false;
      int curr_dist, curr = -1;
      while (!heap.empty()) {
        curr_dist = heap.top().first;
        curr = heap.top().second;
        heap.pop();
        if (dist[curr] == MY_INT_MAX) {
          expandable = true;
          break;
        }
      }
      if (!expandable) {
        return;
      }
      dist[curr] = curr_dist;
      for (const auto &length_to : edge_by_vertex_collection[curr]) {
        heap.emplace(curr_dist + length_to.first, length_to.second);
      }
    }
  };

  int ans = MY_INT_MAX;
  int start = -1;
  for (auto &edge_collection : edge_by_vertex_collection) {
    ++start;
    for (auto b = rbegin(edge_collection), e = rend(edge_collection); b != e;
         ++b) {
      const auto length_to = *b;
      *b = edge_collection.back();
      edge_collection.pop_back();
      dist.assign(vertex_count, MY_INT_MAX);
      dijkstra(start);
      edge_collection.push_back(length_to);
      ans = min(ans, length_to.first + dist[length_to.second]);
    }
  }
  fout << ans << endl;
}

int main() {
  // initialize_adjacent_matrix();
  // solve_with_floyd_warshall();
  initialize_adjacent_list();
  solve_with_dijkstra();
}
