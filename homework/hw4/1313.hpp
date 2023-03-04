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
    Wrapper data;
    node *next;
    node() {}
} * head(nullptr), *tail(head);

int siz = 0;

// todo: create()
Wrapper *create(void (*f)(string s), void (*p)(), void (*s)()) {
    if (!siz) {
        head = new node;
        head->data.func = f;
        head->data.pre = p;
        head->data.suf = s;
        tail = head;
    } else {
        tail->next = new node;
        tail = tail->next;
        tail->data.func = f;
        tail->data.pre = p;
        tail->data.suf = s;
    }
    siz++;
    return &(tail->data);
}

// todo: remove()
void remove(Wrapper *f) {
    siz--;
    if (head == tail) {
        if (&(head->data) == f) {
            delete head;
        }
        return;
    }
    if (&(head->data) == f) {
        node *tmp = head->next;
        delete head;
        head = tmp;
        return;
    }
    node *now = head;
    while (&(now->next->data) != f)
        now = now->next;
    if (now->next != tail) {
        node *tmp = now->next->next;
        delete now->next;
        now->next = tmp;
    } else {
        delete now->next;
        tail = now;
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
    if (!siz)
        return;
    while (head != tail) {
        node *now = head->next;
        delete head;
        head = now;
        siz--;
    }
    siz--;
    delete tail;
}

#endif // Wrapper_CPP_Wrapper_HPP