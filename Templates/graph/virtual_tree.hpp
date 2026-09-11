struct VirtualTree
{
    int root = 0;
    vector<int> point;
    vector<pair<int, int>> edges;
    VirtualTree() = default;
    template <typename LCA>
    VirtualTree(vector<int> p, const vector<int> &dfn, LCA lca)
    {
        if (p.empty())
            return;
        ranges::sort(p, {}, [&](int u)
                     { return dfn[u]; });
        p.erase(unique(p.begin(), p.end()), p.end());
        int n = (int)p.size();
        for (int i = 1; i < n; ++i)
            p.emplace_back(lca(p[i - 1], p[i]));
        ranges::sort(p, {}, [&](int u)
                     { return dfn[u]; });
        p.erase(unique(p.begin(), p.end()), p.end());
        stack<int> st;
        for (int u : p)
        {
            while (!st.empty() && lca(st.top(), u) != st.top())
                st.pop();
            if (!st.empty())
                edges.emplace_back(st.top(), u);
            st.push(u);
        }
        while (st.size() > 1)
            st.pop();
        root = st.top();
        point = move(p);
    }
};
