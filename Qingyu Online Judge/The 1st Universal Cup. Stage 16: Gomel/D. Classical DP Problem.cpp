#include <bits/stdc++.h>
using namespace std;

#define int long long

int a[5005], b[5005];
int n, k;
int dp[5005][5005], ans;

const int mod = 998244353;

void solve()
{
    int t = a[k + 1];
    memset(dp, 0, sizeof dp);
    dp[0][0] = 1;
    for (int i = 1; i <= k; i++)
    {
        for (int j = 0; j <= t; j++)
        {
            dp[i][j] = dp[i - 1][j] * (a[i] - t + j) % mod;
            if (j)
            {
                dp[i][j] += dp[i - 1][j - 1] * (t - j + 1) % mod;
                dp[i][j] %= mod;
            }
        }
    }
    ans += dp[k][t];
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        k = max(k, min(a[i], n - i + 1));
        b[i] = a[i];
    }
    reverse(a + 1, a + n + 1);
    solve();
    for (int i = 1; i <= n; i++)
        a[i] = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= b[i]; j++)
        {
            a[j]++;
        }
    }
    solve();
    int o = 1;
    for (int i = 1; i <= k; i++)
        o = o * i % mod;
    cout << k << ' ' << (ans + mod - o) % mod << '\n';
}