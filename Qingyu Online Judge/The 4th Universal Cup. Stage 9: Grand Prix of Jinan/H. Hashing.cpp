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
struct Main
{
    int n, mod;
    vector<vector<i64>> dp;
    Main()
    {
        cin >> n >> mod;
        dp.resize(n + 5);
        dp[0].assign(n + 5, 1);
        for (int i = 1; i <= n; ++i)
        {
            dp[i].resize(n / i + 5);
            dp[i][0] = 1;
            for (int l = 0, r; r = i - l - 1, l < i && l <= r; ++l)
            {
                auto lasdp = dp[i];
                for (int j = 1; i * j <= n; ++j)
                    for (int k = 1; k <= j; ++k)
                    {
                        if (l == r)
                            (dp[i][j] += lasdp[j - k] * dp[l][2 * k]) %= mod;
                        else
                            (dp[i][j] += lasdp[j - k] * dp[l][k] % mod * dp[r][k]) %= mod;
                    }
            }
        }
        cout << dp[n][1] << '\n';
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
