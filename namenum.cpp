/*
ID: totheso1
LANG: C++14
TASK: namenum
*/

#include <experimental/array>
#include <fstream>
#include <iterator>

using namespace std;

static ifstream fin("namenum.in");
static ifstream fdict("dict.txt");
static ofstream fout("namenum.out");

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

static int hash_char(const char c) {
  static const auto hashmap =
      experimental::make_array(2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7,
                               0, 7, 7, 8, 8, 8, 9, 9, 9, 0);
  return hashmap[static_cast<int>(c) - 65];
}

int main() {
  const auto brand_number = fin_get<long long>();
  bool found_match = false;
  for (auto b = istream_iterator<string>(fdict), e = istream_iterator<string>();
       b != e; ++b) {
    auto hashcode = 0LL;
    for (const char c : *b) {
      hashcode = hashcode * 10 + hash_char(c);
    }
    if (hashcode == brand_number) {
      found_match = true;
      fout << *b << endl;
    }
  }
  if (!found_match) {
    fout << "NONE" << endl;
  }
}
