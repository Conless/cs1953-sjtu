#ifndef ARRAY_LIST_HPP
#define ARRAY_LIST_HPP

#include <iostream>

#define USE_OS

// Don't delete the error class below.
// 不要删除下面的错误类
class error : public std::exception {
  private:
    std::string msg;

  public:
    explicit error(const char *_msg_) : msg(_msg_) {}

    const char *toString() { return msg.c_str(); }
};

template <class T> class ArrayList {
  private:
    T *arr = nullptr;
    int len;
    bool init;

  public:
    // default constructor
    ArrayList() : len(0), init(false) {}
    // constructor with a given array (T* arr, int length) 从已有的数组构造
    ArrayList(T *_arr, int _len) {
        if (_len < 0)
            throw error("invalid length");
        len = _len;
        if (arr != nullptr)
            delete[] arr;
        arr = new T[len];
        init = 1;
        for (int i = 0; i < len; i++)
            arr[i] = _arr[i];
    }
    // constructor with fixed length (int length) 构造一个固定长度的数组
    ArrayList(int _len) {
        if (_len < 0)
            throw error("invalid length");
        len = _len;
        if (arr != nullptr)
            delete[] arr;
        arr = new T[len];
    }
    // copy constructor 拷贝构造函数
    ArrayList(const ArrayList &x) {
        len = x.len;
        init = x.init;
        if (arr != nullptr)
            delete[] arr;
        arr = new T[len];
        for (int i = 0; i < len; i++)
            arr[i] = x.arr[i];
    }
    // size()
    int size() { return len; }
    // operator[]
    auto operator[](int pos) -> T & {
        if (pos >= len || pos < 0)
            throw error("index out of bound");
        return *(arr + pos);
    }
    auto operator[](int pos) const -> const T & {
        if (pos >= len || pos < 0)
            throw error("index out of bound");
        return *(arr + pos);
    }
    // operator+
    friend ArrayList<T> operator+(const ArrayList<T> &x, const ArrayList<T> &y) {
        ArrayList<T> ret(x.len + y.len);
        for (int i = 0; i < x.len; i++)
            ret.arr[i] = x.arr[i];
        for (int i = x.len; i < x.len + y.len; i++)
            ret.arr[i] = y.arr[i - x.len];
        return ret;
    }
    // operator=
    ArrayList<T> operator=(const ArrayList<T> &x) {
        len = x.len;
        init = x.init;
        if (arr != nullptr)
            delete[] arr;
        arr = new T[len];
        for (int i = 0; i < len; i++)
            arr[i] = x.arr[i];
        return *this;
    }
    // operator==
    bool operator==(const ArrayList<T> &x) {
        if (len != x.len)
            return false;
        for (int i = 0; i < len; i++)
            if (!(arr[i] == x.arr[i]))
                return false;
        return true;
    }
    // operator!=
    bool operator!=(const ArrayList<T> &x) { return !(*this == x); }
#ifdef USE_OS
    friend std::ostream &operator<<(std::ostream &os, const ArrayList<T> &x) {
        for (int i = 0; i < x.len; i++) {
            os << x.arr[i];
            if (i != x.len - 1)
                os << ' ';
        }
        return os;
    }

#else
    // Notice: if you don't know how to implement operator<<,
    // you can use the following two print() functions AND COMMENT
    // "#define USE_OS" IN LINE 6 to enable your print functions.
    // 如果你不知道如何重载 operator<< ，请并注释掉
    // 第六行的 "#define USE_OS" 使得你的 print() 函数能够正常使用。
    void print() {
        for (int i = 0; i < length; i++)
            std::cout << arr[i] << " ";
    }
    void print() const {
        for (int i = 0; i < length; i++)
            std::cout << arr[i] << " ";
    }

#endif

    // destructor 析构函数
    ~ArrayList() {
        if (arr != nullptr)
            delete[] arr;
    }
};

template 

#endif // ARRAY_LIST_HPP