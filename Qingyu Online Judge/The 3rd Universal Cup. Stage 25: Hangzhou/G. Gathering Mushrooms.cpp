#include <bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
constexpr int N = 2e5 + 5;
int n, m;
int p[N], a[N];
vector<int> g[N];
vector<int> cc[N], tcc[N];
bool vis[N], exist[N];
int dep[N];
int dp[N];
int cirlen;
inline void dfs(int u, int _fa)
{
    auto calc = [&](int col) -> ll
    {
        if ((int)tcc[col].size() >= m)
            return dep[u] - tcc[col][tcc[col].size() - m] + 1;
        else if (cc[col].size() == 0)
            return 1e18;
        else
            return dep[u] +
                   (ll)(m - (int)tcc[col].size() - 1) / cc[col].size() * cirlen +
                   cc[col][(m - (int)tcc[col].size() - 1) % cc[col].size()];
    };
    vis[u] = true;
    tcc[a[u]].push_back(dep[u]);
    dp[u] = (calc(a[u]) < calc(dp[_fa]) ? a[u] : dp[_fa]);
    for (int v : g[u])
    {
        if (vis[v])
            continue;
        dep[v] = dep[u] + 1;
        dfs(v, u);
    }
    tcc[a[u]].pop_back();
}
inline void find(int S)
{
    set<int> se;
    while (se.find(S) == se.end())
    {
        se.insert(S);
        S = p[S];
    }

    vector<int> col;
    cirlen = 0;
    int T = S;
    for (int u = S; !exist[u]; u = p[u])
    {
        exist[u] = true;
        cc[a[T = u]].push_back(++cirlen);
        col.push_back(a[u]);
    }

    sort(col.begin(), col.end());
    col.erase(unique(col.begin(), col.end()), col.end());
    ll res = 1e18;
    for (auto c : col)
    {
        ll now = (ll)(m - 1) / cc[c].size() * cirlen + cc[c][(m - 1) % cc[c].size()];
        if (now < res)
        {
            dp[0] = c;
            res = now;
        }
    }
    dfs(T, 0);
    for (auto c : col)
        cc[c].clear();
}
inline void _main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    for (int i = 1; i <= n; ++i)
        cin >> p[i];
    for (int i = 1; i <= n; ++i)
        g[p[i]].push_back(i);

    for (int i = 1; i <= n; ++i)
    {
        if (vis[i])
            continue;
        find(i);
    }

    ll ans = 0;
    for (int i = 1; i <= n; ++i)
        ans += (ll)i * dp[i];
    cout << ans << '\n';

    for (int i = 1; i <= n; ++i)
    {
        exist[i] = vis[i] = false;
        g[i].clear();
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    cin >> T;
    for (int cas = 1; cas <= T; ++cas)
        _main();
    return 0;
}