#include <bits/stdc++.h>

using namespace std;

int n, m;
int a[7005], nex[7005][7005], las[7005][7005];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (a[i] == j)
            	las[i][j] = i;
            else {
				if (i == 1)
					las[i][j] = 0;
				else las[i][j] = las[i - 1][j];
			}
        }
    }
    for (int i = n; i >= 1; i--) {
        for (int j = 1; j <= n; j++) {
            if (a[i] == j)
            	nex[i][j] = i;
            else {
            	if (i == n)
            		nex[i][j] = n + 1;
            	else nex[i][j] = nex[i + 1][j];
			}
        }
    }
    while (m--) {
        int opt, x, y;
        scanf("%d%d%d", &opt, &x, &y);
        if (opt == 1) {
            int edtpos = x - 1;
            while (nex[edtpos][a[x]] == x && edtpos) {
                nex[edtpos][a[x]] = nex[x + 1][a[x]];
                edtpos--;
            }
            nex[x][a[x]] = nex[x + 1][a[x]];
            edtpos = x - 1;
            while (nex[edtpos][y] > x && edtpos <= n) {
                nex[edtpos][y] = x;
                edtpos--;
            }
            nex[x][y] = x;
            edtpos = x + 1;
            while (las[edtpos][a[x]] == x && edtpos) {
                las[edtpos][a[x]] = las[x - 1][a[x]];
                edtpos++;
            }
            las[x][a[x]] = las[x - 1][a[x]];
            edtpos = x + 1;
            while (las[edtpos][y] < x && edtpos <= n) {
                las[edtpos][y] = x;
                edtpos++;
            }
            las[x][y] = x;
            a[x] = y;
        }
        else {
            int ans = 0;
            for (int i = 1; i <= n; i++) {
                if (nex[x][i] <= y && las[y][i] >= x)
                    ans += las[y][i] - nex[x][i];
            }
            printf("%d\n", ans);
        }
    }
    return 0;
}