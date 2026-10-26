#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
    #define dbg(...) fprintf(stderr, ##__VA_ARGS__)
#else
    #define dbg(...) 42
#endif

#define all(x) (x).begin(), (x).end()
using LL = long long;

inline void output(auto &&p) {
    const int n = int(p.size());
    for (int i = 0; i < n; ++i) cout << p[i] << " \n"[i == n - 1];
}

struct MainOne {
    int n;
    vector<int> a, p;
    vector<vector<int>> pre, suf;
    bool flag_pre = 1;
    void main() {
        cin >> n;
        a.assign(n, 0);
        for (auto &x : a) cin >> x;
        p.assign(n, 0);
        iota(all(p), 1);
        pre.assign(n - 1, vector<int>(n, 0));
        pre[0] = p;
        if (p == a) flag_pre = 0;
        for (int i = 1; i < n - 1; ++i) {
            next_permutation(all(p));
            pre[i] = p;
            if (p == a) flag_pre = 0;
        }
        for (int i = 0; i < n; ++i) p[i] = n - i;
        suf.assign(n - 1, vector<int>(n, 0));
        suf[0] = p;
        for (int i = 1; i < n - 1; ++i) {
            prev_permutation(all(p));
            suf[i] = p;
        }
        auto &&vec = flag_pre ? pre : suf;
        for (auto &v : vec) output(v);
        output(a);
    }
};
struct MainTwo {
    int n;
    vector<vector<int>> a;
    int mn = 0, mx = 0;
    void main() {
        cin >> n;
        a.assign(n, vector<int>(n, 0));
        for (auto &v : a)
            for (auto &x : v) cin >> x;
        sort(all(a));
        vector<int> p(n);
        iota(all(p), 1);
        bool flag_last = 1;
        for (int i = 0; i < n - 1; ++i) {
            if (p != a[i]) {
                flag_last = 0;
                break;
            }
            next_permutation(all(p));
        }
        output(a[flag_last ? (n - 1) : 0]);
    }
};

int main() {
#ifndef LOCAL
    cin.tie(nullptr)->sync_with_stdio(false);
#endif
    string op;
    cin >> op;
    if (op == "first")
        MainOne{}.main();
    else
        MainTwo{}.main();
    return 0;
}
