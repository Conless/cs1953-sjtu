#include <bits/stdc++.h>

using namespace std;

class term { //项
  public:
    int a, b, c, d;

    term() {}
    term(int _a, int _b, int _c, int _d) { // 你可以用 term t(1, 2, 3, 4); 创建一个表示 x^2sin^3xcos^4x 的term
        a = _a;
        b = _b;
        c = _c;
        d = _d;
    }
    bool operator==(const term &obj) const { // 相等表示是同类项
        return b == obj.b && c == obj.c && d == obj.d;
    }
    bool operator!=(const term &obj) const { return b != obj.b || c != obj.c || d != obj.d; }

    bool operator<(const term &obj) const {
        if (b != obj.b)
            return b > obj.b;
        if (c != obj.c)
            return c > obj.c;
        return d > obj.d;
    }

    term operator*(const term &obj) const { return term(a * obj.a, b + obj.b, c + obj.c, d + obj.d); }
};

class poly { //多项式
  public:
    int n;
    term *t;

    poly() {
        n = 0;
        t = NULL;
    }

    poly(int _n) { // 构造函数
        n = _n;
        t = new term[n];
    }

    poly(const poly &p) {
        n = p.n;
        t = new term[n];
        for (int i = 0; i < n; ++i) {
            t[i] = p.t[i];
        }
    }

    void simplify() { // 合并同类项
        std::set<term> now_poly;
        now_poly.clear();
        for (int i = 0; i < n; ++i) {
            if (t[i].a == 0)
                continue;
            auto it = now_poly.find(t[i]);
            if (it == now_poly.end())
                now_poly.insert(t[i]);
            else {
                term tt = *it;
                tt.a += t[i].a;
                now_poly.erase(it);
                now_poly.insert(tt);
            }
        }
        n = now_poly.size();
        t = new term[n];
        int i = 0;
        for (auto it : now_poly)
            t[i++] = it;
        return;
    }

    poly operator+(const poly &obj) const { // 对 poly 重载加法运算符
        poly ans(n + obj.n);
        for (int i = 0; i < n; ++i)
            ans.t[i] = t[i];
        for (int i = 0; i < obj.n; ++i)
            ans.t[i + n] = obj.t[i];
        ans.simplify();
        return ans;
    }

    poly operator-(const poly &obj) const { // 对 poly 重载减法运算符
        poly ans(n + obj.n);
        for (int i = 0; i < n; ++i)
            ans.t[i] = t[i];
        for (int i = 0; i < obj.n; ++i) {
            ans.t[i + n] = obj.t[i];
            ans.t[i + n].a *= -1;
        }
        ans.simplify();
        return ans;
    }

    poly operator*(const poly &obj) const { // 对 poly 重载乘法运算符
                                            // 重载后,你可以使用 c = a * b 来进行 poly类型的乘法
                                            // 为了避免 CE,你不应该对 a 和 b 中的任何数据做出改动
         for(int i = 0; i < n; ++i)
        	for(int j = 0; j < obj.n; ++j) {
        		term tmp = t[i] * obj.t[j];
        		if(tmp.a == 0) continue;
        		auto it = now_poly.find(tmp);
        		if(it == now_poly.end()) now_poly.insert(tmp);
        		else {
        			term new_t = *it;
        			new_t.a += tmp.a;
        			now_poly.erase(it);
        			if(new_t.a) now_poly.insert(new_t);
        		}
        	}
        if(now_poly.empty()) {
        	poly ans(1);
        	ans.t[0] = term(0);
        	return ans;
        }
        poly ans(now_poly.size());
        int i = 0;
        for(auto it:now_poly) ans.t[i++] = it;
        now_poly.clear();
        return ans;
    }

    poly &operator=(const poly &obj) {
        if (&obj == this)
            return *this;
        n = obj.n;
        if (t != NULL)
            delete[] t;
        t = new term[n];
        for (int i = 0; i < n; ++i) {
            t[i] = obj.t[i];
        }
        return *this;
    }

    poly derivate() const { // 注意,你需要以“只读模式”访问当前的poly,并返回一个求导后的poly
        poly res(n * 3);
        for (int i = 0; i < n; ++i) {
            int a = t[i].a, b = t[i].b, c = t[i].c, d = t[i].d;
            res.t[i * 3] = term(a * b, b - 1, c, d);
            res.t[i * 3 + 1] = term(a * c, b, c - 1, d + 1);
            res.t[i * 3 + 2] = term(-a * d, b, c + 1, d - 1);
        }
        res.simplify();
        return res;
    }

    ~poly() { // 析构函数,释放内存
        if (t != NULL)
            delete[] t;
    }
};

void Print(poly x) {
    for (int i = 0; i < x.n; ++i) {
        if (i && x.t[i].a > 0)
            printf("+");
        else if (x.t[i].a < 0) {
            printf("-");
            x.t[i].a = -x.t[i].a;
        }
        if (x.t[i].a > 1 || (!x.t[i].b && !x.t[i].c && !x.t[i].d))
            printf("%d", abs(x.t[i].a));
        if (x.t[i].b) {
            if (x.t[i].b == 1)
                printf("x");
            else
                printf("x^%d", x.t[i].b);
        }
        if (x.t[i].c) {
            if (x.t[i].c == 1)
                printf("sinx");
            else
                printf("sin^%dx", x.t[i].c);
        }
        if (x.t[i].d) {
            if (x.t[i].d == 1)
                printf("cosx");
            else
                printf("cos^%dx", x.t[i].d);
        }
    }
    return;
}

class frac { // 分式
  public:
    poly p, q;

    frac() {}

    frac(int x) {
        p = poly(1);
        p.t[0] = term(x, 0, 0, 0);
        q = poly(1);
        q.t[0] = term(1, 0, 0, 0);
    }

    frac(term _p) {
        q = poly(1);
        q.t[0] = term(1, 0, 0, 0);
        p = poly(1);
        p.t[0] = _p;
    }

    frac(poly _p, poly _q) : p(_p), q(_q) {}

    frac operator+(const frac &obj) const {
        return frac(p * obj.q + q * obj.p, q * obj.q); // p1/q1+p2/q2=(p1*q2+p2*q1)/(q1*q2)
    }

    frac operator-(const frac &obj) const { return frac(p * obj.q - q * obj.p, q * obj.q); }

    frac operator*(const frac &obj) const { return frac(p * obj.p, q * obj.q); }

    frac operator/(const frac &obj) const { return frac(p * obj.q, q * obj.p); }

    frac derivate() const { // 对分式求导
        return frac(p.derivate() * q - q.derivate() * p, q * q);
    }

    frac operator+=(const frac &obj) {
        *this = *this + obj;
        return *this;
    }
    frac operator-=(const frac &obj) {
        *this = *this - obj;
        return *this;
    }
    frac operator*=(const frac &obj) {
        *this = *this * obj;
        return *this;
    }
    frac operator/=(const frac &obj) {
        *this = *this / obj;
        return *this;
    }

    void output() {
        if (p.n == 1 && p.t[0].a == 0) {
            printf("0");
        } else if (q.n == 1 && q.t[0].a == 1 && q.t[0].b == 0 && q.t[0].c == 0 && q.t[0].d == 0) {
            Print(p);
        } else {
            if (p.n == 1) {
                Print(p);
            } else {
                printf("(");
                Print(p);
                printf(")");
            }
            printf("/");
            if (q.n == 1) {
                Print(q);
            } else {
                printf("(");
                Print(q);
                printf(")");
            }
        }
        printf("\n");
    }
};

inline void read_num(char *s, int &num, int &pos) {
    while (isdigit(s[pos])) {
        num = num * 10 + s[pos] - '0';
        pos++;
    }
}

void solve(char *s, int n) {
    s[n] = ')';
    n++;
    std::stack<frac> num;
    std::stack<char> opt;
    opt.push('(');
    if (isdigit(s[0]) || s[0] == 'x' || s[0] == 's' || s[0] == 'c' || s[0] == '(')
        opt.push('+');
    for (int i = 0; i < n; ++i) {
        if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/') {
            opt.push(s[i]);
            if (s[i] == '(' && (isdigit(s[i + 1]) || s[i + 1] == 'x' || s[i + 1] == 's' || s[i + 1] == 'c' || s[i + 1] == '('))
                opt.push('+');
        } else if (s[i] == '(') {
            if (isdigit(s[i + 1]) || s[i + 1] == 'x' || s[i + 1] == 's' || s[i + 1] == 'c' || s[i + 1] == '(')
                opt.push('+');
        } else if (s[i] == ')') {
            frac res(0);
            while (opt.top() != '(') {
                if (opt.top() == '+')
                    res += num.top();
                else
                    res -= num.top();
                num.pop();
                opt.pop();
            }
            num.push(res);
            opt.pop();
            if (!opt.empty() && (opt.top() == '*' || opt.top() == '/')) {
                frac t2 = num.top();
                num.pop();
                frac t1 = num.top();
                num.pop();
                if (opt.top() == '*')
                    num.push(t1 * t2);
                else
                    num.push(t1 / t2);
                opt.pop();
            }
        } else if (s[i] == 'x' || s[i] == 's' || s[i] == 'c') {
            term tmp(0, 0, 0, 0);
            if (!isdigit(s[i]))
                tmp.a = 1;
            else {
                read_num(s, tmp.a, i);
            }
            if (s[i] == 'x') {
                if (s[i + 1] != '^') {
                    tmp.b = 1;
                    i++;
                } else {
                    i += 2;
                    read_num(s, tmp.b, i);
                }
            }
            if (s[i] == 's') {
                if (s[i + 3] != '^')
                    tmp.c = 1, i += 4;
                else {
                    i += 4;
                    read_num(s, tmp.c, i);
                    i++;
                }
            }
            if (s[i] == 'c') {
                if (s[i + 3] != '^')
                    tmp.d = 1, i += 4;
                else {
                    i += 4;
                    read_num(s, tmp.d, i);
                    i++;
                }
            }
            i--;
            if (!opt.empty() && (opt.top() == '*' || opt.top() == '/')) {
                frac top = num.top();
                num.pop();
                if (opt.top() == '*')
                    num.push(top * frac(tmp));
                else
                    num.push(top / frac(tmp));
                opt.pop();
            } else
                num.push(frac(tmp));
        }
    }
    num.top().output();
    num.top().derivate().output();
}

int n;
char s[55];

int main() {
    scanf("%s", s);
    n = strlen(s);
    solve(s, n);
    return 0;
}
