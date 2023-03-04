#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2e6 + 5;

struct Edge {
    int v, next;
} edge[MAXN];

int n, m, cnt, tim, tot;
int head[MAXN], low[MAXN], dfn[MAXN], ins[MAXN], col[MAXN], ivt[MAXN];
stack<int> st;

void add_edge(int u, int v) {
    cnt++;
    edge[cnt].v = v;
    edge[cnt].next = head[u];
    head[u] = cnt;
    return;
}

bool tarjan(int u, int las) {
    dfn[u] = low[u] = ++tim;
    st.push(u);
    ins[u] = 1;
    bool ret = 0;
    for (int i = head[u]; i; i = edge[i].next) {
        int v = edge[i].v;
        if (v == las)
            continue;
        if (!dfn[v]) {
            col[v] = col[u] ^ 1;
            bool res = tarjan(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] >= dfn[u]) {
                int tp;
                do {
                    tp = st.top();
                    st.pop();
                    ins[tp] = 0;
                    if (res)
                        ivt[tp] = 1;
                } while (tp != v);
                if (res)
                    ivt[u] = 1;
            } else {
                ret |= res;
            }
        } else {
            low[u] = min(low[u], dfn[v]);
            if (col[u] == col[v])
                ret = 1;
        }
    }
    // printf("%d %d %d %d\n", u, dfn[u], low[u], ret);
    if (low[u] == dfn[u])
        return 0;
    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        add_edge(u, v);
        add_edge(v, u);
    }
    for (int i = 1; i <= n; i++) {
        if (!dfn[i])
            tarjan(i, 0);
    }
    int ans = n;
    for (int i = 1; i <= n; i++)
        if (ivt[i])
            ans--;
    cout << ans << endl;
    return 0;
}