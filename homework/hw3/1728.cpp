#include <algorithm>

void Init(int **&p, int n) { //初始化，n为vector的个数,传入的p指向nullptr
    // todo
    p = new int *[n + 1];
    for (int i = 0; i <= n; i++) {
        p[i] = new int[11];
        p[i][0] = 10;
        p[i][1] = 2;
    }
}
void Add_element(int **&p, int x, int y) { //在第x(1-base)个vector后面添加一个元素y
    // todo
    if (p[x][1] > p[x][0]) {
        if (p[0][0] <= p[x][0]) {
            int num = p[x][0];
            delete[] p[0];
            p[0] = new int[num + 11];
            p[0][0] = num + 10;
        }
        int numm = p[0][0];
        for (int i = 1; i < p[x][1]; i++)
            p[0][i] = p[x][i];
        delete[] p[x];
        p[x] = new int[numm + 11];
        for (int i = 1; i < p[0][1]; i++)
            p[x][i] = p[0][i];
        p[x][0] = numm + 10;
    }
    p[x][p[x][1]++] = y;
}
int Get_element(int **&p, int x, int k) { //获取第x(1-base)个vector中第k个(1-base)元素的值
    // todo
    return p[x][k + 1];
}
void Clear(int **&p, int n) { //回收空间
    // todo
    for (int i = 0; i <= n; i++)
        delete[] p[i];
    delete[] p;
}