// Statement and information
/*
    Author: Conless
    Date: 2022-09-27
    File name: /oi/acmoj/1665.cpp
*/

// Headers
#include <bits/stdc++.h>

// Constants, global variables and definitions
const int MAXN = 2e4 + 5;
int n, m, k, cnt;
int d[MAXN], f[MAXN];

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
    void Union(int num1, int num2)
    {
        int f1 = FindFa(num1), f2 = FindFa(num2);
        if (f1 != f2)
            fa[f1] = f2;
    }
    void CountSet()
    {
        for (int i = 1; i <= n; i++)
        {
            int fi = FindFa(i);
            if (!vis[fi])
            {
                cnt++;
                vis[fi] = cnt;
            }
            d[vis[fi]]++;
        }
    }
}

// Classes


// Funtions
void OutputResult()
{
    for (int i = 1; i <= cnt; i++)
        printf("%d ", d[i]);
    printf("\n");
}

// Main function
int main()
{
    scanf("%d%d%d", &n, &m, &k);
    UnionSet::Reset();
    for (int i = 1; i <= k; i++)
    {
        int num1, num2;
        scanf("%d%d", &num1, &num2);
        UnionSet::Union(num1, num2);
    }
    UnionSet::CountSet();
    f[0] = 1;
    for (int i = 1; i <= cnt; i++)
        for (int j = n - d[i]; j >= 0; j--)
        {
            if (!f[j])
                continue;
            f[j + d[i]] = 1;
        }
    for (int i = 0; i <= m; i++)
    {
        if (f[m - i])
        {
            printf("%d\n", m - i);
            break;
        }
        if (m + i <= n && f[m + i])
        {
            printf("%d\n", m + i);
            break;
        }
    }
    return 0;
}