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
    int n, m, s;
    int L, R, lca;
    vector<vector<int>> G;
    vector<vector<int>> g;
    vector<int> fa, dep;
    vector<int> col;
    vector<int> a;
    vector<int> answer, insert;
    auto init(int u, int _fa, int c) -> void
    {
        dep[u] = dep[fa[u] = _fa] + 1;
        col[u] = c;
        for (int v : G[u])
        {
            if (col[v] == -1)
            {
                init(v, u, c ^ 1);
                g[u].push_back(v);
            }
            else if (col[v] == c)
                L = u, R = v;
        }
    }
    auto dfs(int u) -> void
    {
        if (u == lca)
            answer.insert(answer.end(), insert.begin(), insert.end());
        for (int v : g[u])
        {
            answer.push_back(v), a[v] ^= 1;
            dfs(v);
            answer.push_back(u), a[u] ^= 1;
            if (a[v])
            {
                answer.push_back(v), a[v] ^= 1;
                answer.push_back(u), a[u] ^= 1;
            }
        }
    }
    Main() : L(0), R(0)
    {
        cin >> n >> m >> s;
        a.resize(n + 5);
        for (int i = 1; i <= n; ++i)
        {
            cin >> a[i];
            a[i] %= 2;
        }
        G.resize(n + 5);
        g.resize(n + 5);
        fa.resize(n + 5);
        dep.resize(n + 5);
        col.resize(n + 5, -1);
        for (int i = 1; i <= m; ++i)
        {
            int u, v;
            cin >> u >> v;
            G[u].push_back(v);
            G[v].push_back(u);
        }
        init(s, 0, 0);
        {
            int qwq = 0;
            for (int i = 1; i <= n; ++i)
                qwq ^= a[i];
            if (qwq & 1)
            {
                if (!L)
                {
                    cout << "No\n";
                    return;
                }
                auto LCA = [&](int u, int v)
                {
                    if (dep[u] < dep[v])
                        swap(u, v);
                    while (dep[u] > dep[v])
                        u = fa[u];
                    while (u != v)
                    {
                        u = fa[u];
                        v = fa[v];
                    }
                    return u;
                };
                lca = LCA(L, R);
                for (int u = L; u != lca; u = fa[u])
                    insert.push_back(u);
                reverse(insert.begin(), insert.end());
                for (int u = R; u != fa[lca]; u = fa[u])
                    insert.push_back(u);
                for (int i : insert)
                    a[i] ^= 1;
            }
        }
        dfs(s);
        for (int i = 1; i <= n; ++i)
            if (a[i])
            {
                cout << "No\n";
                return;
            }
        cout << "Yes\n";
        cout << answer.size() << '\n';
        for (int i : answer)
            cout << i << ' ';
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

