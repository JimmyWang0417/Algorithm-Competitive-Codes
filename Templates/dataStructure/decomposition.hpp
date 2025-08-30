namespace dataStructure
{
    struct decomposition
    {
        vector<int> dep, fa;
        vector<int> sze, son;
        vector<int> dfn, top;
        decomposition() = default;
        decomposition(int n, const vector<vector<int>> &g)
            : dep(n + 5), fa(n + 5), sze(n + 5), son(n + 5), top(n + 5)
        {
            function<void(int, int)> dfs1 = [&](int u, int _fa)
            {
                sze[u] = 1;
                dep[u] = dep[fa[u] = _fa] + 1;
                for (auto v : g[u])
                {
                    if (v == _fa)
                        continue;
                    dfs1(v, u);
                    sze[u] += sze[v];
                    if (sze[v] > sze[son[u]])
                        son[u] = v;
                }
            };
            int dfstime = 0;
            function<void(int, int)> dfs2 = [&](int u, int topf)
            {
                dfn[u] = ++dfstime;
                top[u] = topf;
                if (son[u])
                    dfs2(son[u], topf);
                for (auto v : g[u])
                {
                    if (dfn[v])
                        continue;
                    dfs2(v, v);
                }
            };
            dfs1(1, 0);
            dfs2(1, 1);
        }
    };
};