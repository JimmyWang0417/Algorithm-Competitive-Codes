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
    int n, m;
    map<pair<int, int>, int> mp;
    auto get(int x, int y)
    {
        if (mp.find({x, y}) == mp.end())
            mp[{x, y}] = ++m;
        return mp[{x, y}];
    }
    vector<vector<int>> G;
    constexpr static int base = 2e5;
    vector<array<bool, 3>> vis;
    auto dfs(int u, int d)
    {
        if (vis[u][d])
            return;
        vis[u][d] = true;
        for (auto v : G[u])
            dfs(v, (d + 1) % 3);
    }
    Main()
    {
        cin >> n;
        m = 0;
        G.resize(6 * n + 5);
        for (int i = 0; i < n; ++i)
        {
            array<int, 3> a;
            for (int j = 0; j < 3; ++j)
                cin >> a[j];
            sort(a.begin(), a.end());
            do
                G[get(a[0], a[1])].emplace_back(get(a[1], a[2]));
            while (next_permutation(a.begin(), a.end()));
        }
        G.resize(m + 5);
        vis.resize(m + 5);
        for (int i = 1; i <= m; ++i)
        {
            if (vis[i][0] || vis[i][1] || vis[i][2])
                continue;
            dfs(i, 0);
            if (vis[i][1] || vis[i][2])
            {
                cout << "yes\n";
                return;
            }
        }
        cout << "no\n";
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
