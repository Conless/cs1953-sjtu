#include <cstring>
#include <iostream>

int n;

// 写出两个函数的声明

int *&funA(int **&ptr);
void funB(int *ans, int **&a, int **&b);

int main() {
    int a[100], b[100], c[100];
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }
    for (int i = 0; i < n; ++i) {
        std::cin >> b[i];
    }
    int **p = nullptr;
    int **q = nullptr;
    funA(p) = a;
    funA(q) = b;
    funB(c, p, q);
    for (int i = 0; i < n; ++i) {
        std::cout << c[i] << " ";
    }
    return 0;
}

// 写出两个函数的定义

int *&funA(int **&ptr) { ptr = new int*; ptr[0] = new int[100]; return ptr[0]; }

void funB(int *ans, int **&a, int **&b) {
    for (int i = 0; i < n; ++i) {
        ans[i] = a[0][i] * b[0][i];
    }
    delete[] a[0];
    delete[] b[0];
    delete a;
    delete b;
}