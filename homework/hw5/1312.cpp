#include <bits/stdc++.h>

using namespace std;

typedef double ll;

const double EPS = 1E-8;
const ll MOD = 1e9 + 7;

int n;
vector<vector<ll>> a[1005];
vector<int> rk, res;

// ll qpow(ll x, ll y) {
//     ll res = 1;
//     while (y) {
//         if (y & 1)
//             res = res * x % MOD;
//         x = x * x % MOD;
//         y >>= 1;
//     }
//     return res;
// }

int gauss(vector<vector<ll>> mat) {
    int rk = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++) {
            if (fabs(mat[i][j]) > 1e-8) {
                rk++;
                if (mat[i][j] < 0) {
                    for (int k = 0; k < n; k++)
                        mat[i][k] = -mat[i][k];
                }
                // ll inv = qpow(mat[i][j], MOD - 2);
                for (int k = 0; k < n; k++)
                    if (k != j)
                        mat[i][k] /= mat[i][j];
                mat[i][j] = 1.0;
                for (int k = i + 1; k < n; k++) {
                    for (int l = 0; l < n; l++)
                        if (l != j)
                            mat[k][l] = mat[k][l] - mat[i][l] * mat[k][j];
                    mat[k][j] = 0.0;
                }
                break;
            }
        }
    }
    return rk;
}

int main() {
    ios::sync_with_stdio(false);
    int T;
    cin >> T >> n;
    for (int i = 0; i < T; i++) {
        a[i].resize(n);
        for (int j = 0; j < n; j++)
        {
            a[i][j].resize(n);
            for (int k = 0; k < n; k++)
                cin >> a[i][j][k];
        }
        rk.push_back(gauss(a[i]));
        res.push_back(i);
        // cout << rk.back() << " ";
    }
    // cout << endl;
    int cnt = unique(res.begin(), res.end(), [](int a, int b) { return rk[a] == rk[b]; }) - res.begin();
    cout << cnt << endl;
    for (int i = 0; i < cnt; i++)
        cout << res[i] + 1 << " ";
    cout << endl;
    return 0;
}