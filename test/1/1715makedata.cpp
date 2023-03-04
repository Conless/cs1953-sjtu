#include <bits/stdc++.h>

using namespace std;

int main() {
    freopen("1715.in", "w", stdout);
    int nn = 1e3;
    for (int i = 1; i <= nn; i++)
        putchar('a' + (rand() % 26));
    putchar('\n');
    for (int i = 1; i <= nn/3; i++)
        putchar('a' + (rand() % 26));
    putchar('$');
    for (int i = 1; i <= nn/3; i++)
        putchar('a' + (rand() % 26));
    putchar('\n');
    int n = 1e3, k = 200;
    printf("%d %d\n", n, k);
    for (int i = 1; i <= k; i++) {
        long long l = (1LL * rand() * rand()) % 100000 + 1;
        printf("%lld %lld\n", l, l + 50);
    }
    return 0;
}