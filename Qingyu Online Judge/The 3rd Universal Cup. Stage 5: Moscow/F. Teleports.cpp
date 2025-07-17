#include <bits/stdc++.h>
using namespace std;

#define int long long

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> tip(n + 1);
    for (int i = 1; i <= n; ++i)
    {
        cin >> tip[i];
    }
    vector<int> f(n + 5);
    vector dp(n + 5, vector<int>(n + 5));
    for (int d = 1; d < n; ++d)
    {
        for (int l = 1; l + d <= n; ++l)
        {
            int r = l + d;
            f[l] = 4e18;
            int k = r / 2;
            for (int i = l / 2 + 1; i <= k; ++i)
            {
                f[l] = min(f[l], max(dp[1][i * 2 - l], dp[i * 2][r]) + tip[i]);
            }
            k = (n + r) / 2;
            for (int i = (n + l) / 2 + 1; i <= k; ++i)
            {
                f[l] = min(f[l], max(dp[i * 2 - r][n], dp[l][2 * i - n - 1]) + tip[i]);
            }
        }
        vector<int> b(n + 5);
        for (int ii = 1; ii <= n - d + 1; ++ii)
        {
            int k = 0;
            for (int i = n - d + 1; i; --i)
            {
                if (!b[i])
                {
                    if (k == 0 || f[i] < f[k])
                        k = i;
                }
            }
            b[k] = 1;
            int l = k, r = k + d, o = (n + l) / 2;
            for (int i = r / 2 + 1; i <= o; ++i)
                f[i * 2 - r] = min(f[i * 2 - r], f[l] + tip[i]);
        }
        for (int i = 1; i <= n - d + 1; ++i)
            dp[i][i + d] = f[i];
    }
    cout << dp[1][n] << '\n';
}