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
constexpr int mod = 1e6 + 3;
template <typename T = int>
constexpr auto quickpow(i64 a, T b = mod - 2)
{
    a %= mod;
    i64 res = 1;
    while (b)
    {
        if (b & 1)
            (res *= a) %= mod;
        (a *= a) %= mod;
        b >>= 1;
    }
    return res;
}
struct Main
{
    int n, m;
    string s;
    vector<vector<int>> G;
    vector<int> d;
    auto dfs1(int u, int _fa) -> void
    {
        d[u] = s[u - 1] == '0' ? INT_MAX / 2 : 0;
        for (auto v : G[u])
        {
            if (v == _fa)
                continue;
            dfs1(v, u);
            d[u] = min(d[u], d[v] + 1);
        }
    }
    vector<int> dp;
    auto dfs2(int u, int _fa, int hp, int ans) -> void
    {
        dp[u] = ans + (s[u - 1] == '0');
        if (hp >= d[u])
            hp = max(hp, m - d[u]);
        if (hp == 0)
        {
            hp = m;
            ans++;
        }
        for (auto v : G[u])
        {
            if (v == _fa)
                continue;
            dfs2(v, u, hp - 1, ans);
        }
    }
    Main()
    {
        cin >> n >> m;
        cin >> s;
        G.resize(n + 5);
        for (int i = 1; i < n; ++i)
        {
            int u, v;
            cin >> u >> v;
            G[u].emplace_back(v);
            G[v].emplace_back(u);
        }
        d.resize(n + 5);
        dp.resize(n + 5);
        dfs1(1, 0);
        dfs2(1, 0, m, 0);
        for (int i = 2; i <= n; ++i)
            cout << dp[i] << ' ';
        cout << '\n';
    }
};
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    cin >> T;
    while (T--)
        Main();
    return 0;
}