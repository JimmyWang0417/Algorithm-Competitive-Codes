#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    vector<int> dp(n + 1, 1e18);
    dp[n] = 0;
    sort(a.begin() + 1, a.end());
    for (int i = n - 1; i >= 1; i--)
    {
        for (int j = 2; j <= 20; j++)
        {
            int pos = lower_bound(a.begin() + i, a.end(), a[i] * j) - a.begin() - 1;
            if (pos >= 1 && pos <= n)
                dp[i] = min(dp[i], dp[pos] + a[pos] / a[i]);
        }
        dp[i] = min(dp[i], dp[i + 1] + a[i + 1] / a[i]);
    }
    cout << dp[1] << "\n";
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    while (t--)
    {
        solve();
    }
}
// 1 2 4 3
// 3 4 2 1