struct decomposition
{
    int n = 0, dfstime = 0;
    vector<vector<int>> G;
    vector<int> dep, fa;
    vector<int> sze, son;
    vector<int> dfn, top;
    auto dfs1(int u, int _fa) -> void
    {
        sze[u] = 1;
        dep[u] = dep[fa[u] = _fa] + 1;
        for (auto v : G[u])
        {
            if (v == _fa)
                continue;
            dfs1(v, u);
            sze[u] += sze[v];
            if (sze[v] > sze[son[u]])
                son[u] = v;
        }
    }
    auto dfs2(int u, int topf) -> void
    {
        dfn[u] = ++dfstime;
        top[u] = topf;
        if (son[u])
            dfs2(son[u], topf);
        for (auto v : G[u])
        {
            if (v == fa[u] || v == son[u])
                continue;
            dfs2(v, v);
        }
    }
    decomposition(int _n, const vector<pair<int, int>> &edges, int root = 1)
        : n(_n), G(n + 1), dep(n + 1), fa(n + 1), sze(n + 1), son(n + 1), dfn(n + 1), top(n + 1)
    {
        for (auto [u, v] : edges)
        {
            G[u].emplace_back(v);
            G[v].emplace_back(u);
        }
        dfs1(root, 0);
        dfs2(root, root);
    }
};
