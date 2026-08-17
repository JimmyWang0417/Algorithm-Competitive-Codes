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
struct subtask1
{
    int n, m, q;
    vector<vector<int>> g;
    vector<bool> vis;
    vector<int> dfn;
    vector<int> p;
    vector<pair<int, int>> edges;
    subtask1()
    {
        cin >> n >> m;
        g.resize(n + 5);
        dfn.resize(n + 5);
        vis.resize(n + 5);
        edges.resize(m);
        for (auto &[u, v] : edges)
        {
            cin >> u >> v;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        cin >> q;
        p.resize(q);
        int dfstime = n;
        queue<int> que;
        for (int &x : p)
        {
            cin >> x;
            que.push(x);
            vis[x] = true;
            dfn[x] = dfstime--;
        }
        while (!que.empty())
        {
            int u = que.front();
            que.pop();
            for (int v : g[u])
            {
                if (vis[v])
                    continue;
                que.push(v);
                vis[v] = true;
                dfn[v] = dfstime--;
            }
        }
        for (auto [u, v] : edges)
        {
            if (dfn[u] > dfn[v])
                swap(u, v);
            if (u == p.back() && v == p.front())
                swap(u, v);
            cout << u << ' ' << v << '\n';
        }
    }
};
struct subtask2
{
    int n, m;
    vector<vector<int>> g, h;
    vector<int> in;
    vector<bool> vis;
    subtask2()
    {
        cin >> n >> m;
        g.resize(n + 5);
        h.resize(n + 5);
        in.resize(n + 5);
        vis.resize(n + 5);
        for (int i = 1; i <= m; ++i)
        {
            int u, v;
            cin >> u >> v;
            g[u].push_back(v);
            h[v].push_back(u);
            ++in[v];
        }
        queue<int> que;
        for (int i = 1; i <= n; ++i)
            if (!in[i])
                que.push(i);
        while (!que.empty())
        {
            int u = que.front();
            que.pop();
            vis[u] = true;
            for (int v : g[u])
                if (!--in[v])
                    que.push(v);
        }
        int S = 0;
        for (int i = 1; i <= n; ++i)
            if (in[i] == 1)
            {
                que.push(i);
                S = i;
            }
        vector<int> to(n + 5);
        while (!que.empty())
        {
            int u = que.front();
            que.pop();
            int v = u;
            for (int w : h[u])
                if (!vis[w])
                    v = w;
            vis[v] = true;
            for (int w : g[v])
                if (--in[w] == 1)
                    que.push(w);
            to[u] = v;
        }
        vector<int> p = {S};
        for (int u = to[S]; u != S; u = to[u])
            p.push_back(u);
        for (int i : p)
            cout << i << ' ';
        cout << '\n';
    }
};
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T;
    cin >> T;
    if (T == 1)
        subtask1();
    else
        subtask2();
    return 0;
}

