// Statement and information
// Author: Conless
// Date: 2022-11-11
// File name: /course/22fall/sjtu/cs1953/test/2/1741_1.cpp

#include <bits/stdc++.h>

using namespace std;

int k, possx, possy;
int t[20];

void pre() {
    t[0] = 1;
    for (int i = 1; i <= k; i++)
        t[i] = t[i - 1] << 1;
}

void fill(int x, int y, int pos_x, int pos_y, int kk) {
    int len = t[kk];
    if (len == 1)
        return;
    if ((pos_x - x) < len / 2 && (pos_y - y) < len / 2) {
        cout << x + len / 2 << " " << len / 2 + y << " " << 1 << '\n';
        fill(x, y, pos_x, pos_y, kk - 1);
        fill(x, y + len / 2, x + len / 2 - 1, y + len / 2, kk - 1);
        fill(x + len / 2, y, x + len / 2, y + len / 2 - 1, kk - 1);
        fill(x + len / 2, y + len / 2, x + len / 2, y + len / 2, kk - 1);
    }
    else if ((pos_x - x) < len / 2 && (pos_y - y) >= len / 2) {
        cout << len / 2 + x << " " << len / 2 + y - 1 << " " << 2 << '\n';
        fill(x, y, x + len / 2 - 1, y + len / 2 - 1, kk - 1);
        fill(x, y + len / 2, pos_x, pos_y, kk - 1);
        fill(x + len / 2, y, x + len / 2, y + len / 2 - 1, kk - 1);
        fill(x + len / 2, y + len / 2, x + len / 2, y + len / 2, kk - 1);
    }
    else if ((pos_x - x) >= len / 2 && (pos_y - y) < len / 2) {
        cout << x + len / 2 - 1 << " " << y + len / 2 << " " << 3 << '\n';
        fill(x, y, x + len / 2 - 1, y + len / 2 - 1, kk - 1);
        fill(x, y + len / 2, x + len / 2 - 1, y + len / 2, kk - 1);
        fill(x + len / 2, y, pos_x, pos_y, kk - 1);
        fill(x + len / 2, y + len / 2, x + len / 2, y + len / 2, kk - 1);
    }
    else if ((pos_x - x) >= len / 2 && (pos_y - y) >= len / 2) {
        cout << x + len / 2 - 1 << " " << y + len / 2 - 1 << " " << 4 << '\n';
        fill(x, y, x + len / 2 - 1, y + len / 2 - 1, kk - 1);
        fill(x, y + len / 2, x + len / 2 - 1, y + len / 2, kk - 1);
        fill(x + len / 2, y, x + len / 2, y + len / 2 - 1, kk - 1);
        fill(x + len / 2, y + len / 2, pos_x, pos_y, kk - 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> k >> possx >> possy;
    pre();
    fill(1, 1, possx, possy, k);
    return 0;
}