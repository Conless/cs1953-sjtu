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
int n, m;
char str[MAXN];
int data[MAXN];

// Templates and namespaces
namespace Template
{
    class SegmentTree
    {
        struct Node {
            int l, r;
            ll sum, mulv, addv;
        } s[MAXN << 1];

        void pushup(int k)
        {
            s[k].sum = s[k << 1].sum + s[(k << 1) | 1].sum;
        }
    public:    
        int fd[MAXN];
        void pushdown(int k)
        {
            int ls = k << 1, rs = (k << 1) | 1, mid = (s[k].l + s[k].r) / 2;	
            s[ls].sum = s[ls].sum * s[k].mulv;
            s[rs].sum = s[rs].sum * s[k].mulv;
            s[ls].sum = (s[ls].sum + s[k].addv * (mid - s[k].l + 1)); 
            s[rs].sum = (s[rs].sum + s[k].addv * (s[k].r - mid));

            s[ls].mulv = s[ls].mulv * s[k].mulv;
            s[rs].mulv = s[rs].mulv * s[k].mulv;
            s[ls].addv = s[ls].addv * s[k].mulv;
            s[rs].addv = s[rs].addv * s[k].mulv;
            s[ls].addv = (s[ls].addv + s[k].addv);
            s[rs].addv = (s[rs].addv + s[k].addv);

            s[k].addv = 0;
            s[k].mulv = 1;
        }
        
        void init(int l, int r, int k)
        {
            s[k].l = l, s[k].r = r, s[k].addv = 0, s[k].mulv = 1;
            if (l == r)
            {
                s[k].sum = fd[l];
                return;
            }
            int mid = (l + r) / 2;
            init(l, mid, k << 1);
            init(mid + 1, r, (k << 1) | 1);
            pushup(k);
        }
        
        void upplus(int l, int r, int c, int k)
        {
            if (l <= s[k].l && s[k].r <= r)
            {
                s[k].addv = s[k].addv + c;
                s[k].sum = (s[k].sum + c * (s[k].r - s[k].l + 1));
                return;
            }
            pushdown(k);
        
            int mid = (s[k].l + s[k].r) >> 1;
            if (l <= mid) upplus(l, r, c, k << 1);
            if (r > mid) upplus(l, r, c, (k << 1) + 1);
            pushup(k);
        }

        void upmul(int l, int r, int c, int k)
        {
            if (l <= s[k].l && r >= s[k].r)
            {
                s[k].mulv = s[k].mulv * c;
                s[k].addv = s[k].addv * c;
                s[k].sum = s[k].sum * c;
                return;
            }
            pushdown(k);
            
            int mid = (s[k].l + s[k].r) >> 1;
            if (l <= mid) upmul(l, r, c, k << 1);
            if (r > mid) upmul(l, r, c, (k << 1) + 1);
            pushup(k);
        }
        
        long long query(int l, int r, int k)
        {
            if(l <= s[k].l && s[k].r <= r) 
                return s[k].sum;
            pushdown(k);
        
            int mid = (s[k].l + s[k].r) / 2;
            long long res = 0;
            if (l <= mid) res += query(l, r, k << 1);
            if (r > mid) res += query(l, r, (k << 1) + 1);
            return res;
        }
    };
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

Template::SegmentTree presum, prepos[2], sufpos[2];

// Classes


// Funtions
inline ll UpdatePresum(int l, int r)
{
    presum.upmul(l, r, -1, 1);
    if (pos < l)
        return presum.fd[pos];
    if (pos > r)
        return presum.fd[l - 1] + ((r - l + 1) - (presum.fd[r] - presum.fd[l - 1])) + presum.fd[pos] - presum.fd[r];
    return presum.fd[l - 1] + ((pos - l + 1) - (presum.fd[pos] - presum.fd[l - 1]));
}
inline ll prepos.fd(int pos, int type)
{
    if (pos < l)
        return prepos.fd[pos][type];
    if (pos > r)
        return prepos.fd[l - 1][type] + (prepos.fd[r][type ^ 1] - prepos.fd[l - 1][type ^ 1]) + prepos.fd[pos][type] - prepos.fd[r][type];
    return prepos.fd[l - 1][type] + prepos.fd[pos][type ^ 1] - prepos.fd[l - 1][type ^ 1];
}
inline ll sufpos.fd(int pos, int type)
{
    if (pos > r)
        return sufpos.fd[pos][type];
    if (pos < l)
        return sufpos.fd[r + 1][type] + (sufpos.fd[l][type ^ 1] - sufpos.fd[r + 1][type ^ 1]) + sufpos.fd[pos][type] - sufpos.fd[l][type];
    return sufpos.fd[r + 1][type] + sufpos.fd[pos][type ^ 1] - sufpos.fd[r + 1][type ^ 1];
}
ll Solve()
{
    int start_pos = n - presum.fd(n),
        SufCount0 = (n - presum.fd(n)) - (start_pos - presum.fd(start_pos));
    ll LeftSumStep, OwnSumStep, RightSumStep;
    if (!data[start_pos])
    {
        LeftSumStep     =   presum.fd(start_pos) * start_pos * 2 - (prepos.fd(start_pos - 1, 1) * 2 + presum.fd(start_pos)) + start_pos - 1,
        OwnSumStep      =   presum.fd(start_pos) * 2 + 1,
        RightSumStep    =   (sufpos.fd(start_pos + 1, 0) * 2 - SufCount0) - SufCount0 * start_pos * 2;
    }
    else {
        LeftSumStep     =   presum.fd(start_pos - 1) * start_pos * 2 - (prepos.fd(start_pos - 1, 1) * 2 + presum.fd(start_pos - 1)) + start_pos - 1,
        OwnSumStep      =   SufCount0 * 2,
        RightSumStep    =   (sufpos.fd(start_pos + 1, 0) * 2 - SufCount0) - SufCount0 * start_pos * 2;
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
        presum.fd[i] = presum.fd[i - 1] + data[i];
        prepos[0].fd[i] = prepos[0].fd[i - 1];
        prepos[1].fd[i] = prepos[1].fd[i - 1]; 
        prepos[data[i]].fd[i] += i;
    }
    for (int i = n; i >= 1; i--)
    {
        sufpos[0].fd[i] = sufpos[0].fd[i + 1];
        sufpos[1].fd[i] = sufpos[1].fd[i + 1]; 
        sufpos[data[i]].fd[i] += i;
    }
    presum.init(1, n, 1);
    prepos[0].init(1, n, 1);
    prepos[1].init(1, n, 1);
    sufpos[0].init(1, n, 1);
    sufpos[1].init(1, n, 1);
    printf("%lld\n", Solve());
    while (m--)
    {
        Template::qin >> l >> r;
        printf("%lld\n", Solve());
    }
}