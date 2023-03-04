// Statement and information
/*
    Author: Conless
    Date: 2022-09-27
    File name: /oi/acmoj/1685.cpp
*/

// Headers
#include <bits/stdc++.h>

// Constants, global variables and definitions
const int MAXN = 5e5 + 5;
int num[MAXN], ans[MAXN], lastminus[MAXN];

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

using Template::BinaryIndexedTree1;
using Template::qin;
using std::unordered_map;
using std::pair;
using std::sort;

BinaryIndexedTree1 bitree;
unordered_map<int, pair<int, int> > ma;

// Classes
struct Query {
    int l, r, num;
    bool operator < (const Query& x)
        { return r < x.r; }
} que[MAXN];

// Funtions


// Main function
int main()
{
    int n, q;
    qin >> n >> q;
    bitree.RebuildTree(n);
    for (int i = 1; i <= n; i++)
    {
        qin >> num[i];
        ma[num[i]] = std::make_pair(0, 0);
    }
    for (int i = 1; i <= q; i++)
    {
        que[i].num = i;
        qin >> que[i].l >> que[i].r;
    }
    sort(que + 1, que + q + 1);
    int lasr = 0;
    for (int i = 1; i <= q; i++)
    {
        while (lasr < que[i].r)
        {
            lasr++;
            pair<int, int> nowmatch = ma[num[lasr]];
            if (nowmatch.second == 0)
                nowmatch.second = lasr;
            else if (nowmatch.first == 0)
            {
                nowmatch.first = nowmatch.second;
                nowmatch.second = lasr;
                bitree.AddNum(nowmatch.first, 1);
            } else {
                int lstminus = lastminus[nowmatch.first];
                if (lstminus)
                    bitree.AddNum(lstminus, 1);
                bitree.AddNum(nowmatch.first, -2);
                bitree.AddNum(nowmatch.second, 1);
                lastminus[nowmatch.second] = nowmatch.first;
                nowmatch.first = nowmatch.second;
                nowmatch.second = lasr;
            }
            ma[num[lasr]] = nowmatch;
            // for (int i = 1; i <= 20; i++)
            //     printf("%d ", bitree.AskSum(i) - bitree.AskSum(i - 1));
            // printf("\n");
        }
        ans[que[i].num] = bitree.AskSum(que[i].r) - bitree.AskSum(que[i].l - 1);
    }
    for (int i = 1; i <= q; i++)
        printf("%d\n", ans[i]);
    return 0;
}
