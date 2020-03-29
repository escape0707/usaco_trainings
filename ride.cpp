/*
ID: totheso1
LANG: C++14
TASK: ride
*/

#include <fstream>
#include <iterator>
#include <numeric>
#include <string>

using namespace std;

static ifstream fin("ride.in");
static ofstream fout("ride.out");

static int convert(const string &name) {
    // if C++17: std::transform_reduce
    int ret = 1;
    for (const char c : name) {
        ret *= c - 64;
    }
    return ret % 47;
}

int main() {
    istream_iterator<string> lines_iter(fin);
    fout << (convert(*lines_iter++) == convert(*lines_iter) ? "GO" : "STAY")
         << endl;
}
