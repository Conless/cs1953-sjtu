#include <bits/stdc++.h>

using namespace std;

int n, m, q;
int vis[100005];
vector<pair<int, int> > edge[100005];
queue<int> qq, qqq;

bool check(int x, int y, int z, int dis) {
	while (!qq.empty())
		qq.pop();
	while (!qqq.empty())
		qqq.pop();
	qq.push(x);
	qq.push(y);
	qqq.push(x);
	qqq.push(y);
	vis[x] = vis[y] = 1;
	bool fl = 0;
	while (!qq.empty()) {
		if (qqq.size() >= z) {
			fl = 1;
			break;
		}
		int u = qq.front();
		qq.pop();
		int llen = edge[u].size();
		for (int i = 0; i < llen; i++) {
			if (edge[u][i].first > dis)
				break;
			int v = edge[u][i].second;
			if (!vis[v]) {
				qq.push(v);
				vis[v] = 1;
				qqq.push(v);
			}
		}
	}
	while (!qqq.empty()) {
		int u = qqq.front();
		vis[u] = 0;
		qqq.pop();
	}
	return fl;
}

int main() {
    freopen("1740.in", "r", stdin);
    freopen("1740.ans", "w", stdout);
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		edge[x].push_back(make_pair(i, y));
		edge[y].push_back(make_pair(i, x));
	}
	scanf("%d", &q);
	while (q--) {
		int x, y, z;
		scanf("%d%d%d", &x, &y, &z);
		int l = 1, r = m, ans = m + 1;
		while (l <= r) {
			int mid = (l + r) >> 1;
			if (check(x, y, z, mid)) {
				ans = mid;
				r = mid - 1;
			} else l = mid + 1;
		}
		printf("%d\n", ans);
	}
	return 0;
}