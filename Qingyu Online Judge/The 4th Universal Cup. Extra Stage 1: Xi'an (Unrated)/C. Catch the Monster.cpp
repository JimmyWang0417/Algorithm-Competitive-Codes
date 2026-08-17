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
    vector<vector<int>> g;
    Main()
    {
        cin >> n >> m >> q;
        g.resize(n + 5);
        for (int i = 1; i <= m; ++i)
        {
            int u, v;
            cin >> u >> v;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        vector<int> answer(n + 5);
        vector<int> deg(n + 5);
        vector<int> cnt(n + 5);
        vector<int> pa(n + 5);
        int all = 0;
        for (int l = 1, r = 1; r <= n; ++r)
        {
            auto add = [&](int u)
            {
                all -= (cnt[u] > 2);
                for (int v : g[u])
                    if (l <= v && v <= r)
                    {
                        all -= (cnt[v] > 2);
                        if (deg[v] == 1)
                            all -= (cnt[pa[v]] > 2);
                    }

                for (int v : g[u])
                    if (l <= v && v <= r)
                    {
                        ++deg[u], ++deg[v];
                        pa[u] ^= v, pa[v] ^= u;
                    }

                if (deg[u] >= 2)
                    for (int v : g[u])
                        if (l <= v && v <= r)
                            ++cnt[v];
                for (int v : g[u])
                    if (l <= v && v <= r && deg[v] == 2)
                        ++cnt[pa[v] ^ u];
                for (int v : g[u])
                    if (l <= v && v <= r)
                        cnt[u] += (deg[v] >= 2);

                all += (cnt[u] > 2);
                for (int v : g[u])
                {
                    all += (cnt[v] > 2);
                    if (deg[v] == 2)
                        all += (cnt[pa[v] ^ u] > 2);
                }
            };
            auto del = [&](int u)
            {
                all -= (cnt[u] > 2);
                for (int v : g[u])
                {
                    all -= (cnt[v] > 2);
                    if (deg[v] == 2)
                        all -= (cnt[pa[v] ^ u] > 2);
                }

                for (int v : g[u])
                    if (l <= v && v <= r)
                        cnt[u] -= (deg[v] >= 2);
                for (int v : g[u])
                    if (l <= v && v <= r && deg[v] == 2)
                        --cnt[pa[v] ^ u];
                if (deg[u] >= 2)
                    for (int v : g[u])
                        if (l <= v && v <= r)
                            --cnt[v];

                for (int v : g[u])
                    if (l <= v && v <= r)
                    {
                        --deg[u], --deg[v];
                        pa[u] ^= v, pa[v] ^= u;
                    }

                all += (cnt[u] > 2);
                for (int v : g[u])
                    if (l <= v && v <= r)
                    {
                        all += (cnt[v] > 2);
                        if (deg[v] == 1)
                            all += (cnt[pa[v]] > 2);
                    }
            };
            add(r);
            while (all)
                del(l++);
            answer[r] = l;
            assert(l <= r);
        }
        while (q--)
        {
            int l, r;
            cin >> l >> r;
            cout << (answer[r] <= l ? "Yes\n" : "No\n");
        }
    }
};
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--)
        Main();
    return 0;
}
