/*
ID: totheso1
LANG: C++14
TASK: msquare
*/

#include <algorithm>
#include <array>
#include <fstream>
#include <iterator>
#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

static ifstream fin("msquare.in");
static ofstream fout("msquare.out");

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

static const string INITIAL = "12345678";
static string GOAL;

static void initialize() {
  getline(fin, GOAL);
  GOAL.erase(remove(begin(GOAL), end(GOAL), ' '), end(GOAL));
}

struct TreeNode {
  const int operation;
  const shared_ptr<const TreeNode> prev;
};

static void print_node(const shared_ptr<const TreeNode> &node) {
  auto head = &node;
  string operator_collection_reversed;
  for (int operation; (operation = (*head)->operation) != -1;
       head = &((*head)->prev)) {
    operator_collection_reversed.push_back(operation + 'A');
  }
  copy(crbegin(operator_collection_reversed),
       crend(operator_collection_reversed), ostream_iterator<char>(fout));
  fout << endl;
}

static string apply_transform(const string &state, const array<int, 8> &trans) {
  string res;
  // res.reserve(state.length());
  res.reserve(8);
  for (const int i : trans) {
    res.push_back(state[i]);
  }
  return res;
}

static void solve() {
  constexpr array<array<int, 8>, 3> trans_collection = {{
      {7, 6, 5, 4, 3, 2, 1, 0},
      {3, 0, 1, 2, 5, 6, 7, 4},
      {0, 6, 1, 3, 4, 2, 5, 7},
  }};
  vector<pair<string, shared_ptr<const TreeNode>>> queue = {
      {INITIAL, shared_ptr<const TreeNode>(new const TreeNode{-1, nullptr})}};
  unordered_set<string> visited_state_collection = {INITIAL};
  for (int length = 0; !queue.empty(); ++length) {
    decltype(queue) next_queue;
    for (const auto &p : queue) {
      const string &state = p.first;
      const shared_ptr<const TreeNode> &node = p.second;
      if (state == GOAL) {
        fout << length << endl;
        print_node(node);
        return;
      }
      int i = -1;
      for (const auto &trans : trans_collection) {
        ++i;
        const string next_state = apply_transform(state, trans);
        if (visited_state_collection.find(next_state) ==
            cend(visited_state_collection)) {
          next_queue.emplace_back(next_state, shared_ptr<const TreeNode>(
                                                  new const TreeNode{i, node}));
          visited_state_collection.insert(next_state);
        }
      }
    }
    queue = move(next_queue);
  }
}

int main() {
  initialize();
  solve();
}
