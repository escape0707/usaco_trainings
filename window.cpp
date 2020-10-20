/*
ID: totheso1
LANG: C++14
TASK: window
*/

#include <algorithm>
#include <fstream>
#include <iterator>
#include <list>
#include <unordered_map>

using namespace std;

static ifstream fin("window.in");
static ofstream fout("window.out");

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

struct Window {
  const int top;
  const int right;
  const int bottom;
  const int left;

  int area() const {
    return (bottom - top) * (right - left);
  }
};

template <typename Key, typename T>
class LinkedHashMap {
 public:
  
 private:
  list<T> value_list;
  unordered_map<Key, list<T>::iterator> list_iterator_by_key_collection;
};

static void solve() {}

int main() {
  solve();
}
