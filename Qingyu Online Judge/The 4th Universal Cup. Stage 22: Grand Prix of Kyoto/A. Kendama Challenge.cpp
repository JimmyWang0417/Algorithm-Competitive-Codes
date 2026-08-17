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
    int n, k;
    vector<i64> p;
    Main()
    {
        cin >> n >> k;
        p.resize(n + 5);
        for (int i = 1; i <= n; ++i)
        {
            int a, b;
            cin >> a >> b;
            p[i] = a * quickpow(b) % mod;
        }
        vector<i64> pre(n + 5);
        pre[0] = 1;
        for (int i = 1; i <= n; ++i)
            pre[i] = pre[i - 1] * p[i] % mod;
        vector<array<i64, 2>> dp(n + 5);
        dp[0][0] = 1;
        i64 ans = 0;
        for (int i = 1; i <= n; ++i)
        {
            dp[i][0] = (dp[i - 1][0] + dp[i - 1][1]) * (1 - p[i]) % mod;
            dp[i][1] = (dp[i - 1][0] + dp[i - 1][1]) * p[i] % mod;
            if (i >= k)
            {
                auto _ = dp[i - k][0] * (pre[i] * quickpow(pre[i - k]) % mod) % mod;
                (dp[i][1] -= _) %= mod;
                (ans += _) %= mod;
            }
        }
        cout << (ans + mod) % mod << '\n';
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
