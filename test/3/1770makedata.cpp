#include <bits/stdc++.h>

using namespace std;

int main() {
    int n = 8, m = 200;
    ios::sync_with_stdio(false);
    freopen("1770.in", "w", stdout);
    cout << n << " " << m << endl;
    for (int i = 1; i <= m; i++) {
        back:int u = rand() % n + 1, v = rand() % n + 1, w = rand() % 30 + 1;
        if (u == v)
            goto back;
        cout << u << " " << v << " " << w << endl;
    }
    return 0;
}