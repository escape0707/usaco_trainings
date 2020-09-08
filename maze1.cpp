/*
ID: totheso1
LANG: C++14
TASK: maze1
*/

#include <algorithm>
#include <array>
#include <fstream>
#include <iterator>
#include <string>
#include <utility>
#include <vector>

using namespace std;

static ifstream fin("maze1.in");
static ofstream fout("maze1.out");

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

static const int WIDTH = fin_get<int>();
static const int HEIGHT = fin_get<int>();
static vector<vector<bool>> available(HEIGHT * 2 + 1,
                                      vector<bool>(WIDTH * 2 + 1, true));
static vector<pair<int, int>> start;

static void initialize() {
  string line;
  getline(fin, line);
  int i = -1;
  while (getline(fin, line)) {
    ++i;
    int j = -1;
    for (const char c : line) {
      ++j;
      if ((i == 0 || i == HEIGHT * 2 || j == 0 || j == WIDTH * 2) && c == ' ') {
        start.emplace_back(i, j);
        available[i][j] = false;
      } else {
        available[i][j] = c == ' ';
      }
    }
  }
}

static int bfs() {
  constexpr array<array<int, 2>, 4> direction_collection = {
      {{-1, 0}, {0, 1}, {1, 0}, {0, -1}}};

  auto que = start;
  int step_doubled = 0;
  while (!que.empty()) {
    ++step_doubled;
    decltype(que) que_next;
    for (const auto &p : que) {
      const int i = get<0>(p);
      const int j = get<1>(p);
      for (const auto &dir : direction_collection) {
        const int di = get<0>(dir);
        const int dj = get<1>(dir);
        const int new_i = i + di;
        const int new_j = j + dj;
        if (0 < new_i && new_i < HEIGHT * 2 && 0 < new_j && new_j < WIDTH * 2) {
          if (available[new_i][new_j]) {
            que_next.emplace_back(new_i, new_j);
            available[new_i][new_j] = false;
          }
        }
      }
    }
    que = move(que_next);
  }
  return step_doubled / 2;
}

int main() {
  initialize();
  fout << bfs() << endl;
}
