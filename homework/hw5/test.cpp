#include <bits/stdc++.h>

using namespace std;

struct node {
    int data;
    node *last, *next;
    node(int data) : data(data) {}
} *head = nullptr;

int main() {
    head = new node(0);
    node *tail = new node(1);
    head->next = tail, tail->last = head;
    tail->next = new node(2);
    tail = tail->next, tail->last = head->next;
    node *tmp = tail;
    tail = tail->last;
    delete tmp;
    tail->next = nullptr;
    delete tail;
    delete head;
}
