/*
ID: totheso1
LANG: C++14
TASK: spin
*/

#include <algorithm>
#include <fstream>
#include <functional>
#include <iterator>
#include <utility>
#include <vector>

using namespace std;

static ifstream fin("spin.in");
static ofstream fout("spin.out");

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

static vector<pair<int, vector<bool>>> wheel_collection;

static void initialize() {
  while (true) {
    const int speed = fin_get<int>();
    if (!fin) {
      break;
    }
    vector<bool> opaque_collection(360, true);
    for (int wedge_count = fin_get<int>(); wedge_count; --wedge_count) {
      for (int start = fin_get<int>(), e = start + fin_get<int>() + 1;
           start < e; ++start) {
        opaque_collection[start % 360] = false;
      }
    }
    wheel_collection.emplace_back(speed, move(opaque_collection));
  }
}

static void solve() {
  for (int time = 0; time < 360; ++time) {
    vector<bool> overall_opaque_collection(360, false);
    for (const auto &wheel : wheel_collection) {
      const int wheel_speed = wheel.first;
      const vector<bool> &wheel_opaque_collection = wheel.second;
      int degree = time * wheel_speed - 1;
      for (const bool opaque : wheel_opaque_collection) {
        ++degree;
        if (opaque) {
          overall_opaque_collection[degree % 360] = true;
        }
      }
    }
    if (!all_of(cbegin(overall_opaque_collection),
                cend(overall_opaque_collection),
                [](const bool b) { return b; })) {
      fout << time << endl;
      return;
    }
  }
  fout << "none" << endl;
}

int main() {
  initialize();
  solve();
}
