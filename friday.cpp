/*
ID: totheso1
LANG: C++14
TASK: friday
*/

#include <algorithm>
#include <array>
#include <experimental/iterator>
#include <fstream>
#include <iterator>

using namespace std;

static ifstream fin("friday.in");
static ofstream fout("friday.out");

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

constexpr array<int, 12> DAYS_OF_MONTH = {31, 28, 31, 30, 31, 30,
                                          31, 31, 30, 31, 30, 31};

static bool is_leap_year(const int year) {
    if (year % 4 != 0) {
        return false;
    }
    if (year % 100 != 0) {
        return true;
    }
    return year % 400 == 0;
}

static array<int, 7> frequency;

int main() {
    const int end_year = fin_get<int>() + 1900;
    int day_of_13th = 0;  // (2 + 13 - 1) % 7
    for (int year = 1900; year < end_year; ++year) {
        for (int month = 0; month < 12; ++month) {
            ++frequency[day_of_13th];
            day_of_13th = (day_of_13th + DAYS_OF_MONTH[month] +
                           (month == 1 && is_leap_year(year))) %
                          7;
        }
    }
    // Wow, USACO Training support std::experimental... I'm shocked.
    copy(begin(frequency), end(frequency),
         experimental::make_ostream_joiner(fout, " "));
    fout << endl;
}
