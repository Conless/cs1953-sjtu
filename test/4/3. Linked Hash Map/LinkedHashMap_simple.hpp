//
// Created by wzj on 2021/12/3.
//

#ifndef FINAL_SRC_HPP
#define FINAL_SRC_HPP

#include <string>
#include <vector>
using namespace std;

class LinkedHashMap;
struct Node{
    Node* next=nullptr;
    Node* timePre=nullptr;
    Node* timeNext=nullptr;

    int key=0;
    string value;
};

struct Data{
    int key;
    string value;
};

vector<Data> traverseByTime(const LinkedHashMap& obj);
vector<Data> traverseByIndex(const LinkedHashMap& obj);

class LinkedHashMap{
// todo: Modify "beg", "current" and related parts in the constructor as you wish.
// todo: 你可以根据自己写链表的习惯修改或删除头尾节点并对应修改构造函数。
public:
    int len;
    Node** array;
    Node* beg;
    Node* current;
    bool forEachMethod;
    // Notice: In this version, you don't need to
    // implement a function pointer here to make the code compile. 
    // 注意：这是一个不会函数指针能通过编译的版本。

    LinkedHashMap(int _len_,bool forEachByTime){
        len=_len_;
        beg=new Node();
        current=beg;
        array=new Node*[len];
        for(int i=0;i<len;i++)
            array[i]=nullptr;
        forEachMethod=forEachByTime;
    }

    ~LinkedHashMap(){
        //todo

    }

    void insert(int key,string value){
        //todo
    }

    void remove(int key,string value){
        //todo
    }

    vector<string> ask(int key)const{
        //todo
    }

    vector<Data> forEach()const{
        if(forEachMethod){
            return traverseByTime(*this);
        }else{
            return traverseByIndex(*this);
        }
    }
};

vector<Data> traverseByTime(const LinkedHashMap& obj){
    //todo
}

vector<Data> traverseByIndex(const LinkedHashMap& obj){
    //todo
}

#endif //FINAL_SRC_HPP
