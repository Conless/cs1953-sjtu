#ifndef EVIL_HPP
#define EVIL_HPP

#include <iostream>
using namespace std;

class Evil {
  private:
    int st, ed, val;
    int *data;

  public:
    Evil(int st = 0, int ed = 0, int val = 0) : st(st), ed(ed), val(val) {
        data = new int[ed - st + 1];
        for (int i = 0; i <= ed - st; ++i)
            data[i] = 0;
    }
    Evil &operator=(const Evil &x) { // note: haven't understand yet, remember to go over the knowledge of copy constructor and
                                     // operator of '='
        if (this == &x)
            return *this;
        else {
            st = x.st;
            ed = x.ed;
            val = x.val;
            delete[] data;
            data = new int[ed - st + 1];
            for (int i = 0; i <= ed - st; ++i)
                data[i] = x.data[i];
        }
        return *this;
    }
    ~Evil() { delete[] data; }
    int &operator[](int i) { return (i >= st && i <= ed) ? data[i - st] : data[0]; }
    Evil &operator++() {
        ++val;
        return *this;
    }
    Evil operator++(int) {
        Evil tmp;
        tmp = *this;
        ++val;
        return tmp;
    }
    friend ostream &operator<<(ostream &out, const Evil &evil_out) {
        out << evil_out.val << " ";
        for (int i = 0; i <= evil_out.ed - evil_out.st; ++i) {
            out << evil_out.data[i] << " ";
        }
        out << "\n";
        return out;
    }
    void Print() { cout << *this; }
};

#endif // EVIL_HPP