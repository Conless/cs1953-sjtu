#include <iostream>

using namespace std;

class A {
  public:
    int a, b;
    A(int a, int b) : a(a), b(b) {}
    // A(const A &x) {
    //     a = x.a << 1;
    //     b = x.b << 1;
    // }
    A operator=(const A &x) {
        a = x.a << 1;
        b = x.b << 1;
        return *this;
    }
};

int main() {
    A x(1, 2);
    A y = x;
    cout << y.a << " " << y.b << endl;
    y = x;
    cout << y.a << " " << y.b << endl;
}