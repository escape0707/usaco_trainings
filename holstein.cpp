/*
ID: totheso1
LANG: C++14
TASK: holstein
*/

#include <algorithm>
#include <deque>
#include <fstream>
#include <functional>
#include <iterator>
#include <queue>
#include <tuple>
#include <vector>

using namespace std;

static ifstream fin("holstein.in");
static ofstream fout("holstein.out");

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

using bfs_status = tuple<int, int, vector<int>>;

static const int VITAMIN_COUNT = fin_get<int>();
static const auto requirement_collection =
    fin_get_collection<vector<int>>(VITAMIN_COUNT);
static const int FEED_COUNT = fin_get<int>();
static vector<vector<int>> ingredient_table_collection;

static void initialize() {
  for (int i = 0; i < FEED_COUNT; ++i) {
    ingredient_table_collection.push_back(
        fin_get_collection<vector<int>>(VITAMIN_COUNT));
  }
}

template <typename C>
static bool all_greater_equal(const C &a, const C &b) {
  return mismatch(cbegin(a), cend(a), cbegin(b), greater_equal<>()).first == cend(a);
}

static void print_feed_bitset(int feed_bitset) {
  int count = 0;
  vector<int> feed_type_collection;
  for (int current_feed_type = 1; feed_bitset != 0;
       ++current_feed_type, feed_bitset >>= 1) {
    if ((feed_bitset & 1) == 1) {
      ++count;
      feed_type_collection.push_back(current_feed_type);
    }
  }
  fout << count;
  for (const int feed_type : feed_type_collection) {
    fout << ' ' << feed_type;
  }
  fout << endl;
}

static void solve_feed() {
  queue<bfs_status> que(
      deque<bfs_status>{{0, 0, vector<int>(VITAMIN_COUNT, 0)}});
  while (!que.empty()) {
    const bfs_status &head = que.front();
    const int next_feed_id = get<0>(head);
    const int feed_bitset = get<1>(head);
    const vector<int> vitamin_collection = move(get<2>(head));
    que.pop();
    for (int feed_id = next_feed_id; feed_id < FEED_COUNT; ++feed_id) {
      const int new_feed_bitset = feed_bitset | (1 << feed_id);
      vector<int> new_vitamin_collection;
      transform(cbegin(vitamin_collection), cend(vitamin_collection),
                cbegin(ingredient_table_collection[feed_id]),
                back_inserter(new_vitamin_collection), plus<>());
      if (all_greater_equal(new_vitamin_collection, requirement_collection)) {
        print_feed_bitset(new_feed_bitset);
        return;
      }
      que.emplace(feed_id + 1, new_feed_bitset, move(new_vitamin_collection));
    }
  }
}

int main() {
  initialize();
  solve_feed();
}
