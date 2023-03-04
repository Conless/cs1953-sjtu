// Statement and information
// Author: Conless
// Date: 2022-10-14
// File name: /oi/acmoj/1716.cpp

// Headers
#include <bits/stdc++.h>

// Constants, global variables and definitions
const int MAXN = 1e5 + 5;

int n;
int maxnum, tail;
int data[MAXN], pos[MAXN];
int prev[MAXN], next[MAXN], vis[MAXN];

// Templates and namespaces

// Classes

// Funtions

// Main function
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &data[i]);
        pos[data[i]] = i;
        prev[i] = i - 1;
        next[prev[i]] = i;
    }
    tail = n;
    maxnum = n;
    while (tail) {
        while (maxnum == data[tail] || vis[maxnum])
            maxnum--;
        int pos1 = pos[maxnum], pos2 = next[pos1];
        printf("%d %d ", data[pos1], data[pos2]);
        vis[data[pos1]] = vis[data[pos2]] = 1;
        if (pos2 == tail)
            tail = prev[pos1];
        else {
            next[prev[pos1]] = next[pos2];
            prev[next[pos2]] = prev[pos1];
        }
    }
    printf("\n");
    return 0;
}