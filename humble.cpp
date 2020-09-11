/*
ID: totheso1
LANG: C++14
TASK: humble
NOTE:
    As I didn't come up with an optimal solution,
    I used Red-Black-Tree in STL (std::map) to solve the problem first.
    It's also understandale.
    And I'm amazed by its speed and power
    to get Accepted even used in a sub-optimal solution.
*/

#include <algorithm>
#include <fstream>
#include <functional>
#include <iterator>
#include <limits>
#include <map>
#include <vector>

using namespace std;

static ifstream fin("humble.in");
static ofstream fout("humble.out");

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

static const int PRIME_COUNT = fin_get<int>();
static const int ANSWER_ORDER = fin_get<int>();
static vector<long> prime_collection =
    fin_get_collection<vector<long>>(PRIME_COUNT);

static void solve_with_RBT() {
  sort(begin(prime_collection), end(prime_collection));

  map<long, int> rbt;
  rbt.emplace(1, 0);
  for (int count = 0; count < ANSWER_ORDER; ++count) {
    const auto front_iter = cbegin(rbt);
    const auto curr = front_iter->first;
    auto i = front_iter->second;
    rbt.erase(front_iter);
    const auto quotient = numeric_limits<long>::max() / curr;
    for (; i < PRIME_COUNT; ++i) {
      if (prime_collection[i] > quotient) {
        break;
      }
      const auto product = curr * prime_collection[i];
      const auto hint = rbt.lower_bound(product);
      if (rbt.size() != ANSWER_ORDER) {
        rbt.emplace_hint(hint, product, i);
      } else {
        if (hint == cend(rbt)) {
          break;
        }
        rbt.emplace_hint(hint, product, i);
        rbt.erase(prev(cend(rbt)));
      }
    }
  }
  fout << cbegin(rbt)->first << endl;
}

static void solve_with_greedy() {
  vector<long> humble_collection = {1};
  vector<int> try_index_collection(PRIME_COUNT, 0);
  for (int humble_count = 0; humble_count < ANSWER_ORDER; ++humble_count) {
    auto min_product = numeric_limits<long>::max();
    const auto last_humble_number = humble_collection.back();
    int i = -1;
    for (const auto prime : prime_collection) {
      ++i;
      for (int j = try_index_collection[i]; true; ++j) {
        const auto product = prime * humble_collection[j];
        if (product > last_humble_number) {
          try_index_collection[i] = j;
          min_product = min(min_product, product);
          break;
        }
      }
    }
    humble_collection.push_back(min_product);
  }
  fout << humble_collection.back() << endl;
}

int main() {
  solve_with_greedy();
}
