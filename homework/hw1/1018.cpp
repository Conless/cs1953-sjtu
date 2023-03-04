// Statement and information
/*
    Author: Conless
    Date: 2022-10-05
    File name: /oi/acmoj/1018.cpp
*/

// Headers
#include <bits/stdc++.h>

// Constants, global variables and definitions
typedef long long ll;

const int MAXN = 1005;

int n, m, k;
int revpr_org;
int num[MAXN], vis[MAXN];
int empos[MAXN], emnum[MAXN];
int presum[MAXN][MAXN], sufsum[MAXN][MAXN];
ll ans;

// Templates and namespaces
namespace Template
{
    class BinaryIndexedTree1
    {
    /* 
        Template name: The template of binary indexed tree, single edit and range query
        Author: Conless
        Date: 2017-11-15
        File name: /oi/template/bitree.hpp
        Required constants: MAXN (the size of the tree)
    */

        int size;
        int data[MAXN << 1];

        // Get the lowbit of the number
        inline int lowbit(int x) { return x & (-x); }

        
        /*
            Here, from the principle of the binary indexed tree, we can find the father of a node,
                                        1000
                                    /   / |
                            0100       /  |
                        /    |        /   |
                    0010       |      0110  |
                /            |      /     |
            0001              0011  0101   0111
        */

    public:
        // The construction function of the tree, where size should be given.
        BinaryIndexedTree1(int SizeOfTheTree = 0)                                
        {
            size = SizeOfTheTree;
            memset(data, 0, sizeof(data));
        }

        // Reconstruction fuction for the tree, mainly used when the tree would be better as a global variable, whose size would be determined later.
        void RebuildTree(int NewSize)
        {
            size = NewSize;
            memset(data, 0, sizeof(data));
        }

        // Add number at a single point of the tree.
        void AddNum(int Position, int Num)
        {
            while (Position <= size)
            {
                data[Position] += Num;
                Position += lowbit(Position);
            }
        }

        // Ask the query sum from 1 to the given position
        int AskSum(int Position)
        {
            int ans = 0;
            while (Position > 0)
            {
                ans += data[Position];
                Position -= lowbit(Position);
            }
            return ans;
        }
    };
}

using std::min;
using Template::BinaryIndexedTree1;
// Classes


// Funtions
int sel[MAXN], sel1[MAXN], sel2[MAXN], vis1[MAXN], vis2[MAXN];
int revpr_new;
ll cntfir[MAXN * 14];

BinaryIndexedTree1 presum_sel;

void dfs1(int now, int sum)
{
    if (now == m / 2)
    {
        cntfir[sum]++;
        return;
    }
    for (int i = 1; i <= m / 2; i++)
        if (!vis1[i])
        {
            vis1[i] = 1;
            int addval = presum_sel.AskSum(n) - presum_sel.AskSum(sel1[i]) + presum[empos[now]][sel1[i]] + sufsum[empos[now]][sel1[i]];
            presum_sel.AddNum(sel1[i], 1);
            dfs1(now + 1, sum + addval);
            presum_sel.AddNum(sel1[i], -1);
            vis1[i] = 0;
        }
}
void dfs2(int now, int sum)
{
    if (now == m)
    {
        int res = k - revpr_org - revpr_new - sum;
        if (res >= 0 && res <= n * 14)
            ans += cntfir[res];
        return;
    }
    for (int i = 1; i <= m - m / 2; i++)
        if (!vis2[i])
        {
            vis2[i] = 1;
            int addval = presum_sel.AskSum(n) - presum_sel.AskSum(sel2[i]) + presum[empos[now]][sel2[i]] + sufsum[empos[now]][sel2[i]];
            presum_sel.AddNum(sel2[i], 1);
            dfs2(now + 1, sum + addval);
            presum_sel.AddNum(sel2[i], -1);
            vis2[i] = 0;
        }
        
}
void dfs(int cnt, int las)
{
    if (cnt == m / 2)
    {
        revpr_new = 0LL;
        for (int i = 1, j = 0, k = 0; i <= m; i++)
            if (sel[i])
                sel1[++j] = emnum[i];
            else {
                revpr_new += 1LL * (m / 2 - j);
                sel2[++k] = emnum[i];
            }
        memset(cntfir, 0, sizeof(cntfir));
        dfs1(0, 0);
        dfs2(m / 2, 0);
        return;
    }
    int maxselect = min(m, m + cnt + 1 - m / 2);
    for (int i = las + 1; i <= maxselect; i++)
    {
        sel[i] = 1;
        dfs(cnt + 1, i);
        sel[i] = 0;
    }
}


// Main function
int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
            presum[i][j] = presum[i - 1][j];
        scanf("%d", &num[i]);
        if (num[i] == 0)
            empos[m++] = i;
        else {
            vis[num[i]] = 1;
            revpr_org += presum[i][num[i]];
            for (int j = 1; j <= num[i]; j++)
                presum[i][j]++;
        }
    }
    for (int i = n; i >= 1; i--)
    {
        for (int j = 1; j <= n; j++)
            sufsum[i][j] = sufsum[i + 1][j];
        if (num[i])
        {
            for (int j = num[i]; j <= n; j++)
                sufsum[i][j]++;
        }
    }
    for (int i = 1, j = 0; i <= n; i++)
        if (!vis[i])
            emnum[++j] = i;
    presum_sel.RebuildTree(n);
    dfs(0, 0);
    printf("%lld\n", ans);
    return 0;
}