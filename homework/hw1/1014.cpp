// Statement and information
/*
    Author: Conless
    Date: 2022-09-28
    File name: /oi/acmoj/1014.cpp
*/

// Headers
#include <bits/stdc++.h>

// Constants, global variables and definitions
typedef long long ll;

const int MAXN = 1e5 + 5;
int n;
ll ans, data[MAXN];

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

using Template::qin;

// Classes


// Funtions

// Main function
int main()
{
    qin >> n;
    for (int i = 1; i <= n; i++)
        qin >> data[i];
    for (int i = 1; i <= n; i++)
    {
        ll num;
        qin >> num;
        data[i] = num - data[i];
        if (data[i] > 0)
        {
            if (data[i] > data[i - 1])
            {
                if (data[i - 1] < 0)
                    data[i - 1] = 0;
                ans += data[i] - data[i - 1];
            }
        }
        else {
            if (data[i] < data[i - 1])
            {
                if (data[i - 1] > 0)
                    data[i - 1] = 0;
                ans += data[i - 1] - data[i];
            }
        }
    }
    printf("%lld\n", ans);
    return 0;
}