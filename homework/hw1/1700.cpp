// Statement and information
/*
    Author: Conless
    Date: 2022-10-05
    File name: /oi/acmoj/1700.cpp
*/

// Headers
#include <bits/stdc++.h>

// Constants, global variables and definitions
const int MAXN = 2e3 + 5;
int n, m;
long long ans;

// Templates and namespaces
namespace UnionSet
{
    int fa[MAXN], vis[MAXN];
    void Reset()
    {
        for (int i = 1; i <= n; i++)
            fa[i] = i;
    }
    int FindFa(int num)
    {
        if (fa[num] != num)
            fa[num] = FindFa(fa[num]);
        return fa[num];
    }
}

// Classes
struct Edge {
    int u, v, w;
    bool operator < (const Edge & x) { return w < x.w; }
} edge[MAXN * MAXN];


// Funtions
void add_edge(int u, int v, int w)
{
    ++m;
    edge[m].u = u;
    edge[m].v = v;
    edge[m].w = w;
}
void Kruskal()
{
    std::sort(edge + 1, edge + m + 1);
    UnionSet::Reset();
    for (int i = 1; i <= m; i++)
    {
        int fu = UnionSet::FindFa(edge[i].u), 
            fv = UnionSet::FindFa(edge[i].v);
        if (fu != fv)
        {
            ans += edge[i].w;
            UnionSet::fa[fu] = fv;
        } 
    }
}

// Main function
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        for (int j = i; j <= n; j++)
        {
            int num;
            scanf("%d", &num);
            add_edge(i - 1, j, num);
        }
    Kruskal();
    printf("%lld\n", ans);
    return 0;
}