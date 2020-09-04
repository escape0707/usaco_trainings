/*
ID: totheso1
LANG: C++14
TASK: concom
*/

#include <algorithm>
#include <fstream>
#include <iterator>
#include <limits>
#include <stack>
#include <vector>

using namespace std;

static ifstream fin("concom.in");
static ofstream fout("concom.out");

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

static constexpr int MAX_COMPANY = 100;
static vector<vector<int>> own(MAX_COMPANY, vector<int>(MAX_COMPANY, 0));
static vector<vector<bool>> control(MAX_COMPANY,
                                    vector<bool>(MAX_COMPANY, false));

static void initialize() {
  for (int i = 0; i < MAX_COMPANY; ++i) {
    control[i][i] = true;
  }
}

static void solve() {
  int line_count = fin_get<int>();
  while (line_count--) {
    const int i = fin_get<int>();
    const int j = fin_get<int>();
    const int percentage = fin_get<int>();
    own[i - 1][j - 1] = percentage;
    // own[fin_get<int>() - 1][fin_get<int>() - 1] = fin_get<int>();  // This is
    // wrong, because the evaluation order of function might not be what you
    // think.
  }

  for (int root = 0; root < MAX_COMPANY; ++root) {
    stack<int> stk({root});
    vector<vector<int>> total_percentage(MAX_COMPANY,
                                         vector<int>(MAX_COMPANY, 0));
    while (!stk.empty()) {
      const int curr = stk.top();
      stk.pop();
      for (int other = 0; other < MAX_COMPANY; ++other) {
        if (!control[root][other]) {
          total_percentage[root][other] += own[curr][other];
          if (total_percentage[root][other] > 50) {
            control[root][other] = true;
            stk.push(other);
          }
        }
      }
    }
  }

  int i = -1;
  for (const auto &row : control) {
    ++i;
    int j = -1;
    for (const bool is_controlling : row) {
      ++j;
      if (is_controlling && i != j) {
        fout << i + 1 << ' ' << j + 1 << endl;
      }
    }
  }
}

int main() {
  initialize();
  solve();
}
