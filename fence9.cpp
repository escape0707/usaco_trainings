/*
ID: totheso1
LANG: C++14
TASK: fence9
*/

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iterator>

using namespace std;

static ifstream fin("fence9.in");
static ofstream fout("fence9.out");

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

static const int X1 = fin_get<int>();
static const int Y1 = fin_get<int>();
static const int X2 = fin_get<int>();

static int gcd(int a, int b) {
  return a == 0 ? abs(b) : b == 0 ? abs(a) : gcd(b, a % b);
}

static void solve_O_N() {
  int ans = 0;
  for (int y = 1; y < Y1; ++y) {
    ans += static_cast<int>(ceil((X1 - X2) * y / static_cast<double>(Y1))) +
           X2 - 1 - static_cast<int>(floor(X1 * y / static_cast<double>(Y1)));
  }
  fout << ans << endl;
}

static void solve_O_logN() {
  const int boundary_lattice_count = gcd(X1, Y1) + gcd(abs(X2 - X1), Y1) + X2;
  fout << (X2 * Y1 - boundary_lattice_count + 2) / 2 << endl;
}

int main() {
  solve_O_logN();
}
