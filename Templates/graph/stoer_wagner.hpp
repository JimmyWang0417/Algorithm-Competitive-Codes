struct StoerWagner
{
    int n, mincut;
    vector<int> fa;
    vector<vector<int>> G;
    vector<bool> del;
    auto find(int x) -> int
    {
        return !fa[x] ? x : fa[x] = find(fa[x]);
    }
    auto isConnected(const vector<tuple<int, int, int>> &edges) -> bool
    {
        for (const auto &e : edges)
        {
            int u = find(get<0>(e)), v = find(get<1>(e));
            if (u != v)
                fa[u] = v;
        }
        for (int i = 2; i <= n; ++i)
            if (find(1) != find(i))
                return false;
        return true;
    }
    auto contract(int &s, int &t)
    {
        vector<int> dis(n + 1);
        vector<bool> vis(n + 1);
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
            for (int i = 1; i <= n; ++i)
                if (!del[i] && !vis[i])
                    dis[i] += G[where][i];
        }
    }
    StoerWagner(int _n, const vector<tuple<int, int, int>> &edges)
        : n(_n), mincut(INT_MAX), fa(n + 1), G(n + 1, vector<int>(n + 1)), del(n + 1)
    {
        if (n <= 1)
        {
            mincut = 0;
            return;
        }
        if (!isConnected(edges))
        {
            mincut = 0;
            return;
        }
        for (auto [u, v, w] : edges)
            G[u][v] += w, G[v][u] += w;
        for (int i = 1; i < n; ++i)
        {
            int s = 0, t = 0;
            mincut = min(mincut, contract(s, t));
            del[t] = true;
            for (int j = 1; j <= n; ++j)
                if (!del[j])
                    G[s][j] = (G[j][s] += G[j][t]);
        }
    }
};
