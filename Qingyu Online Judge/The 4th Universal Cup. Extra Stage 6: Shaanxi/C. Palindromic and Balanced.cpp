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
    string s;
    vector<array<int, 2>> nxt, pre;
    vector<vector<int>> dp;
    Main()
    {
        cin >> n;
        cin >> s;
        pre.resize(n + 5), nxt.resize(n + 5);
        pre[0] = {0, 0};
        for (int i = 1; i <= n; ++i)
        {
            pre[i] = pre[i - 1];
            pre[i][s[i - 1] == ')'] = i;
        }
        nxt[n + 1] = {n + 1, n + 1};
        for (int i = n; i >= 1; --i)
        {
            nxt[i] = nxt[i + 1];
            nxt[i][s[i - 1] == ')'] = i;
        }
        dp.resize(n + 5, vector<int>(n + 5));
        int res = 0;
        for (int i = n + 1; i >= 1; --i)
            for (int j = i - 1; j <= n; ++j)
            {
                if (1 <= pre[i - 1][0] && nxt[j + 1][1] <= n)
                    res = max(res, dp[i][j] * 4 + 2);
                if (1 <= pre[i - 1][0] && nxt[j + 1][0] <= n)
                {
                    int x = pre[pre[i - 1][0] - 1][1];
                    int y = nxt[nxt[j + 1][0] + 1][1];
                    if (1 <= x && y <= n)
                        dp[x][y] = max(dp[x][y], dp[i][j] + 1);
                }
                if (1 <= pre[i - 1][1] && nxt[j + 1][1] <= n)
                {
                    int x = pre[pre[i - 1][1] - 1][0];
                    int y = nxt[nxt[j + 1][1] + 1][0];
                    if (1 <= x && y <= n)
                        dp[x][y] = max(dp[x][y], dp[i][j] + 1);
                }
            }
        cout << res << '\n';
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
