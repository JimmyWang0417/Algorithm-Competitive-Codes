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
    vector<int> sze;
    vector<vector<int>> G;
    auto dfs(int u, int _fa) -> int
    {
        int res = 0;
        i64 cnt = !!u;
        sze[u] = !!u;
        for (int v : G[u])
        {
            if (v == _fa)
                continue;
            res ^= dfs(v, u);
            cnt += (i64)sze[u] * sze[v];
            sze[u] += sze[v];
        }
        cnt += (i64)sze[u] * (n - sze[u] - 1);
        if (cnt & 1)
            res ^= u;
        return res;
    }
    Main()
    {
        cin >> n;
        n = 1 << n;
        G.resize(n);
        for (int i = 1; i < n; ++i)
        {
            int u, v;
            cin >> u >> v;
            G[u].push_back(v);
            G[v].push_back(u);
        }
        sze.resize(n);
        cout << dfs(0, 0) << '\n';
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

