struct tarjan
{
    vector<int> dfn, low;
    vector<int> belong;
    int color;
    tarjan() = default;
    tarjan(int n, const vector<vector<int>> &g) // 有向图tarjan
        : dfn(n + 5), low(n + 5), belong(n + 5), color(0)
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
                }
                else if (!belong[v])
                    low[u] = min(low[u], dfn[v]);
            }
            if (low[u] == dfn[u])
            {
                belong[u] = ++color;
                while (st.top() != u)
                {
                    belong[st.top()] = color;
                    st.pop();
                }
                st.pop();
            }
        };
        for (int i = 1; i <= n; ++i)
            if (!dfn[i])
                dfs(i);
    }
    tarjan(int n, const vector<vector<pair<int, int>>> &g) // 无向图tarjan
        : dfn(n + 5), low(n + 5), belong(n + 5), color(0)
    {
        int dfstime = 0;
        stack<int> st;
        function<void(int, int)> dfs = [&](int u, int lasid)
        {
            st.push(u);
            dfn[u] = low[u] = ++dfstime;
            for (auto [v, id] : g[u])
            {
                if (id == lasid)
                    continue;
                if (!dfn[v])
                {
                    dfs(v, lasid);
                    low[u] = min(low[u], low[v]);
                }
                else low[u] = min(low[u], dfn[v]);
            }
            if (low[u] == dfn[u])
            {
                belong[u] = ++color;
                while (st.top() != u)
                {
                    belong[st.top()] = color;
                    st.pop();
                }
                st.pop();
            }
        };
        for (int i = 1; i <= n; ++i)
            if (!dfn[i])
                dfs(i, -1);
    }
};