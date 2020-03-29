/*
ID: totheso1
LANG: C++14
TASK: gift1
*/

#include <algorithm>
#include <array>
#include <fstream>
#include <iterator>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

static ifstream fin("gift1.in");
static ofstream fout("gift1.out");

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
    const int number_of_people = fin_get<int>();

    const vector<string> &name_collection =
        fin_get_collection<vector<string>>(number_of_people);
    unordered_map<string, int> gain_by_name;
    for (const string &name : name_collection) {
        gain_by_name.emplace(name, 0);
    }

    for (int i = 0; i < number_of_people; ++i) {
        const string &giver_name = fin_get<string>();
        const int total = fin_get<int>();
        const int number_of_gifts = fin_get<int>();
        if (number_of_gifts) {
            const int gift = total / number_of_gifts;
            gain_by_name[giver_name] -= gift * number_of_gifts;
            for (int j = 0; j < number_of_gifts; ++j) {
                const string &receiver_name = fin_get<string>();
                gain_by_name[receiver_name] += gift;
            }
        }
    }

    for (const string &name : name_collection) {
        fout << name << ' ' << gain_by_name[name] << endl;
    }
}
