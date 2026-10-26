#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
constexpr int mod = 998244353;
template <typename T = int>
constexpr auto quickpow(i64 a, T b = mod - 2)
{
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
constexpr auto inv100 = quickpow(100);
struct Main
{
    int n, m, q = 0;
    vector<vector<i64>> a;
    vector<vector<int>> p;
    vector<vector<i64>> f;
    Main()
    {
        cin >> n >> m;
        a.resize(n);
        p.resize(n);
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                int x;
                cin >> x;
                if (x == -1)
                    p[i].emplace_back(a[i].size());
                else
                    a[i].emplace_back(x * inv100 % mod);
            }
            q += (int)p[i].size();
        }
        f.resize(n + 1, vector<i64>(q + 1));
        f[0][q] = 1;
        for (int t = 0; t < n; ++t)
        {
            int o = (int)p[t].size(), r = (int)a[t].size();
            p[t].emplace_back(0), a[t].emplace_back(1);
            vector<vector<i64>> g(q + 1, vector<i64>(o + 1));
            vector<vector<vector<i64>>> h(q + 1, vector<vector<i64>>(o + 1, vector<i64>(r + 1)));
            h[0][0][p[t][0]] = 1;
            for (int i = 0; i < q; ++i)
            {
                for (int j = 0; j < o; ++j)
                {
                    i64 now = 0;
                    for (int k = r; k >= 1; --k)
                    {
                        now = (now * a[t][k] + h[i][j][k]) % mod;
                        (h[i + 1][j][k] += now * (1 - a[t][k - 1])) %= mod;
                    }
                    {
                        now = (now * a[t][0] + h[i][j][0]) % mod;
                        (h[i + 1][j + 1][p[t][j + 1]] += now) %= mod;
                    }
                }
                (h[i + 1][o][p[t][o]] += h[i][o][p[t][o]]) %= mod;
            }
            for (int i = 0; i <= q; ++i)
                for (int j = 0; j <= o; ++j)
                    for (int k = 0; k <= r; ++k)
                        (g[i][j] += h[i][j][k]) %= mod;
            // for (int i = 0; i <= q; ++i)
            // {
            //     for (int j = 0; j <= o; ++j)
            //         cerr << g[i][j] << ' ';
            //     cerr << '\n';
            // }
            // cerr << '\n';
            for (int i = 0; i <= q; ++i)
                for (int j = 0; j <= i && j <= o; ++j)
                    (f[t + 1][i - j] += f[t][i] * g[i][j]) %= mod;
        }
        i64 res = 0;
        for (int i = 0; i <= q; ++i)
            (res += f[n][i] * i) %= mod;
        cout << (res + mod) % mod << '\n';
    }
};
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--)
        Main{};
    return 0;
}
