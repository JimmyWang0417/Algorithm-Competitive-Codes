#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr int N = 2e5 + 5;
constexpr int mod = 998244353;
int dp[705][N];
inline void init()
{
    dp[0][0] = 1;
    for (int i = 1; i <= 700; ++i)
    {
        for (int j = 0; j < i; ++j)
            dp[i][j] = dp[i - 1][j];
        for (int j = i; j <= N - 5; ++j)
            dp[i][j] = (dp[i - 1][j] + dp[i][j - i]) % mod;
    }
}
int n, m;
map<ll, int> mp[N];
int cnt[N];
inline void _main()
{
    cin >> n >> m;
    if (n == 1)
    {
        cout << m << '\n';
        return;
    }
    if ((ll)n * (n + 1) / 2 - 1 > m)
    {
        cout << 0 << '\n';
        return;
    }
    ll ans = 0;
    for (int i = n * (n + 1) / 2 - 1; i <= m; ++i)
        (ans += (ll)(m - i + 1) * dp[n - 1][i - n * (n + 1) / 2 + 1]) %= mod;
    cout << ans << '\n';
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    init();
    int T = 1;
    cin >> T;
    while (T--)
        _main();
    return 0;
}