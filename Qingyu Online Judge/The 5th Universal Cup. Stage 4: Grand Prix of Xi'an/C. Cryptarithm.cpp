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
constexpr int mod = 1e9 + 7;
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
struct Main
{
    int n, m, X, Y, Z;
    vector<vector<i64>> dp;
    vector<int> a, b;
    Main()
    {
        cin >> n >> m >> X >> Y >> Z;
        a.resize(n), b.resize(m);
        for (auto &i : a)
            cin >> i;
        for (auto &i : b)
            cin >> i;
        dp.resize(m + 1, vector<i64>(n + 1, LLONG_MAX / 2));
        dp[0][0] = X;
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                dp[i + 1][j + 1] = min(dp[i + 1][j + 1], dp[i][j] + (i64)abs(b[i] - a[j]) * Y);
                dp[i][j + 1] = min(dp[i][j + 1], dp[i][j] + Z);
            }
            dp[i][0] = min(dp[i][0], dp[i][n] + X);
            for (int j = 0; j < n; ++j)
            {
                dp[i + 1][j + 1] = min(dp[i + 1][j + 1], dp[i][j] + (i64)abs(b[i] - a[j]) * Y);
                dp[i][j + 1] = min(dp[i][j + 1], dp[i][j] + Z);
            }
        }
        for (int j = 0; j < n; ++j)
            dp[m][j + 1] = min(dp[m][j + 1], dp[m][j] + Z);
        // for (int i = 0; i <= m; ++i)
        // {
        //     for (int j = 0; j <= n; ++j)
        //         cout << dp[i][j] << ' ';
        //     cout << '\n';
        // }
        cout << dp[m][n] << '\n';
    }
};
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    // init(100);
    int T = 1;
    cin >> T;
    while (T--)
        Main();
    return 0;
}
