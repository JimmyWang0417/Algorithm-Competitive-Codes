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
constexpr auto lowbit = [](int x)
{
    return x & (-x);
};
struct Main
{
    int n;
    vector<int> a;
    vector<vector<vector<array<i64, 2>>>> dp;
    Main()
    {
        cin >> n;
        a.resize(n);
        dp.resize(n, vector<vector<array<i64, 2>>>(n));
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
            {
                int x;
                cin >> x;
                a[i] |= x << j;
            }
        for (int i = 0; i < n; ++i)
            for (int j = i; j < n; ++j)
                dp[i][j].resize(1 << (j - i));
        for (int i = 0; i < n; ++i)
            dp[i][i][0][1] = 1;
        for (int len = 2; len <= n; ++len)
            for (int i = 0, j; (j = i + len - 1) < n; ++i)
            {
                int mask = a[j] >> i;
                for (int S = 0; S < (int)dp[i][j - 1].size(); ++S)
                {
                    int M = S | (1 << (len - 2));
                    for (int T = M & mask; T; T ^= lowbit(T))
                    {
                        int t = __lg(lowbit(T));
                        int U = M & ((1 << (t + 1)) - 1);
                        if (t == len - 2)
                        {
                            dp[i][j][U][0] += dp[i][j - 1][S][0];
                            dp[i][j][U][1] += dp[i][j - 1][S][1];
                        }
                        else
                            dp[i][j][U][0] += dp[i][j - 1][S][0] + dp[i][j - 1][S][1];
                    }
                }
                for (int k = i; k < j - 1; ++k)
                {
                    array<i64, 2> sum{};
                    for (int S = 0; S < (int)dp[i][k].size(); ++S)
                    {
                        int cnt = __builtin_popcount(S & mask);
                        sum[0] += (dp[i][k][S][0] + dp[i][k][S][1]) * cnt;
                        if ((a[j] >> k) & 1)
                        {
                            sum[0] += dp[i][k][S][0];
                            sum[1] += dp[i][k][S][1];
                        }
                    }
                    for (int T = 0; T < (int)dp[k + 1][j].size(); ++T)
                    {
                        i64 v = dp[k + 1][j][T][1];
                        int U = T << (k + 1 - i);
                        dp[i][j][U][0] += sum[0] * v;
                        dp[i][j][U][1] += sum[1] * v;
                    }
                }
            }
        vector<i64> f(n + 1);
        f[0] = 1;
        for (int i = 0; i < n; ++i)
        {
            for (int j = i; j < n; ++j)
                for (auto _ : dp[i][j])
                    for (auto v : _)
                        f[j + 1] += f[i] * v;
        }
        cout << f[n] << '\n';
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