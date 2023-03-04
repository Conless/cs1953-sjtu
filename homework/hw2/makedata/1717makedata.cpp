#include <bits/stdc++.h>

using namespace std;

int main() {
    freopen("1717.in", "w", stdout);
    time_t t;
    srand(time(&t));
    int n = 1e6, m = 1e5;
    printf("%d %d\n", n, m);
    for (int i = 1; i <= n; i++)
        printf("%d ", rand() * rand() % 1000000 + 1);
    printf("\n");
    while (m--) {
        int p = rand() % (n - 1) + 1;
        int x = rand();
        printf("%d %d\n", p, x);
    }
    return 0;
}