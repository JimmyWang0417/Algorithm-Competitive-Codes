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
    vector<pair<int, int>> path;
    auto dfs(int u, int _fa) -> int
    {
        vector<int> p;
        for (auto v : G[u])
        {
            if (v == _fa)
                continue;
            int w = dfs(v, u);
            if (w)
                p.push_back(w);
        }
        if (p.size() % 2 && p.size() >= 3)
            p.push_back(u);
        for (int i = 0; i + 1 < (int)p.size(); i += 2)
            path.emplace_back(p[i], p[i + 1]);
        if (p.empty())
            p.push_back(u);
        return p.size() % 2 == 0 ? 0 : p.back();
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
        int w = dfs(1, 0);
        if (w)
            path.emplace_back(1, w);
        cout << path.size() << '\n';
        for (auto [x, y] : path)
            cout << x << ' ' << y << '\n';
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
