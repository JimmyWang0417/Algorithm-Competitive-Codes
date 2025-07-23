#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr int N = 1e6 + 5;
constexpr int mod = 998244353;
inline ll quickpow(ll a, int b = mod - 2)
{
    ll res = 1;
    while (b)
    {
        if (b & 1)
            (res *= a) %= mod;
        (a *= a) %= mod;
        b >>= 1;
    }
    return res;
}
int n, m;
vector<pair<int, ll>> f[N], g[N];
ll dp[N], h[N];
ll c[N];
inline void _main()
{
    cin >> m >> n;
    for (int i = 1; i <= m; ++i)
    {
        int l, r, p, q;
        cin >> l >> r >> p >> q;
        f[l].emplace_back(r, p * quickpow(q) % mod);
        g[r].emplace_back(l, p * quickpow(q) % mod);
    }
    ll times = 1;
    dp[0] = 1;
    h[0] = 1;
    for (int i = 1; i <= n; ++i)
    {
        for (auto [r, j] : f[i])
            (times *= (1 - j)) %= mod;
        for (auto [l, j] : g[i])
            (dp[i] += dp[l - 1] * j % mod * quickpow(1 - j) % mod * times % mod * h[l - 1]) %= mod;
        h[i] = h[i - 1];
        for (auto [r, j] : f[i])
            (h[i] *= quickpow(1 - j) % mod) %= mod;
    }
    cout << (dp[n] + mod) % mod << '\n';
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--)
        _main();
    return 0;
}