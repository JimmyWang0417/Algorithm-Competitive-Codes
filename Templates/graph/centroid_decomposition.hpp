template <typename T = i64>
struct CentroidDecomposition
{
    int n, center, balance;
    vector<vector<pair<int, T>>> G;
    vector<int> sze;
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
    auto getdis(int u, int _fa, T dis, vector<pair<int, T>> &res) -> void
    {
        res.emplace_back(u, dis);
        for (auto [v, w] : G[u])
            if (v != _fa && !vis[v])
                getdis(v, u, dis + w, res);
    }
    template <typename F>
    auto decompose(int u, F &work) -> void
    {
        getsze(u, 0);
        center = 0, balance = n + 1;
        getroot(u, 0, sze[u]);
        int rt = center;
        vis[rt] = true;
        work(rt);
        for (auto [v, w] : G[rt])
            if (!vis[v])
                decompose(v, work);
    }
    CentroidDecomposition(int _n, const vector<tuple<int, int, T>> &edges)
        : n(_n), G(n + 1), sze(n + 1), vis(n + 1)
    {
        for (auto [u, v, w] : edges)
            G[u].emplace_back(v, w), G[v].emplace_back(u, w);
    }
    template <typename F>
    auto solve(int root, F work)
    {
        decompose(root, work);
    }
};
