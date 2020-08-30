/*
ID: totheso1
LANG: C++14
TASK: lamps
*/

#include <algorithm>
#include <bitset>
#include <fstream>
#include <iterator>
#include <vector>

using namespace std;

static ifstream fin("lamps.in");
static ofstream fout("lamps.out");

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

static constexpr int MAXLAMPS = 6;
static constexpr int MAXSWITCH = 4;

static int mod(const int dividend, const int divisor) {
  const int res = dividend % divisor;
  return res >= 0 ? res : res + divisor;
}

int main() {
  const int N = fin_get<int>();
  const int C = fin_get<int>();
  bitset<MAXLAMPS> bit_mask, bit_requirement;
  for (int i; (i = fin_get<int>()) != -1;) {
    bit_mask[mod(-i, MAXLAMPS)] = true;
    bit_requirement[mod(-i, MAXLAMPS)] = true;
  }
  for (int i; (i = fin_get<int>()) != -1;) {
    bit_mask[mod(-i, MAXLAMPS)] = true;
  }

  const vector<bitset<MAXLAMPS>> button_effect_collection = {
      0b111111, 0b101010, 0b010101, 0b100100};
  vector<bitset<MAXLAMPS>> ans;
  for (int cnt = C & 1, e = min(MAXSWITCH + 1, C + 1); cnt < e; cnt += 2) {
    vector<bool> switch_collection(MAXSWITCH, false);
    fill_n(begin(switch_collection), cnt, true);
    do {
      bitset<MAXLAMPS> state = button_effect_collection[0];
      int i = -1;
      for (const bool switch_on : switch_collection) {
        ++i;
        if (switch_on) {
          state ^= button_effect_collection[i];
        }
      }
      if ((state & bit_mask) == bit_requirement) {
        ans.push_back(move(state));
      }
    } while (
        prev_permutation(begin(switch_collection), end(switch_collection)));
  }
  if (ans.empty()) {
    fout << "IMPOSSIBLE" << endl;
  } else {
    sort(begin(ans), end(ans),
         [](const bitset<MAXLAMPS> &lhs, const bitset<MAXLAMPS> &rhs) {
           return lhs.to_ulong() < rhs.to_ulong();
         });
    for (const auto &state : ans) {
      for (int i = 1; i <= N; ++i) {
        fout << state[mod(-i, MAXLAMPS)];
      }
      fout << endl;
    }
  }
}
