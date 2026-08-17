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
    int n, m;
    map<pair<int, int>, set<int>> mp;
    Main()
    {
        cin >> n >> m;
        tuple<int, int, int> S, T;
        {
            auto &[x, y, z] = S;
            cin >> x >> y >> z;
        }
        {
            auto &[x, y, z] = T;
            cin >> x >> y >> z;
        }
        for (int i = 0; i < n; ++i)
        {
            int x, y, z;
            cin >> x >> y >> z;
            mp[{x, y}].emplace(z);
        }
        vector<tuple<int, int, int>> e(m);
        for (auto &[x, y, z] : e)
            cin >> x >> y >> z;
        queue<tuple<int, int, int>> q;
        map<tuple<int, int, int>, int> dis;
        dis[S] = 0;
        q.push(S);
        while (!q.empty())
        {
            auto u = q.front();
            auto [x, y, z] = u;
            q.pop();
            for (auto [a, b, c] : e)
            {
                int X = x + a, Y = y + b, Z = z + c;
                const auto &M = mp[{X, Y}];
                if (M.find(Z) == M.end())
                {
                    auto it = M.lower_bound(Z);
                    if (it != M.begin())
                    {
                        Z = *prev(it) + 1;
                        auto v = tie(X, Y, Z);
                        if (dis.find(v) == dis.end())
                        {
                            dis[v] = dis[u] + 1;
                            q.push(v);
                        }
                    }
                }
            }
        }
        if (dis.find(T) != dis.end())
            cout << dis[T] << '\n';
        else
            cout << -1 << '\n';
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
