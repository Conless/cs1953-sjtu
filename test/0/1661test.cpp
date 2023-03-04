#include <bits/stdc++.h>
using namespace std;

struct Node {
    int val;
    Node *next;
    Node(int val = 0): val(val), next(nullptr) {}
};

struct LinkedList {
    // todo: some variables here
    Node *head;
    int n;
    Node *get(int i) {
        Node *p = head;
        while (i > 1) { p = p->next, i--; }
        return p;
    }
    void ins(Node *&p, int x) {
        Node *q = new Node(x);
        q->next = p;
        p = q;
    }
    void del(Node *&p) {
        Node *q = p;
        p = p->next;
        delete q;
    }
    void initialize() {
        head = nullptr;
        scanf("%d", &n);
        int *a = new int[n];
        for (int i = 0; i < n; i++) { scanf("%d", &a[i]); }
        for (int i = n - 1; i >= 0; i--) { ins(head, a[i]); }
        delete[] a;
    }

    void insert(int i, int x) {
        Node *p = get(i);
        ins(p->next, x);
        n++;
    }

    void erase(int i) {
        if (i > 1) {
            Node *p = get(i - 1);
            del(p->next);
        } else { del(head); }
        n--;
    }

    void swap() {
        Node *p = head, *q;
        for (int i = 1; i < n; i += 2) {
            q = p->next;
            ::swap(p->val, q->val);
            p = q->next;
        }
    }

    void moveback(int i, int x) {
        Node *p0 = head, *p = get(i), *q = get(i + x);
        head = p->next, p->next = q->next, q->next = p0;
    }

    int query(int i) {
        return get(i)->val;
    }

    void printAll() {
        Node *p = head;
        while (p) { cout << (p->val) << ((p->next) ? ' ' : '\n'), p = p->next; }
    }

    void ClearMemory() {
        while (head) { del(head); }
        n = 0;
    }
};

int main() {
    freopen("1661new.in", "r", stdin);
    LinkedList List;
    int m, op, i, x;
    List.initialize();
    scanf("%d", &m);
    while (m--) {
        scanf("%d", &op);
        if (op == 1) {
            scanf("%d%d", &i, &x);
            List.insert(i, x);
        } else if (op == 2) {
            scanf("%d", &i);
            List.erase(i);
        } else if (op == 3) {
            List.swap();
        } else if (op == 4) {
            scanf("%d%d", &i, &x);
            List.moveback(i, x);
        } else if (op == 5) {
            scanf("%d", &i);
            printf("%d\n", List.query(i));
        } else if (op == 6) {
            List.printAll();
        }
    }
    List.ClearMemory();
    return 0;
}