// Statement and information
// Author: Conless
// Date: 2022-10-18
// File name: /course/22fall/sjtu/cs1953/homework/hw2/1702.cpp

// Headers
#include <bits/stdc++.h>

// Constants, global variables and definitions
const int MAXN = 1e6 + 5;

struct Ask {
    int l, r, pos, id;
    inline bool operator<(const Ask &x) const {
        if (pos != x.pos)
            return pos < x.pos;
        return pos & 1 ? r < x.r : x.r < r;
    }
} ask[MAXN];

int n, m;
int siz, maxcnt;
int data[MAXN], cnt[MAXN], tim[MAXN];
int ans[MAXN];

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
void add(int num) {
    --tim[cnt[num]];
    ++tim[++cnt[num]];
    while (tim[maxcnt + 1])
        maxcnt++;
}
void del(int num) {
    --tim[cnt[num]];
    ++tim[--cnt[num]];
    while (!tim[maxcnt])
        maxcnt--;
}

// Main function
int main() {
    qin >> n >> m;
    int siz = sqrt(n);
    for (int i = 1; i <= n; i++)
        qin >> data[i];
    for (int i = 1; i <= m; i++) {
        qin >> ask[i].l >> ask[i].r;
        ask[i].pos = ask[i].l / siz;
        ask[i].id = i;
    }
    std::sort(ask + 1, ask + m + 1);
    int l = 1, r = 0;
    for (int i = 1; i <= m; i++) {
        while (r < ask[i].r)
            add(data[++r]);
        while (l > ask[i].l)
            add(data[--l]);
        while (r > ask[i].r)
            del(data[r--]);
        while (l < ask[i].l)
            del(data[l++]);
        ans[ask[i].id] = std::max(1, 2 * maxcnt - (r - l + 1));
    }
    for (int i = 1; i <= m; i++)
        printf("%d\n", ans[i]);
    return 0;
}