/*
ID: totheso1
LANG: C++14
TASK: snail
*/

#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int N, B, ans;
vector<vector<char>> grid;
vector<vector<bool>> visited;
int dx[] = {-1, 0, 0, 1};
int dy[] = {0, -1, 1, 0};

bool on_grid(int x, int y) {
  return x >= 1 && y >= 1 && x <= N && y <= N;
}

vector<int> next_dir(int d) {
  if (d == 0 || d == 3) {
    return {1, 2};
  } else {
    return {0, 3};
  }
}

void move(int x, int y, int d, int step) {
  if (visited[x][y]) return;
  visited[x][y] = true;
  ans = std::max(ans, step);
  int xx = x + dx[d], yy = y + dy[d];
  if (on_grid(xx, yy) && grid[xx][yy] != '#') {
    move(xx, yy, d, step + 1);
  } else {
    auto dirs = next_dir(d);
    for (auto dir : dirs) {
      xx = x + dx[dir];
      yy = y + dy[dir];
      if (on_grid(xx, yy) && grid[xx][yy] == '.') {
        move(xx, yy, dir, step + 1);
      }
    }
  }
  visited[x][y] = false;
}

int main() {
  ifstream fin("snail.in");
  ofstream fout("snail.out");
  fin >> N >> B;
  grid = vector<vector<char>>(N + 1, vector<char>(N + 1, '.'));
  visited = vector<vector<bool>>(N + 1, vector<bool>(N + 1, false));
  for (int i = 1; i <= B; ++i) {
    char col;
    int row;
    fin >> col >> row;
    grid[row][col - 'A' + 1] = '#';
  }

  move(1, 1, 2, 1);
  for (int i = 0; i <= N; ++i) {
    for (int j = 0; j <= N; ++j) {
      visited[i][j] = false;
    }
  }

  move(1, 1, 3, 1);

  cout << ans << endl;
  fout << ans << endl;
}
