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
constexpr int mod = 998244353;
struct matrix
{
    vector<vector<i64>> g;
    matrix() = default;
    matrix(int n) : g(n, vector<i64>(n, LONG_LONG_MIN / 2)) {}
    static matrix I(int n)
    {
        matrix res(n);
        for (int i = 0; i < n; ++i)
            res.g[i][i] = 0;
        return res;
    }
    auto friend operator*(const matrix &lhs, const matrix &rhs)
    {
        int n = (int)lhs.g.size();
        matrix res(n);
        for (int i = 0; i < n; ++i)
            for (int k = 0; k < n; ++k)
                for (int j = 0; j < n; ++j)
                    res.g[i][j] = max(res.g[i][j], lhs.g[i][k] + rhs.g[k][j]);
        return res;
    }
    auto pow(int b) const
    {
        int n = (int)g.size();
        matrix res = I(n), a = (*this);
        while (b)
        {
            if (b & 1)
                res = res * a;
            a = a * a;
            b >>= 1;
        }
        return res;
    }
    auto friend &operator<<(ostream &out, matrix &rhs)
    {
        for (const auto &i : rhs.g)
        {
            for (auto j : i)
                out << (j < 0 ? -1 : j) << ' ';
            out << '\n';
        }
        return out;
    }
};
struct Main
{
    int n, m, k, r;
    vector<int> a, b;
    Main()
    {
        cin >> n >> m >> k >> r;
        a.resize(n), b.resize(n);
        vector<int> suma(1 << n), sumb(1 << n);
        for (int i = 0; i < n; ++i)
        {
            cin >> a[i] >> b[i];
            for (int j = 0; j < (1 << i); ++j)
            {
                suma[(1 << i) | j] = a[i] + suma[j];
                sumb[(1 << i) | j] = b[i] + sumb[j];
            }
        }
        matrix base(1 << n);
        for (int s = 0; s < (1 << n); ++s)
            for (int t = 0; t < (1 << n); ++t)
            {
                if (m >= __builtin_popcount(s & t) * k + sumb[t])
                    base.g[s][t] = suma[t];
            }
        auto res = base.pow(r);
        i64 ans = LONG_LONG_MIN;
        for (int i = 0; i < (1 << n); ++i)
            ans = max(ans, res.g[0][i]);
        cout << ans << '\n';
    }
};
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    cin >> T;
    while (T--)
        Main();
    return 0;
}
