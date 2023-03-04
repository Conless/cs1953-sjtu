// Statement and information
/*
    Author: Conless
    Date: 2022-09-29
    File name: /oi/acmoj/1707.cpp
*/

// Headers
#include <bits/stdc++.h>

// Constants, global variables and definitions
int n, m, tot, ans;
int data[25], vis[25], f[2005];

// Templates and namespaces
using std::max;

// Classes


// Funtions
void dfs(int now, int cnt, int sum)
{
    if (n - now < m - cnt)
        return;
    vis[now] = 1;
    sum += data[now];
    if (cnt == m)
    {
        f[0] = 1;
        int tot_new = 0, cnt_new = 0;
        for (int i = 1; i <= n; i++)
        {
            if (vis[i])
                continue;
            for (int j = tot_new; j >= 0; j--)
                if (f[j])
                    f[j + data[i]] = 1;
            tot_new += data[i];
        }
        for (int j = 1; j <= tot - sum; j++)
            if (f[j])
            {
                cnt_new++;
                f[j] = 0;
            }
        ans = max(ans, cnt_new);
    }
    else {
        for (int i = now + 1; i <= n; i++)
            dfs(i, cnt + 1, sum);
    }
    vis[now] = 0;
    sum -= data[now];
    return;
}

// Main function
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &data[i]);
        tot += data[i];
    }
    dfs(0, 0, 0);
    printf("%d\n", ans);
    return 0;
}