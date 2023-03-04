// Statement and information
// Author: Conless
// Date: 2022-10-18
// File name: /course/22fall/sjtu/cs1953/homework/hw2/1717.cpp

// Headers
#include <bits/stdc++.h>

// Constants, global variables and definitions

const int MAXN = 1e6 + 5;

std::unordered_map<long long, long long> cnt;

int n, m;
long long ans, xorsum, oddcnt, maxans, minans;
long long data[MAXN], suf[MAXN];

// Templates and namespaces

class QuickRead {

  public:
    inline char gc() {
        static const int IN_LEN = 1 << 18 | 1;
        static char buf[IN_LEN], *s, *t;
        return (s == t) && (t = (s = buf) + fread(buf, 1, IN_LEN, stdin)),
               s == t ? -1 : *s++;
    }

    template <typename _Tp> inline QuickRead &operator>>(_Tp &num) {
        static char ch, sgn;
        ch = gc();
        sgn = 0;
        for (; !isdigit(ch); ch = gc()) {
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

// Classes

// Funtions
void calc() {
    xorsum ^= ans;
    oddcnt += ans % 2;
    maxans = std::max(maxans, ans);
    minans = std::min(minans, ans);
}

// Main function
int main() {
    qin >> n >> m;
    for (int i = 1; i <= n; i++)
        qin >> data[i];
    for (int i = n; i >= 1; i--) {
        suf[i] = suf[i + 1] ^ data[i];
        ans += cnt[suf[i]];
        cnt[suf[i]]++;
    }
    minans = ans;
    for (int i = 1; i <= m; i++) {
        int p, x;
        qin >> p >> x;
        cnt[suf[p + 1]]--;
        ans -= cnt[suf[p + 1]];
        suf[p + 1] ^= x;
        ans += cnt[suf[p + 1]];
        cnt[suf[p + 1]]++;
        calc();
    }
    printf("%lld\n%lld\n%lld\n%lld\n", xorsum, oddcnt, maxans, minans);
    return 0;
}