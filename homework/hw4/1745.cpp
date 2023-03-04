// Statement and information
// Author: Conless
// Date: 2022-11-12
// File name: /course/22fall/sjtu/cs1953/homework/hw4/1745.cpp

#include <bits/stdc++.h>
#include <ctime>

using std::cin;
using std::cout;
using std::max;

const int MAXN = 1e5 + 5;

int n, mt, h[MAXN];
int t[20], mxr[MAXN][20], mxl[MAXN][20];
int lg[MAXN];
int disl[1005], disr[1005];

// inline int max(int a, int b) { return a < b ? b : a; }

void pre() {
    t[0] = 1;
    for (int i = 1; i <= n; i++)
        lg[i] = (int)(log(1.0 * i) / log(2.0));
    for (int i = 1; i < 20; i++)
        t[i] = t[i - 1] << 1;
    for (int i = 1; i <= n; i++)
        mxr[i][0] = mxl[i][0] = h[i];
    for (int j = 1; j < 20; j++) {
        for (int i = 1; i <= n; i++) {
            if (i + t[j] - 1 > n)
                break;
            mxr[i][j] = max(mxr[i][j - 1], mxl[i + t[j] - 1][j - 1]);
        }
        for (int i = t[j]; i <= n; i++) {
            mxl[i][j] = max(mxr[i - t[j] + 1][j - 1], mxl[i][j - 1]);
        }
    }
    mt = ceil(sqrt(n));
    for (int i = 1; i <= mt; i++) {
        disl[i] = (i - 1) * (i - 1) + 1;
        disr[i] = i * i;
    }
}

inline int query(int l, int r) {
    int lgg = lg[r - l + 1];
    return max(mxr[l][lgg], mxl[r][lgg]);
}

int main() {
    freopen("1745.in", "r", stdin);
    freopen("1745.out", "w", stdout);
    std::ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> h[i];
    pre();
    // double tt = (double)clock() / CLOCKS_PER_SEC;
    // printf("%.2lf\n", tt);
    for (int i = 1; i <= n; i++) {
        int ans = 0;
        for (int j = 1; j <= mt; j++) {
            // search the left
            if (i > disl[j]) {
                if (i > disr[j])
                    ans = max(ans, query(i - disr[j], i - disl[j]) + j - h[i]);
                else ans = max(ans, query(1, i - disl[j]) + j - h[i]);
            }
            // search the right
            if (i + disl[j] <= n) {
                if (i + disr[j] <= n)
                    ans = max(ans, query(i + disl[j], i + disr[j]) + j - h[i]);
                else ans = max(ans, query(i + disl[j], n) + j - h[i]);
            }
        }
        cout << ans << '\n';
    }
    // printf("%.2lf\n", (double)clock() / CLOCKS_PER_SEC);
    return 0;
}