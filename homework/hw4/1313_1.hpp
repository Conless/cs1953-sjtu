// "Wrapper": src.hpp
#ifndef Wrapper_CPP_Wrapper_HPP
#define Wrapper_CPP_Wrapper_HPP

#include <string>

using namespace std;

struct Wrapper {
    // todo: add definitions here
    void (*func)(string func_name);
    void (*pre)(), (*suf)();
};

// todo: add definition for link list
struct node {
    Wrapper *data;
    node *next;
} * head(nullptr), *tail(head);

// todo: create()
Wrapper *create(void (*f)(string s), void (*p)(), void (*s)()) {
    if (tail == nullptr) {
        head = new node;
        head->data = new Wrapper;
        head->data->func = f;
        head->data->pre = p;
        head->data->suf = s;
        tail = head;
    } else {
        tail->next = new node;
        tail->next->data = new Wrapper;
        tail = tail->next;
        tail->data->func = f;
        tail->data->pre = p;
        tail->data->suf = s;
    }
    return tail->data;
}

// todo: remove()
void remove(Wrapper *f) {
    if (head->next == nullptr) {
        if (head->data == f) {
            head = nullptr;
            tail = nullptr;
        }
        return;
    }
    if (head->data == f) {
        node *tmp = head->next;
        delete head;
        head = tmp;
        return;
    }
    node *now = head;
    while (now->next->data != f)
        now = now->next;
    if (now->next->next != nullptr) {
        node *tmp = now->next->next;
        delete now->next;
        now->next = tmp;
    } else {
        tail = head;
        delete head->next;
        head->next = nullptr;
    }
}

// todo: run()
void run(Wrapper *f, string inp) {
    f->pre();
    f->func(inp);
    f->suf();
    return;
}

// todo: destroy()
void destroy() {
    while (head != nullptr) {
        node *now = head->next;
        delete head;
        head = now;
    }
}

#endif // Wrapper_CPP_Wrapper_HPP