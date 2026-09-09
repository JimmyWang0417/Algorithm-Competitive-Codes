struct LCA
{
    int n;
    vector<vector<int>> G;
    vector<int> dep, pos, euler;
    vector<vector<int>> st;
    auto dfs(int u, int _fa) -> void
    {
        pos[u] = (int)euler.size();
        euler.emplace_back(u);
        for (auto v : G[u])
        {
            if (v == _fa)
                continue;
            dep[v] = dep[u] + 1;
            dfs(v, u);
            euler.emplace_back(u);
        }
    }
    LCA(int _n, const vector<pair<int, int>> &edges, int root) : n(_n), G(n + 1), dep(n + 1), pos(n + 1)
    {
        for (auto [u, v] : edges)
        {
            G[u].emplace_back(v);
            G[v].emplace_back(u);
        }
        dfs(root, 0);
        st.assign(__lg(max((int)euler.size(), 1)) + 1, euler);
        auto cmp = [&](int x, int y)
        { return dep[x] < dep[y]; };
        for (int j = 0; j + 1 < (int)st.size(); ++j)
            for (int i = 0; i + (2 << j) - 1 < (int)euler.size(); ++i)
                st[j + 1][i] = min(st[j][i], st[j][i + (1 << j)], cmp);
    }
    auto query(int x, int y)
    {
        int l = pos[x], r = pos[y];
        if (l > r)
            swap(l, r);
        int k = __lg(r - l + 1);
        return min(st[k][l], st[k][r - (1 << k) + 1], [&](int u, int v)
                   { return dep[u] < dep[v]; });
    }
};
