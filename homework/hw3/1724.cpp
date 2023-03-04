// Statement and information
// Author: Conless
// Date: 2022-10-27
// File name: /course/22fall/sjtu/cs1953/homework/hw3/1724.cpp

#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>

using __gnu_pbds::gp_hash_table;
using std::max;
using std::min;

const int MAXN = 1e5 + 5;

int n, m, maxval, ans;
int data[MAXN], minnum[MAXN], maxnum[MAXN];
gp_hash_table<int, int> c[MAXN];

inline int lowbit(int x) { return x & (-x); }

void add(int x, int y, int v) {
    int i = x;
    while (i <= maxval) {
        int j = y;
        while (j <= maxval) {
            c[i][j] = max(c[i][j], v);
            j += lowbit(j);
        }
        i += lowbit(i);
    }
}

int ask(int x, int y) {
    int res = 0, i = x;
    while (i) {
        int j = y;
        while (j) {
            res = max(res, c[i][j]);
            j -= lowbit(j);
        }
        i -= lowbit(i);
    }
    return res;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &data[i]);
        maxval = max(maxval, data[i]);
        maxnum[i] = minnum[i] = data[i];
    }
    for (int i = 1, x, y; i <= m; i++) {
        scanf("%d%d", &x, &y);
        maxnum[x] = max(maxnum[x], y);
        minnum[x] = min(minnum[x], y);
        maxval = max(maxval, maxnum[x]);
    }
    for (int i = 1; i <= n; i++) {
        int res = ask(minnum[i], data[i]) + 1;
        add(data[i], maxnum[i], res);
        ans = max(ans, res);
    }
    printf("%d\n", ans);
    return 0;
}