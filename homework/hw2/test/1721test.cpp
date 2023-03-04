#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 5003, maxm = maxn << 1;
int n, u[maxm], v[maxm], fst[maxn], nxt[maxm], d[maxn];
bool book[maxn];
int non, ans, fa[4], id, fans;
inline bool valid(int i) { return (i == non) || (i == non + n - 1); }
void dp(int x) {
    book[x] = 1;
    for (int i = fst[x]; i; i = nxt[i]) {
        if (valid(i))
            continue;
        int y = v[i];
        if (book[y])
            continue;
        dp(y);
        ans = max(ans, d[x] + d[y] + 1);
        d[x] = max(d[x], d[y] + 1);
    }
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 1; i < n; ++i) {
        cin >> u[i] >> v[i];
        nxt[i] = fst[u[i]], fst[u[i]] = i;
        int j = i + n - 1;
        u[j] = v[i], v[j] = u[i];
        nxt[j] = fst[u[j]], fst[u[j]] = j;
    }
    for (non = 1; non < n; ++non) {
        // 求直径
        memset(book, 0, sizeof(book));
        memset(d, 0, sizeof(d));
        id = 0;
        fa[0] = fa[1] = 0;
        for (int i = 1; i <= n; ++i)
            if (!book[i]) {
                ans = 0;
                dp(i);
                // printf("%d %d %d\n", non, i, ans);
                fa[id++] = ans;
            }
        // ans[0], ans[1] 为两个子树的直径
        fans = max(fans, fa[0] * fa[1]);
        // cout << non << " " << fa[0] << " " << fa[1] << endl;
    }
    cout << fans << endl;
    return 0;
}