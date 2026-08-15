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
constexpr int inv2 = (mod + 1) / 2;
struct Main
{
    int n;
    vector<int> c;
    vector<vector<int>> g;
    i64 inside, outside;
    vector<i64> in, out;
    vector<int> son, sze;
    vector<i64> cntin, cntout;
    auto init(int u, int _fa) -> void
    {
        sze[u] = 1;
        for (int v : g[u])
        {
            if (v == _fa)
                continue;
            init(v, u);
            sze[u] += sze[v];
            if (sze[son[u]] < sze[v])
                son[u] = v;
        }
    }
    auto add(int u)
    {
        (inside -= in[u] - 1) %= mod;
        (outside -= out[u] - 1) %= mod;
        (in[u] *= 2) %= mod;
        (out[u] *= inv2) %= mod;
        (inside += in[u] - 1) %= mod;
        (outside += out[u] - 1) %= mod;
    }
    auto del(int u)
    {
        (inside -= in[u] - 1) %= mod;
        (outside -= out[u] - 1) %= mod;
        (in[u] *= inv2) %= mod;
        (out[u] *= 2) %= mod;
        (inside += in[u] - 1) %= mod;
        (outside += out[u] - 1) %= mod;
    }
    auto addtree(int u, int _fa) -> void
    {
        add(c[u]);
        for (int v : g[u])
        {
            if (v == _fa)
                continue;
            addtree(v, u);
        }
    }
    auto deltree(int u, int _fa) -> void
    {
        del(c[u]);
        for (int v : g[u])
        {
            if (v == _fa)
                continue;
            deltree(v, u);
        }
    }
    auto dfs(int u, int _fa, bool del) -> void
    {
        for (int v : g[u])
        {
            if (v == _fa || v == son[u])
                continue;
            dfs(v, u, 1);
        }
        if (son[u])
            dfs(son[u], u, 0);
        for (int v : g[u])
        {
            if (v == _fa || v == son[u])
                continue;
            addtree(v, u);
        }
        add(c[u]);
        cntin[u] = inside, cntout[u] = outside;

        if (del)
            deltree(u, _fa);
    }
    i64 answer;
    auto solve(int u, int _fa, i64 ind) -> void
    {
        auto only = cntin[u];
        for (int v : g[u])
        {
            if (v == _fa)
                continue;
            (only -= cntin[v]) %= mod;
        }
        (answer += only * (2 * cntout[u] - ind)) %= mod;
        for (int v : g[u])
        {
            if (v == _fa)
                continue;
            (ind += cntin[v]) %= mod;
        }
        for (int v : g[u])
        {
            if (v == _fa)
                continue;
            solve(v, u, (ind - cntin[v]) % mod);
        }
    }
    Main() : inside(0), outside(0), answer(0)
    {
        cin >> n;
        c.resize(n + 5);
        g.resize(n + 5);
        for (int i = 1; i <= n; ++i)
            cin >> c[i];
        for (int i = 1; i < n; ++i)
        {
            int u, v;
            cin >> u >> v;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        son.resize(n + 5), sze.resize(n + 5);
        init(1, 0);
        in.resize(n + 5, 1), out.resize(n + 5, 1);
        for (int i = 1; i <= n; ++i)
            (out[c[i]] *= 2) %= mod;
        for (int i = 1; i <= n; ++i)
            (outside += out[i] - 1) %= mod;
        cntin.resize(n + 5), cntout.resize(n + 5);
        dfs(1, 0, 0);
        // for (int i = 1; i <= n; ++i)
        //     cout << cntin[i] << ' ';
        // cout << '\n';
        // for (int i = 1; i <= n; ++i)
        //     cout << cntout[i] << ' ';
        // cout << '\n';
        solve(1, 0, 0);
        cout << answer << '\n';
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
