#pragma GCC optimize(2)
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
constexpr int N = 5e5 + 5;
using i64 = int64_t;
int n, m, k;
int f[21][N], g[21][N];
struct Main {
    vector<int> a;
    auto check(i64 mid) {
        i64 sum = 0;
        memset(f, 0, sizeof(f));
        memset(g, 0, sizeof(g));
        for (int i = 0, j = 0; i < n; ++i) {
            if (i == j) {
                sum += a[j];
                j = (j + 1) % n;
            }
            while (i != j && sum + a[j] <= mid) {
                sum += a[j];
                j = (j + 1) % n;
            }
            sum -= a[i];
            f[0][i] = j, g[0][i] = (j - i + 2 * n - 1) % n + 1;
        }
        for (int j = 0; j < 20; ++j)
            for (int i = 0; i < n; ++i) {
                f[j + 1][i] = f[j][f[j][i]];
                g[j + 1][i] = min(g[j][i] + g[j][f[j][i]], n);
            }
        for (int i = 0; i < n; ++i) {
            int res = 0;
            int u = i;
            for (int j = 0; j < 20; ++j)
                if ((k >> j) & 1)
                {
                    res = min(n, res + g[j][u]);
                    u = f[j][u];
                }
            if (res >= n)
                return true;
        }
        return false;
    }
    void main() {
        cin >> n >> m >> k;
        a.resize(n);
        for (auto &i : a)
            cin >> i;
        i64 sum = accumulate(a.begin(), a.end(), (i64)0);
        i64 maxx = *max_element(a.begin(), a.end());
        // for (int i = 1; i <= 20; ++i)
        //     cout << check(i) << ' ';
        // cout << '\n';
        i64 l = maxx, r = sum;
        while (l <= r)
        {
            auto mid = (l + r) >> 1;
            if (check(mid))
                r = mid - 1;
            else
                l = mid + 1;
        }
        auto ans = l * (m - 1) + sum;
        cout << ans << '\n';
    }
};
int main() {
    // freopen("J.in", "r", stdin);
#ifndef LOCAL
    cin.tie(nullptr)->sync_with_stdio(false);
#endif
    int T = 1;
    // cin >> T;
    while (T--)
        Main{}.main();
    return 0;
}
