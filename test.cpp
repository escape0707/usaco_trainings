/*
ID: totheso1
LANG: C++14
TASK: test
*/

#include <fstream>
#include <iterator>
#include <numeric>

using namespace std;

static ifstream fin("test.in");
static ofstream fout("test.out");

int main() {
    istream_iterator<int> b(fin), e;
    fout << accumulate(b, e, 0) << endl;
}
