template <typename T = i64>
struct CentroidTree
{
    int n, center, balance;
    vector<vector<pair<int, T>>> G;
    vector<vector<int>> tree;
    vector<vector<pair<int, T>>> path;
    vector<int> sze, fa;
    vector<bool> vis;
    auto getsze(int u, int _fa) -> void
    {
        sze[u] = 1;
        for (auto [v, w] : G[u])
            if (v != _fa && !vis[v])
                getsze(v, u), sze[u] += sze[v];
    }
    auto getroot(int u, int _fa, int sum) -> void
    {
        int mx = sum - sze[u];
        for (auto [v, w] : G[u])
            if (v != _fa && !vis[v])
                getroot(v, u, sum), mx = max(mx, sze[v]);
        if (mx < balance)
            balance = mx, center = u;
    }
    auto getpath(int u, int _fa, int rt, T dis) -> void
    {
        path[u].emplace_back(rt, dis);
        for (auto [v, w] : G[u])
            if (v != _fa && !vis[v])
                getpath(v, u, rt, dis + w);
    }
    auto decompose(int u, int _fa) -> void
    {
        getsze(u, 0);
        center = 0, balance = n + 1;
        getroot(u, 0, sze[u]);
        int rt = center;
        getpath(rt, 0, rt, 0);
        vis[rt] = true, fa[rt] = _fa;
        if (_fa)
            tree[_fa].emplace_back(rt), tree[rt].emplace_back(_fa);
        for (auto [v, w] : G[rt])
            if (!vis[v])
                decompose(v, rt);
    }
    CentroidTree(int _n, const vector<tuple<int, int, T>> &edges, int root = 1)
        : n(_n), G(n + 1), tree(n + 1), path(n + 1), sze(n + 1), fa(n + 1), vis(n + 1)
    {
        for (auto [u, v, w] : edges)
            G[u].emplace_back(v, w), G[v].emplace_back(u, w);
        decompose(root, 0);
    }
};
