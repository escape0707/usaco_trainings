/*
ID: totheso1
LANG: C++14
TASK: prefix
*/

#include <algorithm>
#include <fstream>
#include <iterator>
#include <memory>
#include <queue>
#include <string>
#include <vector>

using namespace std;

static ifstream fin("prefix.in");
static ofstream fout("prefix.out");

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

static vector<string> primitive_collection;
static string target;

static void initialize() {
  for (string s; fin >> s && s != ".";) {
    primitive_collection.push_back(move(s));
  }
  for (string s; fin >> s;) {
    target += s;
  }
}

static int solve_with_basic_dynamic_programming() {  // Accepted
  const int target_length = target.length();
  vector<bool> matchable_by_length_collection(target_length + 1, false);
  matchable_by_length_collection[0] = true;
  int ans = 0;
  for (int i = 0; i < target_length; ++i) {
    for (const string &primitive : primitive_collection) {
      const int primitive_length = primitive.length();
      if (equal(cbegin(primitive), cend(primitive),
                cbegin(target) + max(0, i + 1 - primitive_length),
                cbegin(target) + i + 1) &&
          matchable_by_length_collection[i - primitive_length + 1]) {
        matchable_by_length_collection[i + 1] = true;
        ans = i + 1;
        break;
      }
    }
  }
  return ans;
}

static int solve_with_dynamic_programming_and_trie() {  // Accepted
  struct TrieNode {
    bool is_ending = false;
    vector<shared_ptr<TrieNode>> next_collection =
        vector<shared_ptr<TrieNode>>(26);
  };
  auto trie_root = make_shared<TrieNode>();
  int trie_height = 1;
  constexpr int ord_A = static_cast<int>('A');  // 65
  for (const string &primitive : primitive_collection) {
    trie_height = max<int>(trie_height, primitive.length() + 1);
    auto curr_node = trie_root;
    for (auto b = crbegin(primitive), e = crend(primitive); b < e; ++b) {
      const int index_c = static_cast<int>(*b) - ord_A;
      auto &next_node = curr_node->next_collection[index_c];
      if (next_node == nullptr) {
        next_node = make_shared<TrieNode>();
      }
      curr_node = next_node;
    }
    curr_node->is_ending = true;
  }

  const int target_length = target.length();
  vector<bool> matchable_by_length_collection(target_length + 1, false);
  matchable_by_length_collection[0] = true;
  int ans = 0;
  for (int i = 0; i < target_length; ++i) {
    auto curr_node = trie_root;
    for (int j = 0, e = min(i + 1, trie_height - 1); j < e; ++j) {
      const int index_c = static_cast<int>(target[i - j]) - ord_A;
      auto &next_node = curr_node->next_collection[index_c];
      if (next_node == nullptr) {
        break;
      }
      curr_node = next_node;
      if (curr_node->is_ending &&
          matchable_by_length_collection[i - j - 1 + 1]) {
        matchable_by_length_collection[i + 1] = true;
        ans = i + 1;
        break;
      }
    }
  }
  return ans;
}

static int solve_with_dynamic_programming_and_AC_automaton() {  // Accepted
  struct ACNode {
    vector<int> end_with_length;
    vector<shared_ptr<ACNode>> next_collection = vector<shared_ptr<ACNode>>(26);
    shared_ptr<ACNode> fail_to;
  };
  auto AC_root = make_shared<ACNode>();
  AC_root->fail_to = AC_root;
  constexpr int ord_A = static_cast<int>('A');  // 65
  for (const string &primitive : primitive_collection) {
    auto curr_node = AC_root;
    for (const char c : primitive) {
      const int index_c = static_cast<int>(c) - ord_A;
      auto &next_node = curr_node->next_collection[index_c];
      if (next_node == nullptr) {
        next_node = make_shared<ACNode>();
      }
      curr_node = next_node;
    }
    curr_node->end_with_length.push_back(primitive.length());
  }

  queue<shared_ptr<ACNode>> que;
  for (const auto &node : AC_root->next_collection) {
    if (node != nullptr) {
      node->fail_to = AC_root;
      que.push(node);
    }
  }
  while (!que.empty()) {
    const auto &parent_node = que.front();
    que.pop();
    int index_c = -1;
    for (const auto &child_node : parent_node->next_collection) {
      ++index_c;
      if (child_node == nullptr) {
        continue;
      }
      que.push(child_node);
      auto fail_to = parent_node->fail_to;
      while (fail_to != AC_root &&
             fail_to->next_collection[index_c] == nullptr) {
        fail_to = fail_to->fail_to;
      }
      const auto &next_node = fail_to->next_collection[index_c];
      child_node->fail_to = next_node != nullptr ? next_node : AC_root;
      {
        auto &a = child_node->end_with_length;
        auto &b = child_node->fail_to->end_with_length;
        a.insert(cend(a), cbegin(b), cend(b));
      }
    }
  }

  const int target_length = target.length();
  vector<bool> matchable_by_length_collection(target_length + 1, false);
  matchable_by_length_collection[0] = true;
  int ans = 0;
  auto curr_node = AC_root;
  int i = -1;
  for (const char c : target) {
    ++i;
    const int index_c = static_cast<int>(c) - ord_A;
    auto next_node = curr_node->next_collection[index_c];
    while (curr_node != AC_root && next_node == nullptr) {
      curr_node = curr_node->fail_to;
      next_node = curr_node->next_collection[index_c];
    }
    curr_node = next_node != nullptr ? next_node : AC_root;
    for (const int length : curr_node->end_with_length) {
      if (matchable_by_length_collection[i - length + 1]) {
        matchable_by_length_collection[i + 1] = true;
        ans = i + 1;
        break;
      }
    }
  }
  return ans;
}

int main() {
  initialize();
  fout << solve_with_dynamic_programming_and_AC_automaton() << endl;
}
