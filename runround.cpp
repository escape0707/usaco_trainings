/*
ID: totheso1
LANG: C++14
TASK: runround
NOTE:
    No input validation included,
    beware of infinite-loop when input is invalid.
*/

#include <algorithm>
#include <fstream>
#include <iterator>
#include <unordered_set>
#include <vector>

using namespace std;

static ifstream fin("runround.in");
static ofstream fout("runround.out");

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

static unordered_set<int> digit_set;
static vector<int> digit_collection;

static bool digit_set_contains(const int digit) {
  return digit_set.find(digit) != cend(digit_set);
}

static bool check_runround(const int length) {
  int i = (0 + digit_collection[0]) % length;
  for (int cnt = 1; cnt < length; ++cnt) {
    if (i == 0) {
      return false;
    }
    i = (i + digit_collection[i]) % length;
  }
  return i == 0;
}

static int convert_to_int() {
  int res = 0;
  for (const int digit : digit_collection) {
    res = res * 10 + digit;
  }
  return res;
}

static bool dfs(const int M, const int length, const int depth = 0) {
  if (depth == length) {
    return check_runround(length) && convert_to_int() > M;
  }
  for (int digit = 1; digit < 10; ++digit) {
    if (digit_set_contains(digit)) {
      continue;
    }
    digit_collection.push_back(digit);
    digit_set.insert(digit);
    if (dfs(M, length, depth + 1)) {
      return true;
    }
    digit_set.erase(digit);
    digit_collection.pop_back();
  }
  return false;
}

static int next_runround(const int M, const int length) {
  if (dfs(M, length)) {
    return convert_to_int();
  }
  return 0;
}

int main() {
  const int M = fin_get<int>();
  for (int b = 1, length = 1; length < 10; ++length) {
    const int e = b * 10;
    if (e > M) {
      const int res = next_runround(M, length);
      if (res != 0) {
        fout << res << endl;
        break;
      }
    }
    b = e;
  }
  // Unreachable.
}

// Below is a much more complex method I've tried to implement
// but get stuck.
// I know it doesn't worth all the time and effort for this small problem,
// but I still tried.
// It's a pity that this way is over complext and I didn't make it out finally.

// static vector<int> digit_collection;
// static unordered_set<int> digit_set;

// static bool digit_set_contains(const int num) {
//   return digit_set.find(num) != cend(digit_set);
// }

// static bool dfs(const int index = 0, const int max_index = 0,
//                 int highest_modified_index = digit_collection.size()) {
//   static int digit_count = digit_collection.size();
//   if (index == 0 && digit_set.size() == digit_count) {
//     return true;
//   }
//   int &digit = digit_collection[index];
//   if (index > highest_modified_index) {
//     digit = 1;
//   }
//   for (; digit <= 9; ++digit) {
//     if (digit == digit_count || digit_set_contains(digit)) {
//       if (index < highest_modified_index && index != max_index) {
//         return false;
//       }
//     } else {
//       digit_set.insert(digit);
//       const int next_index = (index + digit) % digit_count;
//       const bool result =
//           dfs(next_index, max(max_index, next_index),
//           highest_modified_index);
//       digit_set.erase(digit);
//       if (result) {
//         return true;
//       }
//     }
//     highest_modified_index = min(highest_modified_index, index);
//   }
//   if (index != 0) {
//     return false;
//   }
//   digit_collection.assign(++digit_count, 1);
//   return dfs();
// }

// int main() {
//   const int N = fin_get<int>();
//   const string s = to_string(N + 1);
//   transform(cbegin(s), cend(s), back_inserter(digit_collection),
//             [](const char c) { return c - '0'; });
//   dfs();
//   copy(cbegin(digit_collection), cend(digit_collection),
//        ostream_iterator<int>(fout));
//   fout << endl;
// }
