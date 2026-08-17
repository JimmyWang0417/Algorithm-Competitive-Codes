struct blockForest
{
    vector<int> dfn, low;
    vector<int> belong;
    vector<vector<int>> h;
    int color;
    blockForest() = default;
    blockForest(int n, const vector<vector<int>> &g)
        : dfn(n + 5), low(n + 5), belong(n + 5), h(n + 1), color(0)
    {
        int dfstime = 0;
        stack<int> st;
        function<void(int)> dfs = [&](int u)
        {
            st.push(u);
            dfn[u] = low[u] = ++dfstime;
            for (int v : g[u])
            {
                if (!dfn[v])
                {
                    dfs(v);
                    low[u] = min(low[u], low[v]);
                    if (dfn[u] == low[v])
                    {
                        int w = (int)h.size();
                        h.emplace_back();
                        h[w].push_back(u);
                        h[u].push_back(w);
                        while (st.top() != v)
                        {
                            h[w].push_back(st.top());
                            h[st.top()].push_back(w);
                            st.pop();
                        }
                        h[w].push_back(v);
                        h[v].push_back(w);
                        st.pop();
                    }
                }
                else
                    low[u] = min(low[u], dfn[v]);
            }
        };
        for (int i = 1; i <= n; ++i)
            if (!dfn[i])
                dfs(i);
    }
};