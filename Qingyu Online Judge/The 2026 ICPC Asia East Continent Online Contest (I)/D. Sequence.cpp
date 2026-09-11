#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
    #include <local/dbg.h>
#else
    #define dbg(...) 42
#endif

using LL = long long;
using ai3 = array<int, 3>;
using ai26 = array<int, 26>;

#define all(x) (x).begin(), (x).end()

template <class T>
inline bool updmx(T &x, const T y) {
    if (x < y) {
        x = y;
        return 1;
    }
    return 0;
}

constexpr int P = 998244353;
struct Main {
    int n, ans = 2;
    multiset<int> p;
    vector<int> a;
    void main() {
        cin >> n;
        for (int i = 0; i < n; ++i) {
            int x;
            cin >> x;
            p.insert(x);
        }
        a.assign(n + 1, 0);
        if (!create_a()) {
            cout << "0\n";
            return;
        }
        for (int i = 1; i < n; ++i) {
            if (a[i] == a[i + 1] && a[i + 1] == (i - a[i])) {
                ans += ans;
                if (ans >= P) ans -= P;
            }
        }
        cout << ans << "\n";
    }
    bool create_a() {
        int i = 0, last = 0;
        while (i < n) {
            vector<int> pt = {last, i - last};
            sort(all(pt));
            bool ok = 0;
            for (auto x : pt) {
                auto it = p.find(x);
                if (it == p.end()) continue;
                a[++i] = last = x;
                p.erase(it);
                ok = 1;
                dbg(i, x);
                break;
            }
            if (!ok) return 0;
        }
        return 1;
    }
};

int main() {
#ifndef LOCAL
    cin.tie(nullptr)->sync_with_stdio(false);
#endif
    Main{}.main();
    return 0;
}