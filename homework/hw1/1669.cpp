// Statement and information
/*
    Author: Conless
    Date: 2022-09-27
    File name: /oi/acmoj/1669.cpp
*/

// Headers
#include <bits/stdc++.h>

// Constants, global variables and definitions
const int MAXN = 505;
int n, m;
int pos[MAXN];
int dp1[MAXN][MAXN], dp2[MAXN][MAXN];

// Templates and namespaces

using std::min;

namespace DP
{
    int dis[MAXN][MAXN], dis1[MAXN][MAXN], dis2[MAXN][MAXN];

    void GetDistance()
    {
        int suf[MAXN];
        suf[0] = suf[1] = 0;
        for (int i = 2; i <= n; i++)
            suf[i] = suf[i - 1] + pos[i];
        for (int i = 1; i <= n; i++)
            for (int j = i; j <= n; j++)
                dis1[i][j] = pos[j] * (j - i) - (suf[j - 1] - suf[i - 1]);
        for (int i = n; i >= 1; i--)
            for (int j = i; j >= 1; j--)
                dis2[i][j] = (suf[i] - suf[j]) - (i - j) * pos[j];
        memset(dis, 0x7f, sizeof(dis));
        for (int i = 1; i <= n; i++)
            for (int j = i; j <= n; j++)
                for (int k = i + 1; k <= j; k++)
                    dis[i][j] = min(dis[i][j], dis2[k - 1][i] + dis1[k][j]);
    }

    void Solve()
    {
        GetDistance();
        memset(dp1, 0x7f, sizeof(dp1));
        memset(dp2, 0x7f, sizeof(dp2));
        dp1[1][1] = 0;
        for (int i = 2; i <= n; i++)
        {
            dp2[1][i] = dis1[1][i];
            for (int j = 1; j <= m; j++)
            {
                if (j > n)
                    break;
                for (int k = 1; k < i; k++)
                {
                    dp2[j][k] = dp1[j][k];
                    dp2[j][i] = min(dp2[j][i], dp1[j - 1][k] + dis[k][i]);
                }
            }
            memcpy(dp1, dp2, sizeof(dp2));
            memset(dp2, 0x7f, sizeof(dp2));
        }
    }
}

// Classes


// Funtions


// Main function
int main()
{
    scanf("%d%d", &n, &m);
    pos[1] = 0;
    for (int i = 2; i <= n; i++)
    {
        int dist;
        scanf("%d", &dist);
        pos[i] = pos[i - 1] + dist;
    }
    DP::Solve();
    int ans = pos[n] * n;
    for (int i = m; i <= n; i++)
        ans = min(ans, dp1[m][i]+ DP::dis2[n][i]);
    printf("%d\n", ans);
    return 0;
}