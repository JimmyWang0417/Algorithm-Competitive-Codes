struct schreierSims
{
    struct permutation : public vector<int>
    {
        using vector<int>::vector;
        permutation() = default;
        permutation(int n)
        {
            resize(n);
            iota(begin(), end(), 0);
        }
        auto friend operator*(const permutation &lhs, const permutation &rhs)
        {
            permutation res(lhs.size());
            for (int i = 0; i < (int)res.size(); ++i)
                res[i] = lhs[rhs[i]];
            return res;
        }
    };
    int n;
    vector<vector<bool>> reach;
    vector<vector<permutation>> t;
    vector<vector<permutation>> r, inv;
    auto contain(int u, const permutation &g)
    {
        if (u == n)
            return true;
        int v = g[u];
        if (!reach[u][v])
            return false;
        return contain(u + 1, inv[u][v] * g);
    }
    auto add(int u, const permutation &g)
    {
        if (contain(u, g))
            return;
        t[u].push_back(g);
        for (int v = u; v < n; ++v)
            if (reach[u][v])
                dfs(u, g * r[u][v]);
    }
    void dfs(int u, const permutation &g)
    {
        int v = g[u];
        if (reach[u][v])
            add(u + 1, inv[u][v] * g);
        else
        {
            reach[u][v] = true;
            r[u][v] = g;
            for (int i = 0; i < n; ++i)
                inv[u][v][g[i]] = i;
            for (auto f : t[u])
                dfs(u, f * g);
        }
    }
    schreierSims() = default;
    schreierSims(const vector<permutation> &per)
    {
        n = (int)per.front().size();
        t.resize(n);
        reach.assign(n, vector<bool>(n));
        r.assign(n, vector<permutation>(n, permutation(n)));
        inv.assign(n, vector<permutation>(n, permutation(n)));
        for (int i = 0; i < n; ++i)
            reach[i][i] = true;
        for (const auto &p : per)
            add(0, p);
    }
};