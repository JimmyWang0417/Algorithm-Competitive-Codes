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
    vector<int> c;
    vector<int> dep;
    vector<vector<int>> g;
    vector<array<int, 23>> fa;
    vector<array<i64, 23>> af;
    vector<i64> dp, first, second;
    auto dfs1(int u, int _fa) -> void
    {
        first[u] = second[u] = LONG_LONG_MAX / 2;
        dp[u] = c[u];
        for (int v : g[u])
        {
            if (v == _fa)
                continue;
            dfs1(v, u);
            if (dp[v] < first[u])
            {
                second[u] = first[u];
                first[u] = dp[v];
            }
            else if (dp[v] < second[u])
                second[u] = dp[v];
        }
        dp[u] = min(dp[u], first[u] + second[u]);
    }
    auto dfs2(int u, int _fa) -> void
    {
        dep[u] = dep[fa[u][0] = _fa] + 1;
        if (_fa)
            af[u][0] = (first[_fa] == dp[u] ? second[_fa] : first[_fa]);
        for (int i = 0; i < 19; ++i)
        {
            fa[u][i + 1] = fa[fa[u][i]][i];
            af[u][i + 1] = af[u][i] + af[fa[u][i]][i];
        }
        for (int v : g[u])
        {
            if (v == _fa)
                continue;
            dfs2(v, u);
        }
    }
    auto calc(int x, int y) -> i64
    {
        int k = dep[x] - dep[y];
        if (k < 0)
            return -1;
        i64 res = 0;
        for (int i = 19; i >= 0; --i)
            if ((k >> i) & 1)
            {
                res += af[x][i];
                x = fa[x][i];
            }
        if (x == y)
            return res;
        else
            return -1;
    }
    Main()
    {
        int n, m;
        cin >> n >> m;
        c.resize(n + 5);
        dp.resize(n + 5), first.resize(n + 5), second.resize(n + 5);
        g.resize(n + 5);
        dep.resize(n + 5);
        fa.resize(n + 5), af.resize(n + 5);
        for (int i = 1; i <= n; ++i)
            cin >> c[i];
        for (int i = 1; i < n; ++i)
        {
            int x, y;
            cin >> x >> y;
            g[x].push_back(y);
            g[y].push_back(x);
        }
        dfs1(1, 0);
        dfs2(1, 0);
        for (int i = 1; i <= m; ++i)
        {
            int x, y;
            cin >> x >> y;
            cout << calc(x, y) << '\n';
        }
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
