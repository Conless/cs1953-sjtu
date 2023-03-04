// Statement and information
/*
    Author: Conless
    Date: 2022-09-28
    File name: /oi/acmoj/1686.cpp
*/

// Headers
#include <bits/stdc++.h>

// Constants, global variables and definitions
typedef long long ll;

const int MAXN = 1e6 + 5;
int n, m, l, r;
char str[MAXN];
int data[MAXN];
ll presum[MAXN], prepos[MAXN][2], sufpos[MAXN][2];

// Templates and namespaces
namespace Template
{
    class QuickRead
    {

    public:
        inline char gc()
        {
            static const int IN_LEN = 1 << 18 | 1;
            static char buf[IN_LEN], *s, *t;
            return (s == t) && (t = (s = buf) + fread(buf, 1, IN_LEN, stdin)), s == t ? -1 : *s++;
        }

        template <typename _Tp>
        inline QuickRead & operator >> (_Tp & num)
        {
            static char ch, sgn;
            ch = gc();
            sgn = 0;
            for(; !isdigit(ch); ch = gc())
            {
                if (ch == -1)
                    return *this;
                sgn |= (ch == '-');
            }
            num = 0;
            for (num = 0; isdigit(ch); ch = gc())
                num = num * 10 + (ch ^ '0');
            sgn && (num = -num);
            return *this;
        }
    } qin;
}

// Classes


// Funtions
inline ll Presum(int pos)
{
    if (pos < l)
        return presum[pos];
    if (pos > r)
        return presum[l - 1] + ((r - l + 1) - (presum[r] - presum[l - 1])) + presum[pos] - presum[r];
    return presum[l - 1] + ((pos - l + 1) - (presum[pos] - presum[l - 1]));
}
inline ll Prepos(int pos, int type)
{
    if (pos < l)
        return prepos[pos][type];
    if (pos > r)
        return prepos[l - 1][type] + (prepos[r][type ^ 1] - prepos[l - 1][type ^ 1]) + prepos[pos][type] - prepos[r][type];
    return prepos[l - 1][type] + prepos[pos][type ^ 1] - prepos[l - 1][type ^ 1];
}
inline ll Sufpos(int pos, int type)
{
    if (pos > r)
        return sufpos[pos][type];
    if (pos < l)
        return sufpos[r + 1][type] + (sufpos[l][type ^ 1] - sufpos[r + 1][type ^ 1]) + sufpos[pos][type] - sufpos[l][type];
    return sufpos[r + 1][type] + sufpos[pos][type ^ 1] - sufpos[r + 1][type ^ 1];
}
ll Solve()
{
    int start_pos = n - Presum(n),
        SufCount0 = (n - Presum(n)) - (start_pos - Presum(start_pos));
    ll LeftSumStep, OwnSumStep, RightSumStep;
    if (!data[start_pos])
    {
        LeftSumStep     =   Presum(start_pos) * start_pos * 2 - (Prepos(start_pos - 1, 1) * 2 + Presum(start_pos)) + start_pos - 1,
        OwnSumStep      =   Presum(start_pos) * 2 + 1,
        RightSumStep    =   (Sufpos(start_pos + 1, 0) * 2 - SufCount0) - SufCount0 * start_pos * 2;
    }
    else {
        LeftSumStep     =   Presum(start_pos - 1) * start_pos * 2 - (Prepos(start_pos - 1, 1) * 2 + Presum(start_pos - 1)) + start_pos - 1,
        OwnSumStep      =   SufCount0 * 2,
        RightSumStep    =   (Sufpos(start_pos + 1, 0) * 2 - SufCount0) - SufCount0 * start_pos * 2;
    }
    return LeftSumStep + OwnSumStep + RightSumStep;
}

// Main function
int main()
{
    scanf("%d%d", &n, &m);
    scanf("%s", str + 1);
    for (int i = 1; i <= n; i++)
    {
        data[i] = str[i] - '0';
        presum[i] = presum[i - 1] + data[i];
        prepos[i][0] = prepos[i - 1][0];
        prepos[i][1] = prepos[i - 1][1]; 
        prepos[i][data[i]] += i;
    }
    for (int i = n; i >= 1; i--)
    {
        sufpos[i][0] = sufpos[i + 1][0];
        sufpos[i][1] = sufpos[i + 1][1]; 
        sufpos[i][data[i]] += i;
    }
    l = n + 1; r = 0;
    printf("%lld\n", Solve());
    while (m--)
    {
        Template::qin >> l >> r;
        printf("%lld\n", Solve());
    }
}