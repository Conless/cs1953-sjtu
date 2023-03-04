#include <cmath>
#include <iomanip>
#include <iostream>

using namespace std;

class CircleSet {
    friend istream &operator>>(istream &in, CircleSet &obj);

  private:
    struct Circle {
        long long x, y, r;
        Circle(long long _x = 0, long long _y = 0, long long _r = 0) : x(_x), y(_y), r(_r) {}
    };
    int count;       //集合中圆的数目
    Circle *circles; //集合中所有圆
    long long dis(int p, int q) { return pow(circles[p].x - circles[q].x, 2) + pow(circles[p].y - circles[q].y, 2); }

  public:
    CircleSet(int n) : count(n) { circles = new Circle[n]; }
    ~CircleSet() { delete []circles; }
    long long operator[](int p) { return circles[p].r; }
    bool checkContaining(int p, int q) {
        return (circles[p].r > circles[q].r && dis(p, q) < pow(circles[p].r - circles[q].r, 2));
    }
    int getCircleContainingQ(int q) {
        long long ans = 10005;
        for (int i = 0; i < count; i++) {
            if (checkContaining(i, q)) {
                ans = min(ans, circles[i].r);
            }
        }
        return ans;
    }
};

istream &operator>>(istream &in, CircleSet &obj) {
    for (int i = 0; i < obj.count; ++i) {
        in >> obj.circles[i].x >> obj.circles[i].y >> obj.circles[i].r;
    }
    return in;
}

int main() {
    int n, m, type;
    cin >> n >> m;
    CircleSet set(n);
    cin >> set; //输入集合中的所有圆
    while (m--) {
        int type, p, q;
        cin >> type;
        if (type == 1) {
            // do nothing
        } else if (type == 2) {
            for (int i = 0; i < n; ++i) {
                cout << set[i] << ' ';
            }
            cout << endl;
        } else if (type == 3) {
            cin >> p >> q;
            cout << set.checkContaining(p, q) << endl;
        } else if (type == 4) {
            cin >> q;
            cout << set.getCircleContainingQ(q) << endl;
        }
    }
    return 0;
}