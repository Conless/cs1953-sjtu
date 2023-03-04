// Statement and information
// Author: Conless
// Date: 2022-10-12
// File name: /oi/acmoj/1666makedata.cpp

// Headers
#include <bits/stdc++.h>
#include <ostream>

// Constants, global variables and definitions
using namespace std;

// Templates and namespaces

// Classes

// Funtions

// Main function
int main() {
    time_t t;
    srand(time(&t));
    freopen("1666.in", "w", stdout);
    int n = 10, m = 8;
    cout << n << " " << m << endl;
    for (int i = 1; i <= m; i++) {
        int x, y;
        x = rand() % 100 + 1;
        y = rand() % 100 + 1;
        printf("%d %d\n", x, y);
    }
    int p = 10;
    cout << p << endl;
    while (p--) {
        int x, y;
        x = rand() % 100 + 1;
        y = rand() % 100 + 1;
        printf("%d %d\n", x, y);
    }
    return 0;
}