/*
ID: totheso1
LANG: C++14
TASK: wormhole
*/

#include <algorithm>
#include <fstream>
#include <iterator>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

static ifstream fin("wormhole.in");
static ofstream fout("wormhole.out");

#define endl '\n'

template <typename T>
T fin_get() {
  return *istream_iterator<T>(fin);
}

template <typename C>
C fin_get_collection(int size) {
  C ret;
  copy_n(istream_iterator<typename C::value_type>(fin), size,
         back_inserter(ret));
  return ret;
}

static int hole_count;
static vector<int> right_side;

static bool could_get_stuck(const vector<pair<int, int>> &pairing) {
  vector<int> entered_from_collection(hole_count, -1);
  vector<int> exit_collection(hole_count, -1);
  for (const auto &pair : pairing) {
    int hole_a = pair.first, hole_b = pair.second;
    exit_collection[hole_a] = hole_b;
    exit_collection[hole_b] = hole_a;
  }
  int entrance = -1;
  for (const int entered_from : entered_from_collection) {
    ++entrance;
    if (entered_from == -1) {
      for (int towards = entrance; towards != -1;) {
        if (entered_from_collection[towards] == entrance) {
          return true;
        }
        entered_from_collection[towards] = entrance;
        towards = right_side[exit_collection[towards]];
      }
    }
  }
  return false;
}

static int dfs() {
  static vector<bool> in_pairing_collection(hole_count, false);
  static vector<pair<int, int>> pairing;

  int current_hole = -1, hole = -1;
  for (const bool is_in_pairing : in_pairing_collection) {
    ++hole;
    if (!is_in_pairing) {
      current_hole = hole;
      break;
    }
  }
  if (current_hole == -1) {
    return could_get_stuck(pairing);
  }
  in_pairing_collection[current_hole] = true;
  int result = 0;
  hole = -1;
  for (const bool is_in_pairing : in_pairing_collection) {
    ++hole;
    if (!is_in_pairing) {
      in_pairing_collection[hole] = true;
      pairing.emplace_back(current_hole, hole);
      result += dfs();
      pairing.pop_back();
      in_pairing_collection[hole] = false;
    }
  }
  in_pairing_collection[current_hole] = false;
  return result;
}

int main() {
  hole_count = fin_get<int>();
  vector<tuple<int, int, int>> hole_location_collection;
  for (int i = 0; i < hole_count; ++i) {
    const int x = fin_get<int>(), y = fin_get<int>();
    hole_location_collection.emplace_back(y, x, i);
  }
  sort(begin(hole_location_collection), end(hole_location_collection));

  right_side.assign(hole_count, -1);
  for (auto ptr_hole_a = begin(hole_location_collection),
            ptr_hole_b = ptr_hole_a + 1, e = end(hole_location_collection);
       ptr_hole_b != e; ++ptr_hole_a, ++ptr_hole_b) {
    if (get<0>(*ptr_hole_a) == get<0>(*ptr_hole_b)) {
      right_side[get<2>(*ptr_hole_a)] = get<2>(*ptr_hole_b);
    }
  }

  fout << dfs() << endl;
}
