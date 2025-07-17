#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
typedef long long ll;
constexpr int N = 1e5 + 5;
constexpr int mod = 998244353;
constexpr int inv2 = (mod + 1) / 2;
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
struct Edge
{
    int next, to;
} edge[N * 2];
int head[N], num_edge;
inline void add_edge(int from, int to)
{
    edge[++num_edge].next = head[from];
    edge[num_edge].to = to;
    head[from] = num_edge;
}
int sze[N];
ll f[N];
inline void init(int u, int _fa)
{
    f[u] = 0;
    sze[u] = 1;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int v = edge[i].to;
        if (v == _fa)
            continue;
        init(v, u);
        (f[u] += (ll)sze[u] * sze[v]) %= mod;
        sze[u] += sze[v];
    }
    f[u] = (f[u] * 2 + 1) % mod;
}
ll gx2[N], gx[N], g[N], h[N];
inline void dfs(int u, int _fa)
{
    h[u] = 0;
    gx2[u] = gx[u] = g[u] = 0;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int v = edge[i].to;
        if (v == _fa)
            continue;
        dfs(v, u);
        ll vx2 = (gx2[v] + 2 * gx[v] + g[v]) % mod, vx = (gx[v] + g[v]) % mod;
        (h[u] += gx2[u] * g[v] + vx2 * g[u] + 2 * gx[u] * vx + vx2 * (f[u] - (ll)2 * (sze[u] - sze[v]) * sze[v] % mod + (ll)2 * (sze[u] - sze[v]) * (n - sze[u]) % mod)) %= mod;
        (gx2[u] += vx2) %= mod;
        (gx[u] += vx) %= mod;
        (g[u] += g[v]) %= mod;
        (h[u] += h[v]) %= mod;
    }
    g[u] += f[u];
}
inline void work()
{
    cin >> n;
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        cin >> u >> v;
        add_edge(u, v);
        add_edge(v, u);
    }
    ll all = (ll)n * n % mod * (n - 1) % mod * (n - 1) % mod * inv2 % mod * inv2 % mod;
    init(1, 0);
    dfs(1, 0);
    cout << h[1] * quickpow(all, mod - 2) % mod << '\n';
    num_edge = 0;
    for (int i = 1; i <= n; ++i)
        head[i] = 0;
}
signed main()
{
    //	freopen("project.in", "r", stdin);
    //	freopen("project.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    cin >> T;
    while (T--)
        work();
    return 0;
}