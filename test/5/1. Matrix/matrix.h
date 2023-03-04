#ifndef MATRIX_H_
#define MATRIX_H_

#include <bits/stdc++.h>
#include <exception>
// just include whatever you want

using namespace std;

namespace sjtu {

class MatrixSizeError : public std::exception {
  public:
    const char *what() noexcept { return "matrix size mismatch"; }
};
class MatrixIndexingError : public std::exception {
  public:
    const char *what() noexcept { return "invalid matrix indexing"; }
};

template <typename T> class Matrix {
  private:
    int h, w;
    vector<vector<T>> data;

  public:
    int height() const { return h; }
    int width() const { return w; }

    Matrix() = delete;
    Matrix(int h_, int w_, T *seq = nullptr) : h(h_), w(w_) {
        int tot_size = h * w;
        data.resize(h);
        for (int i = 0; i < h; i++)
            data[i].resize(w);
        if (seq == nullptr) {
            for (int i = 0; i < tot_size; i++)
                data[i / w][i % w] = T();
        } else {
            for (int i = 0; i < tot_size; i++)
                data[i / w][i % w] = seq[i];
        }
    }
    Matrix(const Matrix &o) {
        h = o.h;
        w = o.w;
        data.clear();
        data.resize(h);
        for (int i = 0; i < h; i++) {
            data[i].resize(w);
            for (int j = 0; j < w; j++)
                data[i][j] = o.data[i][j];
        }
    }

    Matrix &operator=(const Matrix &o) {
        if (this == &o)
            return *this;
        h = o.h;
        w = o.w;
        data.clear();
        data.resize(h);
        for (int i = 0; i < h; i++) {
            data[i].resize(w);
            for (int j = 0; j < w; j++)
                data[i][j] = o.data[i][j];
        }
        return *this;
    }

    T &operator()(int row, int col) {
        if (row <= 0 || col <= 0 || row > h || col > w)
            throw MatrixIndexingError();
        row--;
        col--;
        return data[row][col];
    }

    const T &operator()(int row, int col) const {
        if (row > h | col > w)
            throw MatrixIndexingError();
        row--;
        col--;
        return data[row][col];
    }

    Matrix operator*(const Matrix &rhs) const {
        if (w != rhs.h)
            throw MatrixSizeError();
        Matrix ret(h, rhs.w);
        for (int i = 0; i < ret.h; i++) {
            for (int j = 0; j < ret.w; j++) {
                for (int k = 0; k < w; k++)
                    ret.data[i][j] = ret.data[i][j] + data[i][k] * rhs.data[k][j];
            }
        }
        return ret;
    }

    Matrix operator+(const Matrix &rhs) const {
        if (h == rhs.h && w == rhs.w) {
            Matrix ret(h, w);
            ret.data.resize(h);
            for (int i = 0; i < h; i++) {
                ret.data[i].resize(w);
                for (int j = 0; j < w; j++)
                    ret.data[i][j] = data[i][j] + rhs.data[i][j];
            }
            return ret;
        }
        if (h == 1 && rhs.w == 1) {
            Matrix lhss(rhs.h, w);
            Matrix rhss(rhs.h, w);
            for (int i = 0; i < rhs.h; i++) {
                lhss.data[i] = data[0];
                for (int j = 0; j < w; j++)
                    rhss.data[i][j] = rhs.data[i][0];
            }
            return lhss + rhss;
        }
        if (w == 1 && rhs.h == 1)
            return rhs + *this;
        throw MatrixSizeError();
    }

    ~Matrix() {
        // TODO
    }
};

template class Matrix<int>;

} // namespace sjtu

#endif // MATRIX_H_
