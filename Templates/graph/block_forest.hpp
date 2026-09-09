struct BlockForest
{
    int n, dfstime = 0;
    vector<vector<int>> G, h;
    vector<int> dfn, low;
    stack<int> st;
    auto dfs(int u) -> void
    {
        st.push(u);
        dfn[u] = low[u] = ++dfstime;
        for (auto v : G[u])
        {
            if (!dfn[v])
            {
                dfs(v);
                low[u] = min(low[u], low[v]);
                if (dfn[u] == low[v])
                {
                    int w = (int)h.size();
                    h.emplace_back();
                    h[w].emplace_back(u);
                    h[u].emplace_back(w);
                    while (st.top() != v)
                    {
                        h[w].emplace_back(st.top());
                        h[st.top()].emplace_back(w);
                        st.pop();
                    }
                    h[w].emplace_back(v);
                    h[v].emplace_back(w);
                    st.pop();
                }
            }
            else
                low[u] = min(low[u], dfn[v]);
        }
    }
    BlockForest(int _n, const vector<pair<int, int>> &edges)
        : n(_n), G(n + 1), h(n + 1), dfn(n + 1), low(n + 1)
    {
        for (auto [u, v] : edges)
        {
            G[u].emplace_back(v);
            G[v].emplace_back(u);
        }
        for (int i = 1; i <= n; ++i)
            if (!dfn[i])
                dfs(i);
    }
};
