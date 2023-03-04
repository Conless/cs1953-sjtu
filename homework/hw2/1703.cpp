// Statement and information
// Author: Conless
// Date: 2022-10-18
// File name: /course/22fall/sjtu/cs1953/homework/hw2/1703.cpp

// Headers
#include <bits/stdc++.h>

// Constants, global variables and definitions

typedef std::pair<long long, long long> pr;

const int MAXN = 1e5 + 5;

int n;
long long ans, res[65];
pr data[MAXN];

// Templates and namespaces

// Classes

// Funtions
bool comp(pr a, pr b) { return a.first > b.first; }

bool insert(int itf) {
    for (int j = 63; j >= 0; j--) {
        if ((itf >> j) & 1LL) {
            if (res[j])
                itf ^= res[j];
            else {
                res[j] = itf;
                return 1;
            }
        }
    }
    return 0;
}

// Main function
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        std::cin >> data[i].second >> data[i].first;
    std::sort(data + 1, data + n + 1, comp);
    for (int i = 1; i <= n; i++) {
        if (insert(data[i].second))
            ans += data[i].first;
    }
    printf("%lld\n", ans);
    return 0;
}