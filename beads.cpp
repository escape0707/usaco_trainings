/*
ID: totheso1
LANG: C++14
TASK: beads
*/

#include <algorithm>
#include <fstream>
#include <iterator>
#include <string>

using namespace std;

static ifstream fin("beads.in");
static ofstream fout("beads.out");

template <typename T>
T fin_get() {
    return *istream_iterator<T>(fin);
}

template <typename C>
C fin_get_collection(int size) {
    C ret;
    copy_n(istream_iterator<typename C::value_type>(fin), size,
           back_inserter(ret));
    return ret;
}

int main() {
    const int number_of_beads = fin_get<int>();
    string &&input = fin_get<string>();
    const string &beads = input + input;

    int left_count = 0;
    int left_white = 0;
    int right_count = 0;
    int right_white = 0;
    int current_split_count =
        left_count + left_white + right_count + right_white;
    int max_split_count = 0;
    char right_color = '\0';

    for (const char bead : beads) {
        if (bead == 'w') {
            right_white += 1;
            current_split_count += 1;
        } else {
            if (bead == right_color) {
                right_count += right_white + 1;
                right_white = 0;
                current_split_count += 1;
            } else {
                if (current_split_count > max_split_count) {
                    max_split_count = current_split_count;
                }
                current_split_count -= left_count - 1;
                right_color = bead;
                left_count = left_white + right_count;
                left_white = right_white;
                right_count = 1;
                right_white = 0;
            }
        }
    }

    max_split_count =
        min(number_of_beads, max(max_split_count, current_split_count));
    fout << max_split_count << endl;
}
