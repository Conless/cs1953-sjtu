// Statement and information
// Author: Conless
// Date: 2022-11-16
// File name: /course/22fall/sjtu/cs1953/homework/hw4/1748makedata.cpp

#include <bits/stdc++.h>

using namespace std;

int main() {
    int n = 3000;
    time_t t;
    srand(time(&t));
    freopen("1748.in", "w", stdout);
    cout << n << endl;
    for (int i = 1; i <= n; i++) {
        int num = (rand() % 100000) + 1;
        cout << num << " ";
    }
    cout << endl;
    return 0;
}