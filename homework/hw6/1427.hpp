#include <bits/stdc++.h>

using namespace std;

class pylist {
    vector<pylist*> _ptr;

  public:
    pylist() {}
    pylist(const int &x) {
        pylist *tmp = new pyint(x);
        _ptr.push_back(tmp);
    }
    void append(const pylist &x) { pyint *tmp = new pyint(x); 

    }
    pylist pop() {
        if (type.back() == 0) {
            int ret = num_int[type.size() - 1];
            num_int.erase(type.size() - 1);
            type.pop_back();
            return ret;
        } else {
        }
    }
    pylist &operator[](size_t i) {
        return *this; // meaningless return to prevent compile error.
    }
    operator int() { return }

    friend std::ostream &operator<<(std::ostream &os, const pylist &ls) { return os; }
};
