#include <bits/stdc++.h>
using namespace std;
constexpr int N = 5000 + 5;
constexpr int mod = 998244353;
typedef long long ll;
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
int n;
ll fac[N], ifac[N];
inline ll C(int _n, int _m)
{
    if (_m < 0 || _n < _m)
        return 0;
    return fac[_n] * ifac[_m] % mod * ifac[_n - _m] % mod;
}
vector<int> G[N];
int sze[N];
ll f[N];
inline void dfs1(int u)
{
    f[u] = 1;
    for (int v : G[u])
    {
        dfs1(v);
        sze[u] += sze[v];
        (f[u] *= f[v] * C(sze[u], sze[v]) % mod) %= mod;
    }
    ++sze[u];
}
ll g[N][N];
inline void dfs2(int u)
{
    for (int v : G[u])
    {
        ll sum = 0;
        ll times = f[u] * quickpow(f[v] * C(sze[u] - 1, sze[v]) % mod, mod - 2) % mod;
        for (int i = 1; i <= n; ++i)
        {
            (sum += g[u][i - 1] * C(n - i + 1 - sze[v], sze[u] - sze[v] - 1)) %= mod;
            (g[v][i] += sum * times) %= mod;
        }
        dfs2(v);
    }
}
inline void _main()
{
    cin >> n;
    for (int i = 2; i <= n; ++i)
    {
        int _fa;
        cin >> _fa;
        G[_fa].push_back(i);
    }
    fac[0] = 1;
    for (int i = 1; i <= n; ++i)
        fac[i] = fac[i - 1] * i % mod;
    ifac[n] = quickpow(fac[n], mod - 2);
    for (int i = n; i >= 1; --i)
        ifac[i - 1] = ifac[i] * i % mod;
    dfs1(1);
    g[1][1] = 1;
    dfs2(1);
    for (int i = 1; i <= n; ++i)
        cout << g[i][i] * f[i] % mod * C(n - i, sze[i] - 1) % mod << ' ';
    cout << '\n';
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int test = 1;
    while (test--)
        _main();
    return 0;
}