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
    int n;
    vector<int> a, b;
    vector<vector<int>> g;
    vector<int> sze, son;
    vector<int> cnt;
    i64 all;
    auto update(int u, int v)
    {
        if (u)
        {
            all -= abs(cnt[u]);
            cnt[u] += v;
            all += abs(cnt[u]);
        }
        else
            cnt[u] += v;
    }
    auto init(int u, int _fa) -> void
    {
        sze[u] = 1;
        for (int v : g[u])
        {
            if (v == _fa)
                continue;
            init(v, u);
            sze[u] += sze[v];
            if (sze[v] > sze[son[u]])
                son[u] = v;
        }
    }
    auto addtree(int u, int _fa) -> void
    {
        update(a[u], 1);
        if (b[u] == 0)
            update(b[u], 1);
        else
            update(b[u], -1);
        for (int v : g[u])
        {
            if (v == _fa)
                continue;
            addtree(v, u);
        }
    }
    auto deltree(int u, int _fa) -> void
    {
        update(a[u], -1);
        if (b[u] == 0)
            update(b[u], -1);
        else
            update(b[u], 1);
        for (int v : g[u])
        {
            if (v == _fa)
                continue;
            deltree(v, u);
        }
    }
    vector<bool> answer;
    auto dfs(int u, int _fa, bool del) -> void
    {
        for (int v : g[u])
        {
            if (v == _fa || v == son[u])
                continue;
            dfs(v, u, true);
        }
        if (son[u])
            dfs(son[u], u, false);
        update(a[u], 1);
        if (b[u] == 0)
            update(b[u], 1);
        else
            update(b[u], -1);
        for (int v : g[u])
        {
            if (v == _fa || v == son[u])
                continue;
            addtree(v, u);
        }
        answer[u] = (all <= cnt[0]);

        if (del)
            deltree(u, _fa);
    }
    Main() : all(0)
    {
        cin >> n;
        a.resize(n + 5);
        b.resize(n + 5);
        g.resize(n + 5);
        for (int i = 1; i <= n; ++i)
            cin >> a[i];
        for (int i = 1; i <= n; ++i)
            cin >> b[i];
        for (int i = 1; i < n; ++i)
        {
            int u, v;
            cin >> u >> v;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        son.resize(n + 5), sze.resize(n + 5);
        cnt.resize(n + 5), answer.resize(n + 5);
        init(1, 0);
        dfs(1, 0, 0);
        for (int i = 1; i <= n; ++i)
            cout << answer[i];
        cout << '\n';
    }
};
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    cin >> T;
    while (T--)
        Main();
    return 0;
}
