/*
ID: totheso1
LANG: C++14
TASK: rockers
*/

#include <algorithm>
#include <fstream>
#include <iterator>
#include <vector>

using namespace std;

static ifstream fin("rockers.in");
static ofstream fout("rockers.out");

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

static const int SONG_COUNT = fin_get<int>();
static const int DISK_SIZE = fin_get<int>();
static const int DISK_COUNT = fin_get<int>();

static void solve() {
  vector<vector<int>> dp(DISK_COUNT + 1, vector<int>(DISK_SIZE + 1, 0));
  for (int song_length; fin >> song_length;) {
    for (int disk = DISK_COUNT; disk >= 1; --disk) {
      for (int curr_size = DISK_SIZE; curr_size >= song_length; --curr_size) {
        dp[disk][curr_size] =
            max({dp[disk][curr_size], dp[disk][curr_size - song_length] + 1,
                 dp[disk - 1][DISK_SIZE] + 1});
      }
    }
  }
  fout << dp[DISK_COUNT][DISK_SIZE] << endl;
}

int main() {
  solve();
}
