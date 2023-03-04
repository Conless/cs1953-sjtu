//
// Created by wzj on 2021/12/3.
//

#ifndef FINAL_SRC_HPP
#define FINAL_SRC_HPP

#include <string>
#include <vector>
using namespace std;

class LinkedHashMap;

struct Node {
    Node *next = nullptr;
    Node *timePre = nullptr;
    Node *timeNext = nullptr;

    int key = 0;
    string value;
};

struct Data {
    int key;
    string value;
};

vector<Data> traverseByTime(const LinkedHashMap &obj);
vector<Data> traverseByIndex(const LinkedHashMap &obj);

class LinkedHashMap {
    // todo: Modify "beg", "current" and related parts in the constructor as you wish.
    // todo: 你可以根据自己写链表的习惯修改或删除头尾节点并对应修改构造函数。
  public:
    int len;
    Node **array;
    Node *head = nullptr;
    Node *tail = nullptr;
    // todo: define a function pointer called "forEachMethod"
    vector<Data> (*forEachMethod)(const LinkedHashMap &obj);
    // to be pointed to function "traverseByTime" or "traverseByDict".
    // todo: 定义一个名为forEachMethod的函数指针，用于对应travelByTime和travelByDict函数。

    LinkedHashMap(int _len_, bool forEachByTime) {
        len = _len_;
        array = new Node *[len];
        for (int i = 0; i < len; i++)
            array[i] = nullptr;
        if (forEachByTime)
            forEachMethod = traverseByTime;
        else
            forEachMethod = traverseByIndex;
    }

    ~LinkedHashMap() {
        // todo
        
    }

    void insert(int key, string value) {
        // todo
        Node *tmp = new Node;
        tmp->key = key;
        tmp->value = value;
        tmp->timePre = tail;
        if (head == nullptr) {
            head = tail = tmp;
            array[key] = tmp;
        } else {
            // time line
            tail->timeNext = tmp;
            tmp->timePre = tail;
            // hash map
            Node *now = array[key];
            if (now == nullptr)
                array[key] = tmp;
            else {
                tmp->next = now;
                now = tmp;
            }
        }
    }

    void remove(int key, string value) {
        // todo
        Node *now = array[key];
        while (now != nullptr && now->value == value) {
            if (now->timePre != nullptr)
                now->timePre->timeNext = now->timeNext;
            Node *tmp = now;
            now = array[key] = tmp->next;
            if (tmp == head)
                head = nullptr;
            if (tmp == tail)
                tail = nullptr;
            delete tmp;
        }
        if (now == nullptr)
            return;
        while (now->next != nullptr) {
            if (now->next->value == value) {
                if (now->next->timePre != nullptr)
                    now->timePre->timeNext = now->timeNext;
                Node *tmp = now->next;
                now->next = tmp->next;
                if (tmp == head)
                    head = nullptr;
                if (tmp == tail)
                    tail = nullptr;
                delete tmp;
            }
            if (now == nullptr)
                return;
            now = now->next;
        }
    }

    vector<string> ask(int key) const {
        // todo
        vector<string> ret;
        Node *now = array[key];
        while (now != nullptr) {
            ret.push_back(now->value);
            now = now->next;
        }
        return ret;
    }

    vector<Data> forEach() const { return forEachMethod(*this); }
};

vector<Data> traverseByTime(const LinkedHashMap &obj) {
    // todo
    vector<Data> ret;
    Node *now = obj.head;
    while (now != nullptr) {
        ret.push_back({now->key, now->value});
        now = now->timeNext;
    }
    return ret;
}

vector<Data> traverseByIndex(const LinkedHashMap &obj) {
    // todo
    vector<Data> ret;
    for (int i = 0; i < obj.len; i++) {
        Node *now = obj.array[i];
        while (now != nullptr) {
            ret.push_back({now->key, now->value});
            now = now->next;
        }
    }
    return ret;
}

#endif // FINAL_SRC_HPP
