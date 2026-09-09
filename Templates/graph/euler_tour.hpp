struct EulerTour
{
    int n;
    vector<vector<int>> G;
    vector<int> p;
    auto dfs(int u) -> void
    {
        while (!G[u].empty())
        {
            int v = G[u].back();
            G[u].pop_back();
            dfs(v);
        }
        p.emplace_back(u);
    }
    EulerTour(int _n, const vector<pair<int, int>> &edges) : n(_n), G(n + 1)
    {
        vector<int> in(n + 1), out(n + 1);
        for (auto [u, v] : edges)
        {
            G[u].emplace_back(v);
            ++out[u], ++in[v];
        }
        for (int i = 1; i <= n; ++i)
            sort(G[i].begin(), G[i].end(), greater<int>());
        int S = 1, start = 0, cnt0 = 0, cnt1 = 0;
        for (int u = 1; u <= n; ++u)
        {
            if (out[u] && !start)
                start = u;
            if (in[u] == out[u])
                continue;
            if (out[u] - in[u] == 1)
            {
                S = u;
                ++cnt0;
            }
            else if (in[u] - out[u] == 1)
                ++cnt1;
            else
                return;
        }
        if (cnt0 != cnt1 || cnt0 > 1)
            return;
        if (!cnt0 && start)
            S = start;
        p.reserve(edges.size() + 1);
        dfs(S);
        reverse(p.begin(), p.end());
        if (p.size() != edges.size() + 1)
            p.clear();
    }
};
