// Statement and information
// Author: Conless
// Date: 2022-10-11
// File name: /oi/acmoj/1661new.cpp

// Headers
#include <iostream>
#include <cstdio>

// Constants, global variables and definitions

// Templates and namespaces

// Classes
class ListNode {
  private:
    int data;
    ListNode *next;
    friend class LinkedList;

  public:
    ListNode(int data = 0) : data(data), next(nullptr) {}
};

class LinkedList {
  private:
    ListNode *head;
    int length;

    ListNode *GetAddress(int pos) {
        ListNode *now = head;
        while (--pos)
            now = now->next;
        return now;
    }
    void InsertAtAddress(ListNode *&now, int data) {
        ListNode *now1 = new ListNode;
        now1->data = data;
        now1->next = now;
        now = now1;
        length++;
    }
    void DeleteAtAddress(ListNode *&now) {
        ListNode *now1 = now;
        now = now->next;
        length--;
        delete now1;
    }
  public:
    LinkedList() {
        int n;
        length = 0;
        scanf("%d", &n);
        int *a = new int[n];
        head = nullptr;
        for (int i = 0; i < n; i++)
            scanf("%d", &a[i]);
        for (int i = n - 1; i >= 0; i--)
            InsertAtAddress(head, a[i]);
        delete[] a;
    }
    void clean() {
        ListNode *now1 = head;
        ListNode *now2 = now1->next;
        while (now2 != nullptr) {
            delete now1;
            now1 = now2;
            now2 = now2->next;
        }
        delete now1;
        head = nullptr;
    }
    void Output() {
        ListNode *now = head;
        while (now != nullptr) {
            printf("%d ", now->data);
            now = now->next;
        }
        printf("\n");
    }

    void InsertNode(int pos, int data) {
        ListNode *now = GetAddress(pos);
        InsertAtAddress(now->next, data);
    }
    void DeleteNode(int pos) {
        if (pos == 1) {
            DeleteAtAddress(head);
            return;
        }
        ListNode *now = GetAddress(pos - 1);
        DeleteAtAddress(now->next);
    }
    void SwapData() {
        if (length <= 1)
            return;
        ListNode *now1 = head;
        ListNode *now2;
        for (int i = 1; i <= length - 1; i += 2)
        {
            now2 = now1->next;
            std::swap(now1->data, now2->data);
            now1 = now2->next;
        }
    }
    void MoveBack(int pos, int length) {
        ListNode *now1 = head;
        ListNode *now2 = GetAddress(pos);
        ListNode *now3 = GetAddress(pos + length);
        head = now2->next;
        now2->next = now3->next;
        now3->next = now1;
    }

    int GetNum(int pos) {
        ListNode *now = GetAddress(pos);
        return now->data;
    }
};
// Funtions

// Main function
int main() {
    // freopen("1661new.in", "r", stdin);
    LinkedList l;
    int m;
    scanf("%d", &m);
    while (m--) {
        int op, i, x;
        scanf("%d", &op);
        switch (op) {
        case 1:
            scanf("%d%d", &i, &x);
            l.InsertNode(i, x);
            break;
        case 2:
            scanf("%d", &i);
            l.DeleteNode(i);
            break;
        case 3:
            l.SwapData();
            break;
        case 4:
            scanf("%d%d", &i, &x);
            l.MoveBack(i, x);
            break;
        case 5:
            scanf("%d", &i);
            printf("%d\n", l.GetNum(i));
            break;
        case 6:
            l.Output();
            break;
        }
        // l.Output();
    }
    l.clean();
    return 0;
}