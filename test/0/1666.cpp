// Statement and information
/*
    Author: Conless
    Date: 2022-09-28
    File name: /oi/acmoj/1666.cpp
*/

// Headers
#include <bits/stdc++.h>
#include <cstdlib>

// Constants, global variables and definitions
const int MAXN = 1e5 + 5;

// Templates and namespaces
using namespace std;

// Classes
struct Edge {
    int v, next;
    int u, num, lab;
} edge[MAXN << 1];
int n, m, cnt;
int head[MAXN], vis[MAXN << 1];
int firu[MAXN], firv[MAXN], finans[MAXN];

// Funtions
void add_edge(int u, int v, int lab)
{
    cnt++;
    edge[cnt].v = v;
    edge[cnt].next = head[u];
    head[u] = cnt;
    edge[cnt].u = u;
    edge[cnt].lab = lab;
}
int dfs(int node, int fromedge, int want)
{
    if (node == want)
        return 1;
    if (vis[fromedge])
        return 0;
    vis[fromedge] = 1;
    int ans = 0;
    for (int i = head[node]; i; i = edge[i].next)
    {
        int v = edge[i].v;
        int res = dfs(v, i, want);
        ans += res;
        edge[i].num += res;
    }
    return ans;
}

// Main function
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        add_edge(a, b, i);
        add_edge(b, a, i);
        firu[i] = a; firv[i] = b;
    }
    int p;
    scanf("%d", &p);
    while (p--)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        vis[0] = 0;
        int ans = dfs(a, 0, b);
        for (int i = 1; i <= cnt; i++)
        {
            if (edge[i].num == ans)
                finans[edge[i].lab] = (firu[edge[i].lab] == edge[i].u ? 1 : 2);
            edge[i].num = 0;
            vis[i] = 0;
        }
    }
    for (int i = 1; i <= m; i++)
    {
        cout << "B";
    }
}