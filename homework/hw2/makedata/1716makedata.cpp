// Statement and information
// Author: Conless
// Date: 2022-10-14
// File name: /oi/acmoj/1716makedata.cpp

// Headers
#include <bits/stdc++.h>

using namespace std;
// Constants, global variables and definitions

// Templates and namespaces

// Classes

// Funtions

// Main function
int main() {
    freopen("1716.in", "w", stdout);
    time_t t;
    vector<int> vec;
    srand(time(&t));
    int n = 1e5;
    printf("%d\n", n);
    for (int i = 1; i <= n; i++)
        vec.push_back(i);
    random_shuffle(vec.begin(), vec.end());
    for (int i = 1; i <= n; i++)
        printf("%d ", vec[i - 1]);
    return 0;
}