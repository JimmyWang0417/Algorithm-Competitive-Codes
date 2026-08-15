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
    int n, m, q;
    struct edge
    {
        int u, v;
        u64 c;
    };
    vector<edge> a;
    struct UnionSet : vector<int>
    {
        using vector<int>::vector;
        UnionSet(size_t n) : vector(n) { iota(begin(), end(), 0); }
        auto find(int x) -> int
        {
            if (at(x) == x)
                return x;
            return at(x) = find(at(x));
        }
        auto merge(int x, int y)
        {
            x = find(x), y = find(y);
            if (x == y)
                return false;
            at(x) = y;
            return true;
        }
    };
    Main()
    {
        cin >> n >> m >> q;
        a.resize(m);
        for (auto &[u, v, c] : a)
            cin >> u >> v >> c;
        vector<vector<pair<int, int>>> que(m);
        vector<u64> Que(q);
        for (int i = 0; i < q; ++i)
        {
            int l, r;
            cin >> l >> r;
            --l, --r;
            que[r].emplace_back(l, i);
        }
        vector<pair<int, int>> S;
        for (int r = 0; r < m; ++r)
        {
            S.emplace(S.begin(), r, -1);
            UnionSet us(n + 5);
            vector<pair<int, int>> T;
            vector<int> U;
            for (auto [i, j] : S)
            {
                auto [u, v, c] = a[i];
                if (us.merge(u, v))
                    T.emplace_back(i, j);
                else
                    U.emplace_back(i);
            }
            S.swap(T);
            vector<vector<pair<int, int>>> G(n + 5);
            for (auto i = 0; i < (int)S.size(); ++i)
            {
                auto [j, _] = S[i];
                auto [u, v, c] = a[j];
                G[u].emplace_back(v, i);
                G[v].emplace_back(u, i);
            }
            for (auto i : U)
            {
                auto dfs = [&](auto &&self, int u, int _fa, int gl, int val) -> bool
                {
                    if (u == gl)
                        return true;
                    for (auto [v, id] : G[u])
                    {
                        if (v == _fa)
                            continue;
                        if (self(self, v, u, gl, val))
                        {
                            S[id].second = max(S[id].second, val);
                            return true;
                        }
                    }
                    return false;
                };
                auto [u, v, c] = a[i];
                dfs(dfs, u, 0, v, i);
                // cout << ' ' << u << ' ' << v << ' ' << r << '\n';
                // cout << r << ' ' << i << '\n';
            }
            vector<tuple<int, int, u64>> p;
            for (auto [i, j] : S)
            {
                auto [u, v, c] = a[i];
                p.emplace_back(i, j, c);
            }
            for (auto [l, id] : que[r])
            {
                for (auto [i, j, c] : p)
                    if (j < l && l <= i)
                        Que[id] += c;
            }
        }
        for (auto i : Que)
            cout << i << '\n';
    }
};
signed main()
{
    // freopen("project.in", "r", stdin);
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--)
        Main();
    return 0;
}
