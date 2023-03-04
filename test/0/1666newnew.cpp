// Statement and information
// Author: Conless
// Date: 2022-10-12
// File name: /oi/acmoj/1666newnew.cpp

// Headers
#include <iostream>
#include <cstdio>
#include <queue>
#include <stack>
#include <utility>

// Constants, global variables and definitions
const int MAXN = 1e5 + 5;

int n, m, p;
int edgecnt, head[MAXN];
int dfncnt;
int from[MAXN], low[MAXN], dfn[MAXN];

int scccnt, bel[MAXN], siz[MAXN];

// Templates and namespaces

// Classes
struct Edge {
    int u, v, next;
} edge[MAXN << 1];

// Funtions
void AddEdge(int u, int v) {
    edgecnt++;
    edge[edgecnt].u = u;
    edge[edgecnt].v = v;
    edge[edgecnt].next = head[u];
    head[u] = edgecnt;
}

std::stack<int> st;
int in_stack[MAXN];

void Tarjan(int now, int las_edge) {
    low[now] = dfn[now] = ++dfncnt;
    st.push(now);
    in_stack[now] = 1;
    for (int i = head[now]; i; i = edge[i].next) {
        int v = edge[i].v;
        if (((i + 1) / 2) == ((las_edge + 1) / 2))
            continue;
        if (!dfn[v]) {
            from[v] = i;
            Tarjan(v, i);
            low[now] = std::min(low[now], low[v]);
        } else {
            if (in_stack[v])
                low[now] = std::min(low[now], dfn[v]);
        }
    }
    if (dfn[now] == low[now]) {
        ++scccnt;
        while (st.top() != now) {
            int tp = st.top();
            bel[tp] = scccnt;
            siz[scccnt]++;
            in_stack[tp] = 0;
            st.pop();
        }
        bel[now] = scccnt;
        siz[scccnt]++;
        in_stack[now] = 0;
        st.pop();
    }
}

using std::pair;
using std::make_pair;
std::vector<pair<int, int> > nedge[MAXN];
int vis[MAXN], tag[MAXN], ans[MAXN];

void AddTag(int u, int v) {
    if (bel[u] != bel[v]) {
        ++tag[bel[u]];
        --tag[bel[v]];
    }
}

void dfs(int now) {
    for (pair<int, int> ed : nedge[now]) {
        int v = ed.first;
        if (vis[v])
            continue;
        vis[v] = 1;
        dfs(v);
        if (tag[v]) {
            if ((tag[v] > 0 && bel[edge[ed.second].v] != v) ||
                (tag[v] < 0 && bel[edge[ed.second].v] == v))
                ans[ed.second >> 1] = -1;
            else ans[ed.second >> 1] = 1;
        }
        tag[now] += tag[v];
    }
}

// Main function
int main() {
    // freopen("1666.in", "r", stdin);
    // freopen("1666.out", "w", stdout);
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        AddEdge(u, v);
        AddEdge(v, u);
    }
    for (int i = 1; i <= n; i++) {
        if (!dfn[i])
            Tarjan(i, 0);
    }
    // for (int i = 1; i <= n; i++)
    //     printf("%d ", dfn[i]);
    // printf("\n");
    // for (int i = 1; i <= n; i++)
    //     printf("%d ", low[i]);
    // printf("\n");
    // for (int i = 1; i <= n; i++)
    //     printf("%d ", bel[i]);
    // printf("\n");
    for (int i = 2; i <= edgecnt; i += 2) {
        int u = bel[edge[i].u], v = bel[edge[i].v];
        if (u == v)
            continue;
        nedge[u].push_back(make_pair(v, i));
        nedge[v].push_back(make_pair(u, i));
    }
    scanf("%d", &p);
    while (p--) {
        int u, v;
        scanf("%d%d", &u, &v);
        AddTag(u, v);
    }
    for (int i = 1; i <= scccnt; i++) {
        if (!vis[i]) {
            vis[i] = 1;
            dfs(i);
        }
    }
    // for (int i = 1; i <= scccnt; i++)
    //     printf("%d ", tag[i]);
    // printf("\n");
    for (int i = 1; i <= m; i++) {
        if (!ans[i]) {
            printf("B");
        } else {
            if (ans[i] == 1)
                printf("R");
            else printf("L");
        }
    }
    printf("\n");
    return 0;
}