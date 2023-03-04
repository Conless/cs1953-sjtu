//1
#include "1292.hpp"
using namespace std;
int main() {
    freopen("1292.out", "w", stdout);
    ios::sync_with_stdio(false);
    Calendar cend = Calendar("1005-12-31");
    Calendar c(1000,1,1);
    Calendar startc;
    startc = c;
    for (; c < cend; c+=2) {
        cout << string(c++) << endl;
        cout << (++c).getday() << endl;
    }
    for (; c >= startc; c-=10) {
        cout << string(c--) << endl;
        cout << (--c).getday() << endl;
    }
    c = Calendar("0001-01-01")+1400;
    Calendar cc = c - 1400;
    for (; cc < c + 1400; ++cc) {
        cout << (cc > c) << (cc == c) << (cc < c) << (cc == c) << (cc != c);
        cout << (cc-c);
    }
}