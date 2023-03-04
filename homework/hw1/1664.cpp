// Statement and information
/*
    Author: Conless
    Date: 2022-09-27
    File name: /oi/acmoj/1664.cpp
*/

// Headers
#include <bits/stdc++.h>

// Constants, global variables and definitions
int k, n, m;
int vis[25], x[105];

// Templates and namespaces
namespace PosSuffix 
{
    int next_pos[105][25];
    void GetSuffix()
    {
        for (int j = 1; j <= m; j++)
            next_pos[n][j] = n + 1;
        next_pos[n][x[n]] = n;
        for (int i = n - 1; i >= 1; i--)
        {
            int maxpos = i, maxnum = -1;
            for (int j = 1; j <= m; j++)
            {
                if (x[i] == j)
                    next_pos[i][j] = i;
                else next_pos[i][j] = next_pos[i + 1][j];
            }
        }
    }
    int GetNum(int now_pos)
    {
        int max_pos = 0, max_num = -1;
        for (int j = 1; j <= m; j++)
            if (vis[j])
            {
                if (next_pos[now_pos][j] >= max_pos)
                {
                    max_pos = next_pos[now_pos][j];
                    max_num = j;
                }
            }
        return max_num;
    }
}

// Classes


// Funtions


// Main function
int main()
{
    scanf("%d%d", &k, &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &x[i]);
        m = std::max(m, x[i]);
    }
    PosSuffix::GetSuffix();
    int used = 0, ans = 0;
    for (int i = 1; i <= n; i++)
    {
        if (vis[x[i]])
            continue;
        if (used < k)
        {
            vis[x[i]] = 1;
            used++;
            continue;
        }
        vis[PosSuffix::GetNum(i)] = 0;
        vis[x[i]] = 1;
        ans++;
    }
    printf("%d\n", ans);
    return 0;
}