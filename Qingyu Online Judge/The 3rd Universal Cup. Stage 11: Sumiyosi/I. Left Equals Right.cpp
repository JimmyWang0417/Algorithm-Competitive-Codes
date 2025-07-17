#include <bits/stdc++.h>
using namespace std;

#define mod 998244353
#define int long long

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> tip(n + 1);
    int sum = 0;
    for (int i = 1; i <= n; i++)
    {
        cin >> tip[i];
        sum += tip[i];
    }

    if (sum % 2)
    {
        cout << 0 << "\n";
        return 0;
    }
    vector<vector<int>> dp(sum / 2 + 1, vector<int>(n + 1));
    dp[0][0]++;
    vector<int> ok(sum / 2 + 1);
    ok[0] = 1;
    for (int i = 1; i <= n; i++)
    {
        for (int j = sum / 2; j >= tip[i]; j--)
        {
            if (ok[j - tip[i]])
            {
                ok[j] = 1;
                for (int k = 0; k <= n; k++)
                {
                    if (dp[j - tip[i]][k])
                    {
                        dp[j][k + 1] += dp[j - tip[i]][k];
                        dp[j][k + 1] %= mod;
                    }
                }
            }
        }
    }

    int ans = 0;
    for (int x = 1; x <= n; x++)
    {
        if (dp[sum / 2][x])
        {
            int o = 1;
            for (int i = x; i >= 1; i--)
            {
                o *= i;
                o %= mod;
            }
            for (int i = n - x; i >= 1; i--)
            {
                o *= i;
                o %= mod;
            }
            ans += o * dp[sum / 2][x] % mod;
            ans %= mod;
        }
    }

    cout << ans << "\n";
}