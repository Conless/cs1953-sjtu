#include <bits/stdc++.h>

using namespace std;

#define ca Date

const int month_days[2][13] = {{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
                               {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};
const int day_sum_month[2][13] = {{0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365},
                                  {0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366}};

inline bool is_run(int year) { return (year % 4 == 0 && year % 100) || (year % 400 == 0); }

inline int year_to_cnt(const int &year) { return year * 365 + year / 4 - year / 100 + year / 400; }
inline int month_to_cnt(const bool &is_run, const int &month) { return day_sum_month[is_run][month]; }
inline int day_to_cnt(const int &day) { return day; }

int to_int(const std::string &s);
std::string to_str(int cnt);

class Date {
  private:
    int cnt;

  public:
    Date() { *this = Date(1900, 1, 1); }
    Date(int year, int month, int day) {
        if ((month < 1 || month > 12) || day > month_days[is_run(year)][month])
            year = 1900, month = 1, day = 1;
        cnt = year_to_cnt(year - 1) + month_to_cnt(is_run(year), month - 1) + day_to_cnt(day);
    }
    Date(const std::string &s) { *this = Date(to_int(s.substr(0, 4)), to_int(s.substr(5, 2)), to_int(s.substr(8, 2))); }

  private:
    Date(const int &cnt) : cnt(cnt) {}

  public:
    friend bool operator==(const ca &x, const ca &y) { return x.cnt == y.cnt; }
    friend bool operator!=(const ca &x, const ca &y) { return x.cnt != y.cnt; }
    friend bool operator>=(const ca &x, const ca &y) { return x.cnt >= y.cnt; }
    friend bool operator<=(const ca &x, const ca &y) { return x.cnt <= y.cnt; }
    friend bool operator>(const ca &x, const ca &y) { return x.cnt > y.cnt; }
    friend bool operator<(const ca &x, const ca &y) { return x.cnt < y.cnt; }

  public:
    friend ca operator+(ca x, const int &y) { return ca(x.cnt + y); }
    friend ca operator-(ca x, const int &y) { return ca(x.cnt - y); }

    ca &operator+=(const int &y) { return *this = ca(cnt + y); }
    ca &operator-=(const int &y) { return *this = ca(cnt - y); }

    ca &operator++() { return *this += 1; }
    ca &operator--() { return *this -= 1; }
    ca operator++(int) { return Date((*this += 1).cnt - 1); }
    ca operator--(int) { return Date((*this -= 1).cnt + 1); }

    friend int operator-(const ca &x, const ca &y) { return abs(x.cnt - y.cnt); }

  public:
    operator std::string() { return to_str(cnt); }
    int getday() { return cnt % 7; }
};

int to_int(const std::string &s) {
    int res = 0;
    for (int i = 0; i < s.size(); i++)
        res = res * 10 + s[i] - '0';
    return res;
}
std::string to_str(int cnt) {
    int year = 0, month = 0;
    for (int i = 15; ~i; i--)
        if (year_to_cnt(year | (1 << i)) < cnt)
            year |= (1 << i);
    cnt -= year_to_cnt(year);
    year++;
    for (; day_sum_month[is_run(year)][month] < cnt; month++)
        ;
    cnt -= day_sum_month[is_run(year)][month - 1];
    char out_str[11];
    sprintf(out_str, "%d-%d-%d", year, month, cnt);
    return std::string(out_str);
}
std::ostream &operator<<(std::ostream &out, ca x) {
    out << std::string(x);
    return out;
}

void Test() {
    int op;
    cin >> op;
    int yy, mm, dd;
    if (op == 1 || op == 0) {
        Date d0;
        Date d1(2000, 2, 29);
        Date d2(1900, 2, 29);
        cout << d0 << endl;
        cout << d1 << endl;
        cout << d2 << endl;
        // d0.out(); d1.out(); d2.out();
    }
    if (op == 2 || op == 0) {
        cin >> yy >> mm >> dd;
        Date d0(yy, mm, dd);
        for (int i = 0; i < 5; ++i)
            cout << ++d0 << endl; //(++d0).out();
        for (int i = 0; i < 5; ++i)
            cout << d0++ << endl; //(d0++).out();
        for (int i = 0; i < 5; ++i)
            cout << d0-- << endl; //(d0--).out();
        for (int i = 0; i < 2; ++i)
            cout << --d0 << endl; //(--d0).out();
        cout << d0 << endl;
        // d0.out();
    }
    if (op == 3 || op == 0) {
        cin >> yy >> mm >> dd;
        Date d0(yy, mm, dd);
        cout << d0 + 100 << endl;
        // (d0+100).out();
        cout << d0 - 1000 << endl;
        // (d0-1000).out();
    }
    if (op == 4 || op == 0) {
        cin >> yy >> mm >> dd;
        Date d0(yy, mm, dd);
        Date d1(2020, 12, 21);
        cout << (d0 < d1) << endl;
    }
    if (op == 5 || op == 0) {
        cin >> yy >> mm >> dd;
        Date d0(yy, mm, dd);
        Date d1(1912, 6, 23);
        cout << d0 - d1 << endl;
    }
}
int main() {
    Test();
    return 0;
}
