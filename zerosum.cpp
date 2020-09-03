/*
ID: totheso1
LANG: C++14
TASK: zerosum
*/

#include <algorithm>
#include <fstream>
#include <iterator>
#include <vector>

using namespace std;

static ifstream fin("zerosum.in");
static ofstream fout("zerosum.out");

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

static const int N = fin_get<int>();

static bool sum_to_zero(const vector<int> &sequence) {
  int total = 0;
  int current_term = 1;
  int sign = 1;
  int digit = 1;
  for (const int opt_id : sequence) {
    ++digit;
    if (opt_id == 0) {
      current_term = current_term * 10 + digit;
    } else {
      total += sign * current_term;
      current_term = digit;
      sign = opt_id == 1 ? 1 : -1;
    }
  }
  return total + sign * current_term == 0;
}

static void output(const vector<int> &sequence) {
  const char opt_table[] = " +-";
  int digit = 0;
  for (const int opt_id : sequence) {
    ++digit;
    fout << digit << opt_table[opt_id];
  }
  fout << digit + 1 << endl;
}

static void dfs(const int N, const int depth = 0) {
  static vector<int> sequence;
  if (N < 3) {
    throw invalid_argument("N must be larger than or equal to 3.");
  }
  if (depth == 0) {
    sequence.resize(N - 1);
  }
  if (depth == N - 1) {
    if (sum_to_zero(sequence)) {
      output(sequence);
    }
    return;
  }
  for (int i = 0; i < 3; ++i) {
    sequence[depth] = i;
    dfs(N, depth + 1);
  }
}

int main() {
  dfs(N);
}
