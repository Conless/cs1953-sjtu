#include <iostream>

using namespace std;

const auto func = [](const int &n) -> void {
    // todo
    int sel[15] = {0};
    int visc[15] = {0}, viss[30] = {0}, visd[30] = {0};
    const auto &s = [&](auto &&self, int n, int now) -> void {
        if (now == n) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < sel[i]; j++)
                    printf(".");
                printf("Q");
                for (int j = sel[i] + 1; j < n; j++)
                    printf(".");
                printf("\n");
            }
        } else {
            for (int i = 0; i < n; i++) {
                if (visc[i])
                    continue;
                if (viss[i + now])
                    continue;
                if (visd[i - now + n])
                    continue;
                visc[i] = 1;
                viss[i + now] = 1;
                visd[i - now + n] = 1;
                sel[now] = i;
                self(self, n, now + 1);
                visc[i] = 0;
                viss[i + now] = 0;
                visd[i - now + n] = 0;
                sel[now] = 0;
            }
        }
    };
    s(s, n, 0);
};

int main() {
    int n;
    cin >> n;
    func(n);
    return 0;
}