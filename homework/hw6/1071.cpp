#include <bits/stdc++.h>

class LinkList {
  private:
    struct node {
        int data;
        node *next;
        node(int data) : data(data), next(nullptr) {}
    } * head, *tail;
    int siz;

    bool empty() { return siz == 0; }
    int front() { return head->data; }
    void pop_front() {
        node *tmp = head;
        head = head->next;
        delete tmp;
        siz--;
        if (!siz)
            head = tail = nullptr;
    }
    void push_back(int x) {
        node *tmp = new node(x);
        siz++;
        if (siz == 1)
            head = tail = tmp;
        else {
            tail->next = tmp;
            tail = tmp;
        }
    }

  public:
    LinkList() {
        head = tail = nullptr;
        siz = 0;
    }
    ~LinkList() {
        if (siz) {
            while (true) {
                node *tmp = head;
                if (tmp->next == nullptr) {
                    siz--;
                    delete tmp;
                    return;
                } else {
                    siz--;
                    head = head->next;
                    delete tmp;
                }
            }
            head = tail = nullptr;
        }
    }
    void push(int x) {
        node *tmp = new node(x);
        delete tmp;
        siz++;
        if (siz == 1) {
            head = tail = tmp;
        } else {
            node *now = head;
            if (now->data > x) {
                tmp->next = head;
                head = tmp;
            } else {
                while (now->next != nullptr) {
                    if (now->next->data > x) {
                        tmp->next = now->next;
                        now->next = tmp;
                        return;
                    }
                    now = now->next;
                }
                now->next = tmp;
                tail = tmp;
            }
        }
    }
    int getKth(int k) {
        if (k >= siz)
            return -1;
        node *tmp = head;
        while (k--)
            tmp = tmp->next;
        return tmp->data;
    }
    void merge(LinkList *a) {
        LinkList *tmp = new LinkList;
        while (!empty() && !a->empty()) {
            int x = front(), y = a->front();
            if (x < y) {
                tmp->push_back(x);
                pop_front();
            } else {
                tmp->push_back(y);
                a->pop_front();
            }
        }
        while (!empty()) {
            tmp->push_back(front());
            pop_front();
        }
        while (!a->empty()) {
            tmp->push_back(a->front());
            a->pop_front();
        }
        while (!tmp->empty()) {
            push_back(tmp->front());
            tmp->pop_front();
        }
        delete tmp;
    }
};

class LinkListArray {
  private:
    int len;
    LinkList **lists;

  public:
    LinkListArray(int n) : len(n) {
        lists = new LinkList *[n];
        for (int i = 0; i < n; ++i)
            lists[i] = new LinkList;
    }
    ~LinkListArray() {
        for (int i = 0; i < len; ++i) {
            delete lists[i];
        }
        delete[] lists;
    }

    void insertNumber(int n, int x) { lists[n]->push(x); }
    int queryNumber(int n, int k) { return lists[n]->getKth(k); }
    void mergeLists(int p, int q) { lists[p]->merge(lists[q]); }
};

using namespace std;
int main() {
    // int len, m;
    // scanf("%d%d", &len, &m);
    // LinkListArray a = LinkListArray(len);
    // for (int i = 0, op, s1, s2; i < m; ++i) {
    //     scanf("%d%d%d", &op, &s1, &s2);
    //     if (op == 0) {
    //         a.insertNumber(s1, s2);
    //     }
    //     if (op == 1) {
    //         printf("%d\n", a.queryNumber(s1, s2));
    //     }
    //     if (op == 2) {
    //         a.mergeLists(s1, s2);
    //     }
    // }
    int n;
    cin >> n;
    LinkListArray a(1);
    for (int i = 0; i < n; i++) {
        int num;
        cin >> num;
        a.insertNumber(0, num);
    }
    for (int i = 0; i < n; i++) {
        cout << a.queryNumber(0, i);
    }
    return 0;
}
