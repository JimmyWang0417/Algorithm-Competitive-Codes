#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
    #define dbg(...) fprintf(stderr, ##__VA_ARGS__)
#else
    #define dbg(...) 42
#endif

#define all(x) (x).begin(), (x).end()
using LL = long long;

#define NO return void(cout << "NO\n")
struct Main {
    vector<LL> a, b, pt;
    LL K;
    void main() {
        a.assign(6, 0);
        for (auto &x : a) cin >> x;
        sort(all(a));
        cin >> K;
        pt = {0};
        pt.insert(pt.end(), all(a));
        b.assign(6, 0);
        if (!dfs(0, K)) NO;
        cout << "YES\n";
        for (auto x : b) cout << x << " ";
        cout << "\n";
    }
    bool dfs(int u, LL rest) {
        if (u == 6) {
            int cnt = 0;
            for (int i = 0; i < 6; ++i)
                for (int j = 0; j < 6; ++j) {
                    if (b[i] > a[j]) ++cnt;
                }
            return cnt >= 19;
        }
        if (u == 5 && rest >= 1) {
            b[u] = rest;
            if (dfs(u + 1, 0)) {
                return 1;
            }
        } else {
            for (auto x : pt) {
                ++x;
                if (rest >= x) {
                    b[u] = x;
                    if (dfs(u + 1, rest - x)) {
                        return 1;
                    }
                }
            }
        }
        return 0;
    }
};

int main() {
#ifndef LOCAL
    cin.tie(nullptr)->sync_with_stdio(false);
#endif
    Main{}.main();
    return 0;
}
