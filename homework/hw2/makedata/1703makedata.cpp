#include <bits/stdc++.h>
#include <cstdlib>
#include <unordered_map>

using namespace std;

unordered_map<long long, int> ma;

int main() {
    freopen("1703.in", "w", stdout);
    time_t t;
    srand(time(&t));
    int n = rand() % 100000 + 1;
    cout << n << endl;
    for (int i = 1; i <= n; i++) {
        int a = rand(), b = 1LL * rand() * rand() % 100000000000LL;
        b = b < 0 ? -b : b;
        while (ma[b] == 1)
            b = 1LL * rand() * rand() % 100000000000LL, b = b < 0 ? -b : b;
        ma[b] = 1;
        printf("%d %d\n", b, a);
    }
    return 0;
}