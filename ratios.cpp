/*
ID: totheso1
LANG: C++14
TASK: ratios
*/

#include <algorithm>
#include <fstream>
#include <iterator>
#include <vector>

using namespace std;

static ifstream fin("ratios.in");
static ofstream fout("ratios.out");

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

static const auto goal = fin_get_collection<vector<int>>(3);
static vector<vector<int>> mixture_collection;

static void initialize() {
  for (int i = 0; i < 3; ++i) {
    mixture_collection.push_back(fin_get_collection<vector<int>>(3));
  }
}

static int validate(const vector<int> vector_x) {
  int prev_k = -1;
  for (int component_id = 0; component_id < 3; ++component_id) {
    int my_inner_product = 0;
    for (int mixture_id = 0; mixture_id < 3; ++mixture_id) {
      my_inner_product +=
          mixture_collection[mixture_id][component_id] * vector_x[mixture_id];
    }
    if (goal[component_id] == 0) {
      if (my_inner_product != 0) {
        return 0;
      }
    } else {
      const int remainder = my_inner_product % goal[component_id];
      const int k = my_inner_product / goal[component_id];
      if (remainder != 0 || k != prev_k && prev_k != -1) {
        return 0;
      }
      prev_k = k;
    }
  }
  return prev_k;
}

static void solve() {
  for (int x1 = 0; x1 < 100; ++x1) {
    for (int x2 = 0; x2 < 100; ++x2) {
      for (int x3 = 0; x3 < 100; ++x3) {
        const int k = validate({x1, x2, x3});
        if (k != 0) {
          fout << x1 << ' ' << x2 << ' ' << x3 << ' ' << k << endl;
          return;
        }
      }
    }
  }
  fout << "NONE" << endl;
}

int main() {
  initialize();
  solve();
}
