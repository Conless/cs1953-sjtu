// Statement and information
// Author: Conless
// Date: 2022-11-14
// File name: /course/22fall/sjtu/cs1953/test/2/1740makedata.cpp

#include <bits/stdc++.h>

using namespace std;

int main() {
    time_t t;
    srand(time(&t));
    freopen("1740.in", "w", stdout);
    int n = 10, m = 20;
    cout << n << " " << m << endl;
    for (int i = 1; i <= m; i++) {
        int x = rand() % n + 1;
        int y = rand() % n + 1;
        cout << x << " " << y << endl;
    }
    int q = 10;
    cout << q << endl;
    for (int i = 1; i <= q; i++) {
        int x = rand() % n + 1;
        int y = rand() % n + 1;
        int z = rand() % (n - 1) + 2;
        cout << x << " " << y << " " << z << endl;
    }
    return 0;
}