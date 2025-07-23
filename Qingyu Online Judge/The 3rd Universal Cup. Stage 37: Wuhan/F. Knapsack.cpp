#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr int N = 5005;
constexpr int mod = 998244353;
int n, m;
inline ll quickpow(ll a, int b)
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
map<int, ll> mp;
inline void _main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
    {
        int a, b;
        cin >> a >> b;
        mp[b] += a;
    }
    int las = 1e9;
    ll leaf = 0, ans = 0;
    for (auto it = mp.rbegin(); it != mp.rend(); ++it)
    {
        auto [a, b] = *it;
        // cout << a << ' ' << b << '\n';
        if (pow(2, las - a) * leaf > 1e18)
            break;
        leaf <<= las - a;
        if (leaf >= b)
            leaf -= b;
        else
        {
            ll x = b - leaf;
            (ans += (x + m - 1) / m % mod * quickpow(2, a)) %= mod;
            leaf = (m - x % m) % m;
        }
        las = a;
    }
    cout << ans << '\n';
    mp.clear();
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