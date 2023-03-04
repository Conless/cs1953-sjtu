// Statement and information
// Author: Conless
// Date: 2022-11-16
// File name: /course/22fall/sjtu/cs1953/homework/hw4/1746makedata.cpp

#include <bits/stdc++.h>

using namespace std;

int main() {
    freopen("1746.in", "w", stdout);
    int k = 15, n = 25;
    cout << k << " " << n << endl;
    for (int i = 1; i <= n; i++) {
        int v = rand() % 100, s = rand() % 100, r = rand() % n;
        cout << v << " " << s << " " << r << endl;
    }
    return 0;
}