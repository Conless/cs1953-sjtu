#include "list.h"
#include <iostream>

using namespace std;

int main() {
    int data;
    list<int> a;
    while (cin >> data) {
        a.push_back(data);
        a.push_front(data);
        a.print();
        
    }
    return 0;
}