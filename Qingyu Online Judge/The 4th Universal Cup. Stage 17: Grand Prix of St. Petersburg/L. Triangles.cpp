#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>
using namespace std;
typedef int64_t i64;
typedef uint64_t u64;
typedef __int128_t i128;
typedef __uint128_t u128;
typedef __float80 f80;
typedef __float128 f128;
constexpr int mod = 1e6 + 3;
template <typename T = int>
constexpr auto quickpow(i64 a, T b = mod - 2)
{
    a %= mod;
    i64 res = 1;
    while (b)
    {
        if (b & 1)
            (res *= a) %= mod;
        (a *= a) %= mod;
        b >>= 1;
    }
    return res;
}
struct Main
{
    int n;
    vector<pair<int, int>> a;
    vector<pair<int, int>> b;
    vector<int> g[3][3];
    vector<pair<int, int>> X, Y;
    Main()
    {
        cin >> n;
        a.resize(n), b.resize(n);
        for (auto &[x, y] : a)
            cin >> x >> y;
        for (int i = 0; i < n; ++i)
        {
            X.emplace_back(a[i].first, i);
            Y.emplace_back(a[i].second, i);
        }
        ranges::sort(X);
        ranges::sort(Y);
        for (int j = 0; j < 3; ++j)
            for (int i = j * (n / 3); i < (j + 1) * (n / 3); ++i)
            {
                b[X[i].second].first = j;
                b[Y[i].second].second = j;
            }
        for (int i = 0; i < n; ++i)
            g[b[i].first][b[i].second].push_back(i);
        array<int, 3> p{0, 1, 2};
        vector<tuple<int, int, int>> q;
        i64 sum = 0;
        do
        {
            while (!g[0][p[0]].empty() && !g[1][p[1]].empty() && !g[2][p[2]].empty())
            {
                int u = g[0][p[0]].back();
                int v = g[1][p[1]].back();
                int w = g[2][p[2]].back();
                g[0][p[0]].pop_back();
                g[1][p[1]].pop_back();
                g[2][p[2]].pop_back();
                auto minY = min({a[u].second, a[v].second, a[w].second});
                auto maxY = max({a[u].second, a[v].second, a[w].second});
                sum += 2 * ((a[w].first - a[u].first) + (maxY - minY));
                q.emplace_back(u, v, w);
            }
        } while (next_permutation(p.begin(), p.end()));
        cout << sum << '\n';
        for (auto [u, v, w] : q)
            cout << u + 1 << ' ' << v + 1 << ' ' << w + 1 << '\n';
    }
};
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--)
        Main();
    return 0;
}
