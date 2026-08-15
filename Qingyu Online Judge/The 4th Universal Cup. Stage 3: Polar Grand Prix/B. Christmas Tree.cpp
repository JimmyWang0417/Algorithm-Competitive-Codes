#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>
using namespace std;
typedef int64_t i64;
typedef uint64_t u64;
typedef __int128_t i128;
typedef __uint128_t u128;
typedef __float80 f80;
typedef __float128 f128;
constexpr int mod = 998244353;
struct Main
{
    int n;
    vector<int> sze;
    vector<i64> a;
    vector<vector<int>> G;
    vector<vector<i64>> U, D;
    auto dfs(int u, int _fa) -> void
    {
        sze[u] = 1;
        for (int v : G[u])
        {
            if (v == _fa)
                continue;
            dfs(v, u);
            sze[u] += sze[v];
        }
        D[u].assign(sze[u] + 1, LLONG_MAX / 2);
        U[u].assign(n + 5, LLONG_MAX / 2);
        for (int i = 1; i <= n; ++i)
        {
            vector<i64> f = {0};
            for (int v : G[u])
            {
                if (v == _fa)
                    continue;
                vector<i64> g((int)f.size() + sze[v], LLONG_MAX / 2);
                for (int j = 0; j < (int)f.size(); ++j)
                {
                    g[j] = min(g[j], f[j] + U[v][i]);
                    for (int k = 0; k <= sze[v]; ++k)
                        g[j + k] = min(g[j + k], f[j] + D[v][k]);
                }
                f = move(g);
            }
            if (i <= sze[u])
                D[u][i] = f[i - 1] + a[u] * i;
            for (int j = 0; j < (int)f.size() && j < i - 1; ++j)
                U[u][i - j - 1] = min(U[u][i - j - 1], f[j] + a[u] * i);
        }
    }
    Main()
    {
        cin >> n;
        a.resize(n + 5);
        for (int i = 1; i <= n; ++i)
            cin >> a[i];
        G.resize(n + 5);
        for (int i = 1; i < n; ++i)
        {
            int u, v;
            cin >> u >> v;
            G[u].push_back(v);
            G[v].push_back(u);
        }
        sze.resize(n + 5);
        U.resize(n + 5), D.resize(n + 5);
        dfs(1, 0);
        i64 res = LLONG_MAX;
        for (int i = 1; i <= n; ++i)
            res = min(res, D[1][i]);
        cout << res << '\n';
    }
};
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    cin >> T;
    while (T--)
        Main();
    return 0;
}

