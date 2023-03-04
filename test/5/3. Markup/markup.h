#ifndef MARKUP_H_
#define MARKUP_H_

#include <iostream>

namespace sjtu {

class MarkUp {
  public:
    class Node {
      public:
        char ch;
        Node *next;
        // add whatever you want

        Node(char ch_, Node *prev = nullptr, Node *next_ = nullptr) {
            ch = ch_;
            next = next_;
            if (prev != nullptr)
                prev->next = this;
        }
    };

    class HeadNode {
      public:
        Node *rowHead, *rowTail; // the first letter of the line
        HeadNode *nextHead;      // link to next line
        // add whatever you want

        HeadNode(Node *rowHead_, HeadNode *prevHead = nullptr, HeadNode *nextHead_ = nullptr) {
            rowHead = rowTail = rowHead_;
            nextHead = nextHead_;
            if (prevHead != nullptr)
                prevHead->nextHead = this;
        }
        ~HeadNode() {
            Node *now = rowHead;
            while (now != nullptr) {
                Node *tmp = now->next;
                delete now;
                now = tmp;
            }
        }
        void print() const {
            Node *now = rowHead;
            while (now != nullptr) {
                putchar(now->ch);
                now = now->next;
            }
            putchar('\n');
        }
        std::string print_to_str() const {
            Node *now = rowHead;
            std::string s = "";
            while (now != nullptr) {
                s += now->ch;
                now = now->next;
            }
            return s;
        }
    };

    HeadNode *headPointer, *tailPointer;

    MarkUp() { headPointer = tailPointer = nullptr; }

    ~MarkUp() {
        // TODO: delete body
        HeadNode *now = headPointer;
        while (now != nullptr) {
            HeadNode *tmp = now->nextHead;
            delete now;
            now = tmp;
        }
    }

    void print() const {
        std::cout << "==========MARK_UP_OUTPUT==========\n"; // Output prefix. Do not modify this line!!!!
        HeadNode *now = headPointer;
        while (now != nullptr) {
            now->print();
            now = now->nextHead;
        }
    }

    void typeIn(char ch) {
        if (tailPointer == nullptr) {
            Node *tmp1 = new Node(ch);
            HeadNode *tmp2 = new HeadNode(tmp1);
            headPointer = tailPointer = tmp2;
        } else {
            Node *tail = tailPointer->rowTail;
            Node *tmp1 = new Node(ch, tail);
            if (tailPointer->rowHead == nullptr)
                tailPointer->rowHead = tmp1;
            tailPointer->rowTail = tmp1;
        }
    }

    char query(int row, int col) const {
        HeadNode *now = headPointer;
        while (--row)
            now = now->nextHead;
        Node *noww = now->rowHead;
        while (--col)
            noww = noww->next;
        return noww->ch;
    }

    // insert position is 1-based!
    // example: abc.
    // <I> refers to your mouse cursor
    // Iabc  col=1
    // aIbc  col=2
    void insert(int row, int col, char ch) {
        // TODO: insert the letter ch at (row, col)
        HeadNode *now = headPointer;
        while (--row)
            now = now->nextHead;
        Node *noww = now->rowHead;
        if (col == 1) {
            Node *tmp = new Node(ch, nullptr, noww);
            now->rowHead = tmp;
        } else {
            col--;
            while (--col)
                noww = noww->next;
            Node *tmp = new Node(ch, noww, noww->next);
            if (noww->next == nullptr)
                now->rowTail = tmp;
        }
    }

    void erase(int row, int col) {
        // TODO: erase the letter at (row, col)
        HeadNode *now = headPointer;
        while (--row)
            now = now->nextHead;
        Node *noww = now->rowHead;
        if (col == 1) {
            now->rowHead = noww->next;
            if (noww == now->rowTail)
                now->rowTail = nullptr;
            delete noww;
        } else {
            col--;
            while (--col)
                noww = noww->next;
            if (noww->next == now->rowTail)
                now->rowTail = noww;
            Node *tmp = noww->next;
            noww->next = tmp->next;
            delete tmp;
        }
    }

    // type '\n' at (row, col)
    void split(int row, int col) {
        // TODO: split a line into two
        HeadNode *now = headPointer;
        if (col == 1) {
            if (row == 1) {
                HeadNode *tmp = new HeadNode(nullptr, nullptr, now);
                headPointer = tmp;
            } else {
                row--;
                while (--row)
                    now = now->nextHead;
                HeadNode *tmp = new HeadNode(nullptr, now, now->nextHead);
            }
            return;
        }
        while (--row)
            now = now->nextHead;
        Node *noww = now->rowHead;
        col--;
        while (--col)
            noww = noww->next;
        HeadNode *tmp = new HeadNode(noww->next, now, now->nextHead);
        if (noww->next != nullptr)
            tmp->rowTail = now->rowTail;
        noww->next = nullptr;
        now->rowTail = noww;
        if (tmp->nextHead == nullptr)
            tailPointer = tmp;
    }

    void copy_paste(int src_begin_row, int src_begin_col, int src_end_row, int src_end_col, int dest_row, int dest_col) {
        // TODO: implement copy and paste
        // O(n) complexity is enough
        HeadNode *now = headPointer;
        while (--src_begin_row) {
            --src_end_row;
            now = now->nextHead;
        }
        src_end_row--;
        std::string s[100];
        Node *noww = now->rowHead;
        if (!src_end_row) {
            while (--src_begin_col) {
                src_end_col--;
                noww = noww->next;
            }
            src_end_col--;
            for (int i = 0; i <= src_end_col; i++) {
                s[0] += noww->ch;
                noww = noww->next;
            }
        } else {
            while (--src_begin_col)
                noww = noww->next;
            while (noww != nullptr) {
                s[0] += noww->ch;
                noww = noww->next;
            }
            for (int i = 1; i < src_end_row; i++) {
                now = now->nextHead;
                s[i] = now->print_to_str();
            }
            now = now->nextHead;
            noww = now->rowHead;
            for (int i = 1; i <= src_end_col; i++) {
                s[src_end_row] += noww->ch;
                noww = noww->next;
            }
        }
        // copy

        now = headPointer;
        while (--dest_row)
            now = now->nextHead;
        noww = now->rowHead;
        if (dest_col == 1) {
            noww = new Node(s[0][0]);
            for (int j = 1; j < s[0].size(); j++) {
                Node *tmp = new Node(s[0][j], noww, noww->next);
                noww = tmp;
            }
            if (noww->next == nullptr)
                now->rowTail = noww;
        } else {
            dest_col--;
            while (--dest_col)
                noww = noww->next;
            Node *tmp = new Node(s[0][0], noww, noww->next);
            noww = tmp;
            for (int j = 1; j < s[0].size(); j++) {
                Node *tmp = new Node(s[0][j], noww, noww->next);
                noww = tmp;
            }
            if (noww->next == nullptr)
                now->rowTail = noww;
        }
        if (src_end_row) {
            HeadNode *tmp[100];
            for (int i = 1; i <= src_end_row; i++) {
                Node *tmp1 = new Node(s[i][0]);
                tmp[i] = new HeadNode(tmp1);
                for (int j = 1; j < s[i].size(); j++) {
                    Node *tmp2 = new Node(s[i][j], tmp1);
                    tmp1 = tmp2;
                }
                tmp[i]->rowTail = tmp1;
            }
            for (int i = 1; i < src_end_row; i++)
                tmp[i]->nextHead = tmp[i + 1];
            tmp[src_end_row]->rowTail->next = noww->next;
            tmp[src_end_row]->nextHead = now->nextHead;
            noww->next = nullptr;
            now->nextHead = tmp[1];
            if (tmp[src_end_row]->nextHead == nullptr)
                tailPointer = tmp[src_end_row];
        }
        // paste
    }
};

} // namespace sjtu

#endif // MARKUP_H_
