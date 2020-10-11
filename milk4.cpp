/*
ID: totheso1
LANG: C++14
TASK: milk4
*/

#include <algorithm>
#include <fstream>
#include <functional>
#include <iterator>
#include <limits>
#include <memory>
#include <set>
#include <utility>
#include <vector>

using namespace std;

static ifstream fin("milk4.in");
static ofstream fout("milk4.out");

#define endl '\n'

template <typename T>
T fin_get() {
  T res;
  fin >> res;
  return res;
}

template <typename C>
C fin_get_collection(const int size) {
  C ret;
  copy_n(istream_iterator<typename C::value_type>(fin), size,
         back_inserter(ret));
  return ret;
}

struct TreeNode {
  const int value;
  const shared_ptr<TreeNode> prev;
};

bool operator<(const shared_ptr<TreeNode> &lhs,
               const shared_ptr<TreeNode> &rhs) {
  if (!rhs) {
    return false;
  }
  if (!lhs) {
    return true;
  }
  return lhs->value < rhs->value ? true : lhs->prev < rhs->prev;
}

static const int TARGET = fin_get<int>();
static const int PAIL_COUNT = fin_get<int>();
static auto dp = []() {
  vector<pair<int, shared_ptr<TreeNode>>> res(
      TARGET + 1, {numeric_limits<int>::max() - 1, {}});
  res[0].first = 0;
  return res;
}();
static const set<int, greater<>> pail_collection((istream_iterator<int>(fin)),
                                                 istream_iterator<int>());

static void solve() {
  vector<pair<int, shared_ptr<TreeNode>>> including;
  including.reserve(TARGET + 1);
  for (const int pail_value : pail_collection) {
    including.resize(pail_value);
    fill_n(begin(including), pail_value,
           pair<int, shared_ptr<TreeNode>>{numeric_limits<int>::max(), {}});
    for (int i = pail_value, prev = 0; i <= TARGET; ++i, ++prev) {
      auto new_pair = make_pair(
          dp[prev].first + 1,
          shared_ptr<TreeNode>(new TreeNode{pail_value, dp[prev].second}));
      including.push_back(min(including[prev], new_pair));
    }
    for (int i = pail_value; i <= TARGET; ++i) {
      dp[i] = min(dp[i], including[i]);
    }
  }

  fout << dp[TARGET].first;
  for (auto curr = dp[TARGET].second; curr; curr = curr->prev) {
    fout << ' ' << curr->value;
  }
  fout << endl;
}

int main() {
  solve();
}
