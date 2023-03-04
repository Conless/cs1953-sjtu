// Statement and information
/*
    Author: Conless
    Date: 2022-09-28
    File name: /oi/acmoj/1661.cpp
*/

// Headers
#include <bits/stdc++.h>
#include <cstddef>

// Constants, global variables and definitions

// Templates and namespaces

// Classes
class LinkedList {
    struct ListNode {
        int data;
        ListNode *next;
        ListNode(int num = 0) : data(num), next(nullptr) {}
    } *head;

  public:
    void Initialize() {
        int n;
        int *a = new int[n];
        scanf("%d", &n);
        head = new ListNode;
        ListNode *now = head;
        for (int i = 1; i <= n; i++) {
            now->next = new ListNode;
            now = now->next;
            scanf("%d", &a[i]);
            now->data = a[i];
        }
        delete[] a;
    }
    void Print() {
        ListNode *now = head->next;
        while (now != NULL) {
            printf("%d ", now->data);
            now = now->next;
        }
        printf("\n");
    }
    void Insert(int pos, int num) {
        ListNode *now = head;
        while (pos--)
            now = now->next;
        if (now->next == NULL) {
            now->next = new ListNode;
            now->next->data = num;
        } else {
            ListNode *backu = now->next;
            now->next = new ListNode;
            now->next->next = backu;
            now->next->data = num;
        }
    }
    void Delete(int pos) {
        ListNode *now = head;
        while (--pos)
            now = now->next;
        now->next = now->next->next;
    }
    void Swap() {
        ListNode *now = head->next;
        while (now != NULL && now->next != NULL) {
            std::swap(now->data, now->next->data);
            now = now->next->next;
        }
    }
    void Move(int num, int len) {
        for (int i = 1; i <= num; i++) {
            Insert(num + len, head->next->data);
            // std::cout << ":";
            // Print();
            Delete(1);
            // std::cout << ":";
            // Print();
        }
    }
    void Output(int pos) {
        ListNode *now = head;
        while (pos--)
            now = now->next;
        printf("%d\n", now->data);
    }
    void Haha() {
        ListNode *now = head->next;
        ListNode *haha = now;
        now = new ListNode;
        now->data = 1;
        now->next = haha;
        head->next = now;
    }
    void Free() { free(head); }
} l;

// Funtions

// Main function

int main() {
    // freopen("1661.in", "r", stdin);
    l.Initialize();
    int m;
    scanf("%d", &m);
    while (m--) {
        int op, i, x;
        scanf("%d", &op);
        switch (op) {
        case 1:
            scanf("%d%d", &i, &x);
            l.Insert(i, x);
            break;
        case 2:
            scanf("%d", &i);
            l.Delete(i);
            break;
        case 3:
            l.Swap();
            break;
        case 4:
            scanf("%d%d", &i, &x);
            l.Move(i, x);
            break;
        case 5:
            scanf("%d", &i);
            l.Output(i);
            break;
        case 6:
            l.Print();
            break;
        }
    }
    l.Free();
    return 0;
}