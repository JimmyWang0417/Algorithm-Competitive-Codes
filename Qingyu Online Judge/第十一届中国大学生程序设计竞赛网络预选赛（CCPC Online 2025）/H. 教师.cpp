#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
typedef int64_t i64;
typedef uint64_t u64;
typedef __int128_t i128;
typedef __uint128_t u128;
typedef __float80 f80;
typedef __float128 f128;
constexpr int mod = 998244353;
typedef complex<double> p2;
constexpr auto pi = M_PI;
auto cross(p2 x, p2 y)
{
    return (conj(x) * y).imag();
}
auto rotate(p2 x, double angle)
{
    return x * polar(1.0, angle);
}
struct Main
{
    Main()
    {
        int n, m, k, T;
        cin >> n >> m >> k >> T;
        vector a(n, vector<int>(k + 1));
        for (int i = 0; i < n; ++i)
            for (int j = 0; j <= k; ++j)
                cin >> a[i][j];
        vector dp(T + 1, vector<i64>(1 << n));
        for (int S = 0; S < (1 << n); ++S)
        {
            int res = 0;
            for (int i = 0; i < n; ++i)
                if ((S >> i) & 1)
                    res += a[i][0];
            for (int i = 0; i <= T; ++i)
                dp[i][S] = res;
        }
        for (int _ = 0; _ < m; ++_)
        {
            int h, t;
            cin >> h >> t;
            vector<int> b(n);
            for (int i = 0; i < h; ++i)
            {
                int x, y;
                cin >> x >> y;
                --x;
                b[x] = a[x][y];
            }
            for (int i = T - t; i >= 0; --i)
            {
                auto g = dp[i];
                for (int j = 0; j < n; ++j)
                    for (int S = 0; S < (1 << n); ++S)
                        if (((S >> j) & 1) == 0)
                            g[S | (1 << j)] = max(g[S | (1 << j)], g[S] + b[j]);

                for (int S = 0; S < (1 << n); ++S)
                    dp[i + t][S] = max(dp[i + t][S], g[S]);
            }
        }
        for (int i = 1; i <= T; ++i)
            cout << dp[i][(1 << n) - 1] << '\n';
    }
};
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--)
        Main();
    return 0;
}