/*
ID: totheso1
LANG: C++14
TASK: lgame
NOTE:
    The interesting fact is this C++ implementation is only two times faster
    than my Python implementation.
*/

#include <algorithm>
#include <array>
#include <fstream>
#include <iterator>
#include <set>
#include <string>
#include <unordered_set>
#include <utility>

using namespace std;

static ifstream fin("lgame.in");
static ifstream fdict("lgame.dict");
static ofstream fout("lgame.out");

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

static constexpr array<int, 26> value_collection = {2, 5, 4, 4, 1, 6, 5, 5, 1,
                                                    7, 6, 3, 5, 2, 3, 5, 7, 2,
                                                    1, 2, 4, 6, 6, 7, 5, 7};

static string given_charactor_collection = []() {
  string res = fin_get<string>();
  sort(begin(res), end(res));
  return res;
}();

static const auto dictionary = []() {
  unordered_set<string> res((istream_iterator<string>(fdict)),
                            istream_iterator<string>());
  res.erase(".");
  return res;
}();

static void solve() {
  const auto compute_score = [&](const string &s) {
    int res = 0;
    for (const char c : s) {
      res += value_collection[c - 'a'];
    }
    return res;
  };

  int ans_score = 0;
  set<string> ans_str_collection;
  const int given_length = given_charactor_collection.size();
  do {
    for (int right = 3; right <= given_length; ++right) {
      for (int mid = 3; mid <= right; ++mid) {
        string total = given_charactor_collection.substr(0, mid);
        if (dictionary.find(total) == dictionary.cend()) {
          continue;
        }
        int score = compute_score(total);
        if (right - mid >= 3) {
          string second = given_charactor_collection.substr(mid, right - mid);
          if (dictionary.find(second) == dictionary.cend()) {
            continue;
          }
          score += compute_score(second);
          if (total > second) {
            swap(total, second);
          }
          total += ' ';
          total += second;
        }
        if (ans_str_collection.find(total) == cend(ans_str_collection)) {
          if (score > ans_score) {
            ans_score = score;
            ans_str_collection.clear();
          }
          if (score == ans_score) {
            ans_str_collection.insert(move(total));
          }
        }
      }
    }
  } while (next_permutation(begin(given_charactor_collection),
                            end(given_charactor_collection)));

  fout << ans_score << endl;
  for (const string &s : ans_str_collection) {
    fout << s << endl;
  }
}

int main() {
  solve();
}
