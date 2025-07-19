#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr int N = 3e5 + 5;
constexpr int mod = 998244353;
int n, m;
int a[N], b[N];
int power[N];
int sum[N];
ll dp[N];
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    for (int i = 1; i <= n; ++i)
        cin >> b[i];
    for (int i = 1; i <= n; ++i)
        sum[i] = sum[i - 1] + b[i];
    power[0] = 1;
    for (int i = 1; i <= n; ++i)
        power[i] = power[i - 1] * 2 % mod;
    for (int i = 0; i <= m; ++i)
        dp[i] = 1;
    ll ans = 0;
    for (int i = 1; i <= n; ++i)
    {
        (ans += power[n - i] * dp[m - b[i]] % mod * a[i]) %= mod;
        for (int j = m; j >= b[i]; --j)
            (dp[j] += dp[j - b[i]]) %= mod;
    }
    for (int i = 0; i <= m; ++i)
        dp[i] = 1;
    for (int i = n; i >= 1; --i)
    {
        if (sum[i] <= m)
            (ans += power[i - 1] * dp[m - sum[i]] % mod * a[i]) %= mod;
        for (int j = m; j >= b[i]; --j)
            (dp[j] += dp[j - b[i]]) %= mod;
    }
    cout << ans << '\n';
    return 0;
}