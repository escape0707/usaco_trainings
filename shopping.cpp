/*
ID: totheso1
LANG: C++14
TASK: shopping
*/

#include <algorithm>
#include <fstream>
#include <iterator>
#include <limits>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

static ifstream fin("shopping.in");
static ofstream fout("shopping.out");

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

static const int OFFER_COUNT = fin_get<int>();
static auto offer_collection = []() {
  vector<pair<unordered_map<int, int>, int>> res;
  for (int i = 0; i < OFFER_COUNT; ++i) {
    unordered_map<int, int> offer_content;
    for (int offer_size = fin_get<int>(); offer_size; --offer_size) {
      const int product_code = fin_get<int>();
      const int product_count = fin_get<int>();
      offer_content.emplace(product_code, product_count);
    }
    const int reduced_price = fin_get<int>();
    res.emplace_back(move(offer_content), reduced_price);
  }
  return res;
}();
static const int REQUIREMENT_COUNT = fin_get<int>();
static const auto product_collection = []() {
  vector<array<int, 3>> res;
  for (int i = 0; i < REQUIREMENT_COUNT; ++i) {
    const int product_code = fin_get<int>();
    const int requirement = fin_get<int>();
    const int regular_price = fin_get<int>();
    res.push_back({product_code, requirement, regular_price});
  }
  return res;
}();

int main() {
  const auto less_equal = [](int state_a, int state_b) {
    while (state_a || state_b) {
      if (state_a % 6 > state_b % 6) {
        return false;
      }
      state_a /= 6;
      state_b /= 6;
    }
    return true;
  };

  constexpr array<int, 6> power_6_collection = {1, 6, 36, 216, 1296, 7776};

  unordered_map<int, int> power_6_by_product_code_collection;
  auto power_6_iter = cbegin(power_6_collection);
  for (const auto &arr : product_collection) {
    const int product_code = get<0>(arr);
    const int regular_price = get<2>(arr);
    power_6_by_product_code_collection.emplace(product_code, *power_6_iter);
    offer_collection.push_back({{{product_code, 1}}, regular_price});
    ++power_6_iter;
  }

  constexpr int STATE_COUNT = power_6_collection[5];
  vector<int> dp(STATE_COUNT, numeric_limits<int>::max() / 2);  // Big enough
  dp[0] = 0;
  for (const auto &offer : offer_collection) {
    const unordered_map<int, int> &offer_content = offer.first;
    const int price = offer.second;
    int min_state = 0;
    for (const auto &p : offer_content) {
      const int product_code = p.first;
      const int product_count = p.second;
      if (power_6_by_product_code_collection.find(product_code) ==
          cend(power_6_by_product_code_collection)) {
        min_state = 0;
        break;
      }
      min_state +=
          power_6_by_product_code_collection[product_code] * product_count;
    }
    if (min_state == 0) {
      continue;
    }
    for (int state = 0; state < STATE_COUNT; ++state) {
      if (less_equal(min_state, state)) {
        dp[state] = min(dp[state], dp[state - min_state] + price);
      }
    }
  }

  int target_state = 0;
  power_6_iter = cbegin(power_6_collection);
  for (const auto &arr : product_collection) {
    const int requirement = get<1>(arr);
    target_state += *power_6_iter * requirement;
    ++power_6_iter;
  }
  fout << dp[target_state] << endl;
}
