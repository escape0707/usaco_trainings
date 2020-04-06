/*
ID: totheso1
LANG: C++14
TASK: transform
*/

#include <algorithm>
#include <array>
#include <fstream>
#include <iterator>
#include <string>
#include <utility>
#include <vector>

using namespace std;

static ifstream fin("transform.in");
static ofstream fout("transform.out");

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

using trans_info = array<array<int, 2>, 3>;

const int side = fin_get<int>();
const auto origin = fin_get_collection<vector<string>>(side);
const auto target = fin_get_collection<vector<string>>(side);

static trans_info rotate_90(const trans_info &trans) {
  const array<int, 2> &start = get<0>(trans), &step_outer = get<1>(trans),
                      &step_inner = get<2>(trans);
  return {{{get<1>(start), side - 1 - get<0>(start)},
           {get<1>(step_outer), -get<0>(step_outer)},
           {get<1>(step_inner), -get<0>(step_inner)}}};
}

static trans_info reflect(const trans_info &trans) {
  const array<int, 2> &start = get<0>(trans), &step_outer = get<1>(trans),
                      &step_inner = get<2>(trans);
  return {{{get<0>(start), side - 1 - get<1>(start)},
           {get<0>(step_outer), -get<1>(step_outer)},
           {get<0>(step_inner), -get<1>(step_inner)}}};
}

static bool equal(const trans_info &trans) {
  array<int, 2> start = get<0>(trans);
  const array<int, 2> &step_outer = get<1>(trans);
  const array<int, 2> &step_inner = get<2>(trans);
  for (const string &origin_row : origin) {
    int x = get<0>(start), y = get<1>(start);
    for (const char tile : origin_row) {
      if (tile != target[x][y]) {
        return false;
      }
      x += get<0>(step_inner);
      y += get<1>(step_inner);
    }
    get<0>(start) += get<0>(step_outer);
    get<1>(start) += get<1>(step_outer);
  }
  return true;
}

static vector<trans_info> map(trans_info (*f)(const trans_info &),
                              const vector<trans_info> &range) {
  vector<trans_info> ret;
  transform(cbegin(range), cend(range), back_inserter(ret), f);
  return ret;
}

static int find_transformation() {
  const trans_info identity_trans = {{{0, 0}, {1, 0}, {0, 1}}};
  vector<vector<trans_info>> transformations = {{rotate_90(identity_trans)}};

  for (int i = 0; i < 2; ++i) {
    transformations.push_back(map(rotate_90, transformations.back()));
  }
  transformations.push_back({reflect(identity_trans)});
  {
    vector<trans_info> tmp;
    for (const vector<trans_info> &vec : transformations) {
      for (const trans_info &trans : vec) {
        tmp.push_back(reflect(trans));
      }
    }
    transformations.push_back(move(tmp));
  }
  transformations.push_back({identity_trans});
  int ret = 1;
  for (const vector<trans_info> &transCollection : transformations) {
    for (const trans_info &view : transCollection) {
      if (equal(view)) {
        return ret;
      }
    }
    ++ret;
  }
  return ret;
}

int main() {
  fout << find_transformation() << endl;
}
