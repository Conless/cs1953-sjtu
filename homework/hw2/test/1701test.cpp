//test2
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef pair<int, int> pii;
#define IOS ios::sync_with_stdio(0)
#define For(i,a,b) for (int i=(a),_b=(b);i<=_b;i++)
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

//#ifndef DEBUG
//#define FIO
//#endif
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
using IO::putc;

#endif

//can't input/output -1<<31 or -1LL<<63
template <class T>
inline void read(T &x) {
    bool f = x = 0;
    char c;
    while (!isdigit(c = getchar())) if (c == '-') { f = 1; }
    for (; isdigit(c); x = c - '0' + x * 10, c = getchar());
    if (f) { x = -x; }
}
template <class T, class ...Args>
inline void read(T &x, Args &...args) {
    read(x), read(args...);
}
template <class T>
void write(T x) {
    if (x < 0) { putchar('-'), x = -x; }
    if (x >= 10) { write(x / 10); }
    putchar(x % 10 + '0');
}
template <class T>
inline void write(T x, char c) {
    write(x), putchar(c);
}

constexpr int N = 3e5 + 10, SZ = N * 4;
constexpr ll P = 1e9 + 9;
#define mod(x) (x>=P?(x-=P):0)
#define add(x,y) (x+=(y),mod(x))
int s0[N];

#define lc o<<1
#define rc o<<1|1
//#define M ((L+R)>>1)
#define _o int o,int L,int R
#define _l lc,L,M
#define _r rc,M+1,R

ll f[N] = {0, 1}; //fibonacci
ll f1[SZ], f2[SZ]; //tags
ll sum[SZ];

inline void pushup(int o) {sum[o] = sum[lc] + sum[rc], mod(sum[o]);}
//must add tag if using permanent tag
inline void pushdown(_o) {
    if (f1[o] || f2[o]) {
        int M = (L + R) >> 1;
        ll a = f1[o], b = f2[o];
        add(f1[lc], a);
        add(f2[lc], b);
        add(sum[lc], (a * f[M + 1 - L] + b * (f[M + 2 - L] - 1 + P)) % P);

        a = (f1[o] * f[M - L] + f2[o] * f[M + 1 - L]) % P, b = (f1[o] * f[M + 1 - L] + f2[o] * f[M + 2 - L]) % P;
        add(f1[rc], a);
        add(f2[rc], b);
        add(sum[rc], (a * f[R - M] + b * (f[R + 1 - M] - 1 + P)) % P);

        f1[o] = f2[o] = 0;
    }
}

void modify(_o, int l, int r) {
    if (l <= L && R <= r) {
        add(f1[o], f[L - l + 1]);
        add(f2[o], f[L - l + 2]);
        (sum[o] += f[R - l + 3] - f[L - l + 2] + P) %= P;
        return;
    }
    int M = (L + R) >> 1;
    pushdown(o, L, R);
    if (l <= M) { modify(_l, l, r); }
    if (r > M) { modify(_r, l, r); }
    pushup(o);
}
ll query(_o, int l, int r) {
    if (l <= L && R <= r) {
        return sum[o];
    }
    int M = (L + R) >> 1;
    pushdown(o, L, R);
    int ret = ((l <= M) ? query(_l, l, r) : 0) + ((r > M) ? query(_r, l, r) : 0);
    mod(ret);
    return ret;
}

signed main() {
    freopen("1701.in", "r", stdin);
    int n, q;
    read(n, q);
    For(i, 2, n + 5) f[i] = f[i - 1] + f[i - 2], mod(f[i]);
    For(i, 1, n) read(s0[i]), add(s0[i], s0[i - 1]);

    For(i, 1, q) {
        int op, l, r;
        read(op, l, r);
        if (op == 1) {
            modify(1, 1, n, l, r);
        } else {
            write((query(1, 1, n, l, r) + s0[r] - s0[l - 1] + P) % P, '\n');
        }
        printf("\n");
        for (int j = 1; j <= n; j++)
            printf("%lld ", query(1, 1, n, j, j));
        printf("\n");
    }

    return cout << flush, 0;
}