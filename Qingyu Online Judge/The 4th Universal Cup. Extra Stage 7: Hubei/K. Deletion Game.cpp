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
    vector<int> S, a;
    Main()
    {
        cin >> n;
        S.resize(n + 5);
        a.resize(n + 5);
        for (int i = 1; i <= n; ++i)
            cin >> S[i];
        for (int i = 1; i <= n; ++i)
            cin >> a[i];

        vector<int> p(S.begin() + 1, S.begin() + 1 + n);
        sort(p.begin(), p.end());
        p.erase(unique(p.begin(), p.end()), p.end());
        vector<vector<int>> T(p.size());
        vector<vector<tuple<int, int, int>>> G(n + 5);
        for (int i = 1; i <= n; ++i)
        {
            S[i] = (int)(lower_bound(p.begin(), p.end(), S[i]) - p.begin());
            T[S[i]].push_back(i);
        }
        for (const auto &t : T)
        {
            for (int j = 1; j < (int)t.size(); ++j)
            {
                G[t[j - 1]].emplace_back(t[j], 0, 0);
                G[t[j]].emplace_back(t[0], 0, 1);
            }
        }

        for (int i = 1; i < n; ++i)
            G[i].emplace_back(i + 1, a[i + 1], 0);

        vector<pair<i64, int>> dis(n + 5, {LLONG_MAX, INT_MAX});
        vector<bool> vis(n + 5);
        priority_queue<pair<pair<i64, int>, int>, vector<pair<pair<i64, int>, int>>, greater<>> q;
        dis[1] = {a[1], 1};
        q.emplace(dis[1], 1);
        while (!q.empty())
        {
            int u = q.top().second;
            q.pop();
            if (vis[u])
                continue;
            vis[u] = true;
            for (auto [v, w1, w2] : G[u])
            {
                pair<i64, int> cur = {dis[u].first + w1, dis[u].second + w2};
                if (dis[v] > cur)
                    q.emplace(dis[v] = cur, v);
            }
        }
        cout << dis[n].first << ' ' << dis[n].second << '\n';
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
