/*
ID: totheso1
LANG: C++14
TASK: nocows
*/

#include <algorithm>
#include <fstream>
#include <iterator>
#include <vector>

using namespace std;

static ifstream fin("nocows.in");
static ofstream fout("nocows.out");

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

static constexpr int MODULO = 9901;
static const int NODE_TOTAL = fin_get<int>();
static const int MAX_HEIGHT = fin_get<int>();

int main() {
  if ((NODE_TOTAL & 1) == 0) {
    fout << 0 << endl;
    return 0;
  }
  vector<vector<int>> dp_no_more_than(MAX_HEIGHT + 1,
                                      vector<int>(NODE_TOTAL + 1, 0));
  vector<vector<int>> dp_exact(MAX_HEIGHT + 1, vector<int>(NODE_TOTAL + 1, 0));
  dp_exact[1][1] = 1;
  for (int height = 2; height <= MAX_HEIGHT; ++height) {
    for (int node_count = 1; node_count <= NODE_TOTAL; node_count += 2) {
      const int half_node_count = (node_count - 1) / 2;
      for (int left_child_node_count = 1;
           left_child_node_count <= half_node_count;
           left_child_node_count += 2) {
        const int right_child_node_count =
            node_count - 1 - left_child_node_count;
        const int multiplier =
            1 + static_cast<int>(left_child_node_count != half_node_count);
        dp_exact[height][node_count] +=
            multiplier *
            (dp_exact[height - 1][left_child_node_count] *
                 dp_no_more_than[height - 2][right_child_node_count] +
             dp_exact[height - 1][right_child_node_count] *
                 dp_no_more_than[height - 2][left_child_node_count] +
             dp_exact[height - 1][left_child_node_count] *
                 dp_exact[height - 1][right_child_node_count]);
        dp_exact[height][node_count] %= MODULO;
      }
    }
    for (int node_count = 1; node_count <= NODE_TOTAL; node_count += 2) {
      dp_no_more_than[height - 1][node_count] =
          (dp_exact[height - 1][node_count] +
           dp_no_more_than[height - 2][node_count]) %
          MODULO;
    }
  }
  fout << dp_exact[MAX_HEIGHT][NODE_TOTAL] << endl;
}
