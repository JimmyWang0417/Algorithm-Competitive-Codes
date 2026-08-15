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
struct Main
{
    vector<int> sum, dp;
    int n, m, k;
    map<int, vector<int>> g;
    Main()
    {
        cin >> n >> k >> m;
        sum.resize(1 << k), dp.resize(1 << k);
        for (int c, i = 0; i < k; i++)
        {
            cin >> c;
            for (int j = 1; j <= c; j++)
            {
                int l, r;
                cin >> l >> r;
                g[l].push_back(i);
                g[r + 1].push_back(i);
            }
        }
        int S = 0, pre = 0;
        for (auto [p, a] : g)
        {
            if (__builtin_popcount(S) >= 2)
                sum[S] += p - pre;
            for (auto i : a)
                S ^= 1 << i;
            pre = p;
        }
        for (int i = 0; i < (1 << k); i++)
        {
            int t = sum[i], y = ((1 << k) - 1) ^ i;
            if (!t)
                continue;
            dp[(1 << k) - 1] += t;
            for (int j = 0; j < k; j++)
                if (i >> j & 1)
                    dp[y | 1 << j] -= t;
            dp[y] += (__builtin_popcount(i) - 1) * t;
        }
        for (int i = 0; i < k; i++)
            for (int j = 0; j < (1 << k); j++)
                if (j >> i & 1)
                    dp[j ^ 1 << i] += dp[j];
        i64 ans = 0;
        for (int i = 0; i < (1 << k); i++)
            ans += dp[i] >= m;
        cout << ans << '\n';
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
