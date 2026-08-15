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
struct Main
{
    int n, m;
    struct node
    {
        int a, b, c, d, e, p;
    };
    vector<node> arr;
    Main()
    {
        cin >> n >> m;
        arr.resize(n);
        for (auto &[a, b, c, d, e, p] : arr)
            cin >> a >> b >> c >> d >> e >> p;
        vector dp(n + 5, vector(4, vector<long double>(m + 5, -1e18)));
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j <= m; ++j)
                dp[n][i][j] = 0;
        for (int i = n - 1; i >= 0; --i)
        {
            auto [a, b, c, d, e, p] = arr[i];
            for (int j = 0; j < 4; ++j)
                for (int k = 0; k <= m; ++k)
                {
                    if (j == 3)
                    {
                        if (k + b <= m)
                            dp[i][j][k] = max(dp[i][j][k], a + dp[i + 1][j][k + b]);
                        if (k + d + e <= m)
                            dp[i][j][k] = max(dp[i][j][k], c + dp[i + 1][0][k + d + e]);
                    }
                    else
                    {
                        if (k + b <= m)
                        {
                            if ((p == 0 || dp[i + 1][j | 1][k + b] >= 0) &&
                                (p == 100 || dp[i + 1][j | 2][k + b] >= 0))
                                dp[i][j][k] = max(dp[i][j][k], a + p / 100.0 * dp[i + 1][j | 1][k + b] +
                                                                   (1 - p / 100.0) * dp[i + 1][j | 2][k + b]);
                        }
                        if (k + d <= m)
                        {
                            if ((p == 0 || dp[i + 1][j | 1][k + d] >= 0) &&
                                (p == 100 || dp[i + 1][j | 2][k + d] >= 0))
                                dp[i][j][k] = max(dp[i][j][k], c + p / 100.0 * dp[i + 1][j | 1][k + d] +
                                                                   (1 - p / 100.0) * dp[i + 1][j | 2][k + d]);
                        }
                    }
                }
        }
        if (dp[0][0][0] >= 0)
            cout << fixed << setprecision(9) << dp[0][0][0] << '\n';
        else
            cout << -1 << '\n';
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
