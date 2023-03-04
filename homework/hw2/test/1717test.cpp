#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef vector<int> vi;
typedef pair<int, int> pii;
#define IOS ios::sync_with_stdio(0)
#define For(i,a,b) for (int i=(a),_b=(b);i<=_b;i++)
#define FOr For
#define Iter(i,a,b) for (int i=(a),_b=(b);i<_b;i++)
#define Downto(i,a,b) for (int i=(a),_b=(b);i>=_b;i--)
#define set0(a) memset(a,0,sizeof(a))
#define set0n(a,n) memset(a,0,sizeof((a)[0])*(n+1))
#define pb push_back
#define mkp make_pair
#define all(a) (a).begin(),(a).end()
template <class T1, class T2>
inline void getmin(T1 &x, const T2 &y) {if (y < x) x = y;}
template <class T1, class T2>
inline void getmax(T1 &x, const T2 &y) {if (x < y) x = y;}
//char NY[2][10]={"NO\n","YES\n"};//capital?

#ifndef DEBUG
#define FIO
#endif
//#define FIO
#ifdef FIO

namespace IO {
    const int sz = 1 << 21;
    char ib[sz], *s = ib, *t = ib;
#define getchar getc
    inline int getc() {
        return s == t && (t = (s = ib) + fread(ib, 1, sz, stdin), s == t) ? EOF : *s++;
    }

    char ob[sz + 99];
    int p = 0;
    inline void flush() {
        fwrite(ob, 1, p, stdout), p = 0;
    }
    struct F {
        ~F() {
            flush();
        }
    } f; //Don't call fclose
#define putchar putc
    inline void putc(int c) {
        ob[p++] = c;
        if (p >= sz) { flush(); }
    }
}
using IO::getc;

#endif

//can't input/output -1<<31 or -1LL<<63
template <class T>
inline void read(T &x) {
    x = 0;
    bool f = 0;
    char c;
    while (!isdigit(c = getchar())) if (c == '-') { f = 1; }
    for (; isdigit(c); x = c - '0' + x * 10, c = getchar());
    if (f) { x = -x; }
}

const int N = 1e6 + 5;
int a[N], s[N];
unordered_map<int, int> c;
ll ans;
inline void del(int x) {ans -= --c[x];}
inline void add(int x) {ans += c[x]++;}

signed main() {
    freopen("1717.in", "r", stdin);
    int n, m;
    read(n), read(m);
    For(i, 1, n) read(a[i]);
    s[n + 1] = 0, c[0] = 1;
    Downto(i, n, 1) s[i] = s[i + 1] ^ a[i], add(s[i]);
    int sum = 0, odd = 0, mx = 0, mn = (1ll << 31) - 1;
    For(i, 1, m) {
        int p, x;
        read(p), read(x);
        del(s[p + 1]), s[p + 1] ^= x, add(s[p + 1]);
        sum ^= ans, odd += ans % 2, getmax(mx, ans), getmin(mn, ans);
    }
    printf("%d\n%d\n%d\n%d\n", sum, odd, mx, mn);

    return cout << flush, 0;
}