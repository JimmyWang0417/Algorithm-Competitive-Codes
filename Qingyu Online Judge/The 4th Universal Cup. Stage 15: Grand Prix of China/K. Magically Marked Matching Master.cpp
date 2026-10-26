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
    int n;
    vector<vector<int>> G;
    vector<bool> dp;
    auto dfs(int u, int _fa) -> int
    {
        int w = 0;
        for (auto v : G[u])
        {
            if (v == _fa)
                continue;
            int _w = dfs(v, u);
            if (!w && _w)
                w = _w;
        }
        if (w)
        {
            dp[w] = 1;
            return 0;
        }
        else
        {
            dp[u] = 0;
            return u;
        }
    }
    auto dfs1(int u, int _fa) -> void
    {
        dp[u] = dp[u] ^ dp[_fa];
        for (auto v : G[u])
        {
            if (v == _fa)
                continue;
            dfs1(v, u);
        }
    }
    Main()
    {
        cin >> n;
        G.resize(n + 5);
        for (int i = 1; i < n; ++i)
        {
            int u, v;
            cin >> u >> v;
            G[u].emplace_back(v);
            G[v].emplace_back(u);
        }
        dp.resize(n + 5);
        dfs(1, 0);
        dfs1(1, 0);
        for (int i = 2; i <= n; ++i)
            cout << dp[i];
        cout << '\n';
    }
};
struct Solve
{
    int n;
    vector<int> a;
    Solve()
    {
        cin >> n;
        string s;
        cin >> s;
        a.resize(n + 5);
        for (int i = 2; i <= n; ++i)
            a[i] = s[i - 2] - '0';
        for (int i = 1; i < n; ++i)
        {
            int u, v;
            cin >> u >> v;
            if (a[u] != a[v])
                cout << "take" << endl;
            else
                cout << "ignore" << endl;
        }
    }
};
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    // int T = 1;
    // // cin >> T;
    // while (T--)
    //     Main();
    string s;
    cin >> s;
    if (s == "prepare")
        Main();
    else
        Solve();
    return 0;
}
