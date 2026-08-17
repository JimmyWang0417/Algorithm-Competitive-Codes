#include <bits/stdc++.h>
using namespace std;
typedef int64_t i64;
typedef uint64_t u64;
typedef __int128_t i128;
typedef __uint128_t u128;
typedef __float128 f128;
auto _main()
{
    int n;
    cin >> n;
    vector<i64> a(n + 5);
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    vector<int> dp(n + 5, INT_MAX / 2);
    dp[0] = 0;
    for (int i = 1, r = 0; i <= n; ++i)
    {
        dp[i] = min(dp[i], dp[i - 1] + 1);
        dp[i + 1] = min(dp[i + 1], dp[i - 1] + 1);
        dp[i + 2] = min(dp[i + 2], dp[i - 1] + 1);
        if (i <= r - 2)
            continue;
        for (int j = i + 3; j <= n; ++j)
        {
            if (a[i + 2] - 2 * a[i + 1] + a[i] == a[j] - 2 * a[j - 1] + a[j - 2])
            {
                dp[j] = min(dp[j], dp[i - 1] + 1);
                r = max(r, j);
            }
            else
                break;
        }
    }
    cout << dp[n] << '\n';
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    cin >> T;
    while (T--)
        _main();
    return 0;
}
