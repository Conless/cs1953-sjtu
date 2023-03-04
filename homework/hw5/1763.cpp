#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2e6 + 5;

struct Edge {
    int v, next;
} edge[MAXN];

int n, m, q, cnt, tim, tot;
int head[MAXN], low[MAXN], dfn[MAXN], ins[MAXN], col[MAXN];
stack<int> st;
vector<int> g[MAXN];

void add_edge(int u, int v) {
    cnt++;
    edge[cnt].v = v;
    edge[cnt].next = head[u];
    head[u] = cnt;
    return;
}

void tarjan(int u) {
    dfn[u] = low[u] = ++tim;
    st.push(u);
    ins[u] = 1;
    for (int i = head[u]; i; i = edge[i].next) {
        int v = edge[i].v;
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (ins[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (low[u] == dfn[u]) {
        tot++;
        int tp;
        do {
            tp = st.top();
            ins[tp] = 0;
            col[tp] = tot;
            st.pop();
        } while (tp != u);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int x, y, t;
        cin >> x >> y >> t;
        add_edge(x << 1 | 1, (y << 1) | t);
        add_edge((y << 1) | (t ^ 1), x << 1);
        g[x].push_back((y << 1) | (t ^ 1));
    }
    int nex = n << 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < g[i].size(); j++) {
            q++;
            int fl = nex + (q << 1), tr = nex + (q << 1 | 1);
            add_edge(fl, g[i][j] ^ 1);
            add_edge(tr, g[i][j] ^ 1);
            if (j) {
                add_edge(tr - 2, tr);
                add_edge(fl, fl - 2);
                add_edge(g[i][j], fl - 2);
            }
            if (j + 1 != g[i].size())
                add_edge(g[i][j], tr + 2);
        }
    }
    for (int i = 2; i <= nex + (q << 1 | 1); i++) {
        if (!dfn[i])
            tarjan(i);
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        // cout << col[i << 1] << " " << col[i << 1 | 1] << endl;
        if (col[i << 1] == col[i << 1 | 1]) {
            printf("Impossible\n");
            return 0;
        } else {
            ans += col[i << 1] < col[i << 1 | 1];
        }
    }
    printf("%d\n", ans);
    for (int i = 1; i <= n; i++)
        if (col[i << 1] < col[i << 1 | 1])
            printf("%d ", i);
    printf("\n");
    return 0;
}