// Statement and information
// Author: Conless
// Date: 2022-10-18
// File name: /course/22fall/sjtu/cs1953/homework/hw2/1687.cpp

// Headers
#include <bits/stdc++.h>

// Constants, global variables and definitions
const int MAXN = 2e5 + 5;

int n;
long long data[MAXN], presum[MAXN], ans[MAXN];

// Templates and namespaces
namespace Template {
class BinaryIndexedTree1 {
    /*
        Template name: The template of binary indexed tree, single edit and
       range query Author: Conless Date: 2017-11-15 File name:
       /oi/template/bitree.hpp Required constants: MAXN (the size of the tree)
    */

    int size;
    long long data[MAXN << 2];

    // Get the lowbit of the number
    inline int lowbit(int x) { return x & (-x); }

    /*
        Here, from the principle of the binary indexed tree, we can find the
       father of a node, 1000 /   / | 0100       /  | /    |        /   | 0010
       |      0110  | /            |      /     | 0001              0011  0101
       0111
    */

  public:
    // The construction function of the tree, where size should be given.
    BinaryIndexedTree1(int SizeOfTheTree = 0) {
        size = SizeOfTheTree;
        memset(data, 0, sizeof(data));
    }

    // Reconstruction fuction for the tree, mainly used when the tree would be
    // better as a global variable, whose size would be determined later.
    void RebuildTree(int NewSize) {
        size = NewSize;
        memset(data, 0, sizeof(data));
    }

    // Add number at a single point of the tree.
    void AddNum(int Position, int Num) {
        while (Position <= size) {
            data[Position] += Num;
            Position += lowbit(Position);
        }
    }

    // Ask the query sum from 1 to the given position
    long long AskSum(int Position) {
        if (Position > size)
            Position = size;
        long long ans = 0;
        while (Position > 0) {
            ans += data[Position];
            Position -= lowbit(Position);
        }
        return ans;
    }
};
} // namespace Template
// Classes

// Funtions

Template::BinaryIndexedTree1 btree1, btree2;

// Main function
int main() {
    scanf("%d", &n);
    long long maxa = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &data[i]);
        maxa = std::max(maxa, data[i]);
    }
    btree1.RebuildTree(maxa);
    btree2.RebuildTree(maxa);
    for (int i = 1; i <= n; i++) {
        presum[i] = presum[i - 1] + data[i];
        ans[i] = ans[i - 1] + presum[i - 1];
        for (int j = 1; j * data[i] <= maxa; j++) {
            int sumrange = btree1.AskSum((j + 1) * data[i] - 1) -
                           btree1.AskSum(j * data[i] - 1);
            ans[i] -= sumrange * j * data[i];
        }
        btree1.AddNum(data[i], 1);
        ans[i] += 1LL * (i - 1) * data[i] - btree2.AskSum(data[i]);
        for (int j = 1; j * data[i] <= maxa; j++)
            btree2.AddNum(j * data[i], data[i]);
        printf("%lld ", ans[i]);
    }
    printf("\n");
    return 0;
}