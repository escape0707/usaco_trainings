/*
ID: totheso1
LANG: C++14
TASK: nuggets
*/

#include <algorithm>
#include <fstream>
#include <functional>
#include <iterator>
#include <numeric>
#include <queue>
#include <vector>

using namespace std;

static ifstream fin("nuggets.in");
static ofstream fout("nuggets.out");

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

static const int OPTION_COUNT = fin_get<int>();
static const auto option_collection =
    fin_get_collection<vector<int>>(OPTION_COUNT);

static int gcd(int a, int b) {
  return a == 0 ? abs(b) : b == 0 ? abs(a) : gcd(b, a % b);
}

static int find_max_int_cant_make() {
  if (accumulate(cbegin(option_collection), cend(option_collection), 0, gcd) !=
      1) {
    return 0;
  }
  vector<int> purchase_collection = {0};
  priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>>
      heap;
  for (const int option : option_collection) {
    heap.emplace(option, option, -1);
  }
  // Since there will at most be 10 option,
  // std::make_heap don't make a big difference here.
  const int min_option = get<0>(heap.top());
  int max_consecutive_purchase = 0;
  while (true) {
    while (get<0>(heap.top()) == purchase_collection.back()) {
      const int total = get<0>(heap.top());
      const int option = get<1>(heap.top());
      const int index = get<2>(heap.top());
      heap.pop();
      if (index == -1) {
        continue;
      }
      heap.emplace(option + purchase_collection[index], option, index + 1);
    }
    const int total = get<0>(heap.top());
    const int option = get<1>(heap.top());
    const int index = get<2>(heap.top());
    heap.pop();
    purchase_collection.push_back(total);
    if (total - purchase_collection[purchase_collection.size() - 2] == 1) {
      ++max_consecutive_purchase;
      if (max_consecutive_purchase == min_option) {
        return purchase_collection[purchase_collection.size() -
                                   max_consecutive_purchase] -
               1;
      }
    } else {
      max_consecutive_purchase = 1;
    }
    if (index == -1) {
      heap.emplace(2 * option, option, purchase_collection.size());
    } else {
      heap.emplace(option + purchase_collection[index], option, index + 1);
    }
  }
}

int main() {
  fout << find_max_int_cant_make() << endl;
}
