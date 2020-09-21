/*
ID: totheso1
LANG: C++14
TASK: heritage
*/

#include <algorithm>
#include <fstream>
#include <iterator>
#include <string>

using namespace std;

static ifstream fin("heritage.in");
static ofstream fout("heritage.out");

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

static const auto in_order = fin_get<string>();
static const auto pre_order = fin_get<string>();

template <typename InputIt>
static void print_post_order_recursive(const InputIt in_l, const InputIt in_r,
                                       const InputIt pre_l,
                                       const InputIt pre_r) {
  if (in_l == in_r && pre_l == pre_r) {
    return;
  }
  const auto root_in = find(in_l, in_r, *pre_l);
  const auto right_pre = next(pre_l, 1 + distance(in_l, root_in));
  print_post_order_recursive(in_l, root_in, next(pre_l), right_pre);
  print_post_order_recursive(next(root_in), in_r, right_pre, pre_r);
  fout << *pre_l;
}

int main() {
  print_post_order_recursive(cbegin(in_order), cend(in_order),
                             cbegin(pre_order), cend(pre_order));
  fout << endl;
}
