struct stoerWagner
{
    int mincut;
    stoerWagner() = default;
    stoerWagner(int n, const vector<tuple<int, int, int>> &edges) : mincut(INT_MAX)
    {
        vector<int> fa(n + 5);
        auto isConnected = [&]()
        {
            function<int(int)> find = [&](int x) -> int
            {
                return !fa[x] ? x : fa[x] = find(fa[x]);
            };
            for (auto [u, v, w] : edges)
            {
                u = find(u), v = find(v);
                if (u == v)
                    continue;
                fa[u] = v;
            }
            for (int i = 2; i <= n; ++i)
                if (find(1) != find(i))
                    return false;
            return true;
        };
        if (!isConnected())
        {
            mincut = 0;
            return;
        }
        vector g(n + 5, vector<int>(n + 5));
        vector<bool> del(n + 5);
        for (auto [u, v, w] : edges)
            g[u][v] += w, g[v][u] += w;
        auto contract = [&](int &s, int &t)
        {
            vector<int> dis(n + 5);
            vector<bool> vis(n + 5);
            int res = 0;
            while (true)
            {
                int where = -1, maxx = -1;
                for (int i = 1; i <= n; ++i)
                    if (!del[i] && !vis[i] && dis[i] > maxx)
                    {
                        where = i;
                        maxx = dis[i];
                    }
                if (where == -1)
                    return res;
                s = t, t = where;
                res = maxx;
                vis[where] = true;
                for (int i = 1; i <= n; i++)
                    if (!del[i] && !vis[i])
                        dis[i] += g[where][i];
            }
        };
        for (int i = 1; i < n; ++i)
        {
            int s, t;
            mincut = min(mincut, contract(s, t));
            del[t] = true;
            for (int j = 1; j <= n; ++j)
                if (!del[j])
                    g[s][j] = (g[j][s] += g[j][t]);
        }
    }
};