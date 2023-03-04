// Statement and information
// Author: Conless
// Date: 2022-10-24
// File name: /course/22fall/sjtu/cs1953/homework/hw3/1726.cpp

// Headers
#include <bits/stdc++.h>

const int MAXN = 1e3 + 5;

int n, ans;
int c[MAXN];
std::queue<int> q;

// Funtions

// Main function
int main() {
    scanf("%d", &n);
    ans = n * n * n;
    for (int i = 0; i < n; i++)
        scanf("%d", &c[i]);
    for (int i = 0; i < n; i++) {
        while (!q.empty())
            q.pop();
        int sum = 0, fai = 0;
        for (int j = 0; j < n; j++) {
            int pos = (i + j) % n;
            if (c[pos]) {
                for (int k = 2; k <= c[pos]; k++)
                    q.push(pos);
                if (!q.empty()) {
                    q.push(pos);
                    sum += pow((pos - q.front() + n) % n, 2);
                    q.pop();
                }
            } else {
                if (q.empty()) {
                    fai = 1;
                    break;
                }
                sum += pow((pos - q.front() + n) % n, 2);
                q.pop();
            }
        }
        if (!fai)
            ans = std::min(ans, sum);
    }
    printf("%d\n", ans);
    return 0;
}