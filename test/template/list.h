#include <iostream>

using namespace std;

class A {
    const int a = 2;
};

template <class T> class list {
  public:
    struct node {
        T data;
        node *pre, *nex;
        node() : pre(nullptr), nex(nullptr) {}
        node(T _data) : data(_data), pre(nullptr), nex(nullptr) {}
    } * head, *tail;

    list() : head(nullptr), tail(nullptr) {}
    ~list() {
        node *now = head;
        while (now != nullptr) {
            node *tmp = now->nex;
            delete now;
            now = tmp;
        }
    }
    void push_back(T data) {
        node *tmp = new node(data);
        if (tail == nullptr)
            head = tail = tmp;
        else {
            node *now = tail;
            tmp->pre = now;
            now->nex = tmp;
            tail = tmp;
        }
    }
    void push_front(T data) {
        node *tmp = new node(data);
        if (head == nullptr)
            head = tail = tmp;
        else {
            node *now = head;
            now->pre = tmp;
            tmp->nex = now;
            head = tmp;
        }
    }
    void print() {
        node *now = head;
        cout << "Printing:\n";
        while (now != nullptr) {
            node *tmp = now->nex;
            cout << now->data << ' ';
            now = tmp;
        }
        cout << '\n';
    }
};

template class list<int>;