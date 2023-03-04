// Statement and information
/*
    Author: Conless
    Date: 2022-10-04
    File name: /oi/acmoj/1706.cpp
*/

// Headers
#include <bits/stdc++.h>
#include <cstring>

// Constants, global variables and definitions
typedef long long ll;

const int MAXN = 1e5 + 5;
const ll MAXTIME = 1e9 + 7;

int n, m, cnt;
int start, target;
ll suptime, accspeed;
ll max_time[MAXN], dis[MAXN], vis[MAXN], head[MAXN];
std::queue<int> q;

// Templates and namespaces
namespace Template {
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
} // namespace Template

using Template::qin;

// Classes
struct Edge {
    int v, w, next;
} edge[MAXN * 10];

// Funtions
void add_edge(int u, int v, int w) {
    cnt++;
    edge[cnt].v = v;
    edge[cnt].w = w;
    edge[cnt].next = head[u];
    head[u] = cnt;
}
void SPFA() {
    memset(dis, 0x7f, sizeof(dis));
    if (max_time[start] >= 0) {
        q.push(start);
        dis[start] = 0;
        vis[start] = 1;
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        vis[u] = 0;
        for (int i = head[u]; i != 0; i = edge[i].next) {
            int v = edge[i].v;
            ll next_dis = dis[u] + edge[i].w;
            if (next_dis < dis[v] && (v == target || next_dis <= max_time[v])) {
                dis[v] = next_dis;
                if (!vis[v]) {
                    q.push(v);
                    vis[v] = 1;
                }
            }
        }
    }
}

// Main function
int main() {
    qin >> n >> m >> start >> target >> suptime >> accspeed;
    for (int i = 1; i <= n; i++) {
        int height, limit;
        qin >> height >> limit;
        max_time[i] = (limit - height) / accspeed;
    }
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        qin >> u >> v >> w;
        add_edge(u, v, w);
        add_edge(v, u, w);
    }
    SPFA();
    if (dis[target] > suptime)
        printf("sad\n");
    else
        printf("%lld\n", dis[target]);
    return 0;
}