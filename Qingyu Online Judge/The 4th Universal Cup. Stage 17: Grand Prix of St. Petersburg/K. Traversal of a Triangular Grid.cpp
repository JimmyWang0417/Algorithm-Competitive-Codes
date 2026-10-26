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
    int n, m, q;
    map<pair<int, int>, int> mp;
    vector<vector<tuple<int, int, int>>> G;
    vector<bool> vis;
    stack<pair<int, int>> st;
    auto dfs(int u, int c) -> void
    {
        while (!G[u].empty())
        {
            auto [v, w, id] = G[u].back();
            G[u].pop_back();
            if (vis[id])
                continue;
            vis[id] = true;
            dfs(v, w);
        }
        st.emplace(u, c);
    }
    Main()
    {
        m = q = 0;
        cin >> n;
        for (int i = 0; i <= n; ++i)
        {
            for (int j = 0; j <= i; ++j)
                mp[{i, j}] = m++;
        }
        G.resize(m);
        for (int i = 0; i <= n; ++i)
            for (int j = 0; j <= i; ++j)
            {
                if (j + 1 <= i)
                {
                    G[mp[{i, j}]].emplace_back(mp[{i, j + 1}], 0, q);
                    G[mp[{i, j + 1}]].emplace_back(mp[{i, j}], 3, q);
                    ++q;
                }
                if (i - 1 >= j)
                {
                    G[mp[{i, j}]].emplace_back(mp[{i - 1, j}], 1, q);
                    G[mp[{i - 1, j}]].emplace_back(mp[{i, j}], 4, q);
                    ++q;
                }
                if (i - 1 >= 0 && j - 1 >= 0)
                {
                    G[mp[{i, j}]].emplace_back(mp[{i - 1, j - 1}], 2, q);
                    G[mp[{i - 1, j - 1}]].emplace_back(mp[{i, j}], 5, q);
                    ++q;
                }
            }
        vis.resize(q);
        dfs(0, 0);
        st.pop();
        while (!st.empty())
        {
            auto [u, v] = st.top();
            st.pop();
            cout << v;
        }
        cout << '\n';
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
