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
    auto newnode()
    {
        G.emplace_back(vector<int>(n + 2));
        return (int)G.size() - 1;
    }
    auto dfs(int l, int r)
    {
        if (l == r)
            return -l;
        int mid = (l + r) >> 1;
        int root = newnode();
        int p = dfs(l, mid), q = dfs(mid + 1, r);
        int u = 0, v = root;
        for (int i = 0; i < mid - l + 1; ++i)
        {
            u = newnode();
            G[v][0] = p;
            for (int j = 1; j < l; ++j)
                G[v][j] = v;
            for (int j = l; j <= mid; ++j)
                G[v][j] = u;
            for (int j = mid + 1; j <= n + 1; ++j)
                G[v][j] = v;
            v = u;
        }
        G[u][0] = q;
        for (int j = 1; j <= n + 1; ++j)
            G[u][j] = u;
        return root;
    }
    Main()
    {
        cin >> n;
        dfs(1, n + 1);
        cout << G.size() << '\n';
        for (const auto &u : G)
        {
            for (auto v : u)
                cout << v << ' ';
            cout << '\n';
        }
    }
};
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--)
        Main();
    return 0;
}
