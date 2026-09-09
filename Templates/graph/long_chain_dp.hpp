template <typename T = i64>
struct LongChainDP
{
    int n, root, used;
    vector<vector<int>> G;
    vector<int> fa, height, son;
    vector<T> pool;
    vector<span<T>> dp;
    auto dfs1(int u, int _fa) -> void
    {
        fa[u] = _fa, height[u] = 1;
        for (auto v : G[u])
            if (v != _fa)
            {
                dfs1(v, u);
                if (height[v] + 1 > height[u])
                    height[u] = height[v] + 1, son[u] = v;
            }
    }
    template <typename F, typename Merge>
    auto dfs2(int u, F &work, Merge &merge) -> void
    {
        if (son[u])
        {
            dp[son[u]] = dp[u].subspan(1, height[son[u]]);
            dfs2(son[u], work, merge);
        }
        for (auto v : G[u])
            if (v != fa[u] && v != son[u])
            {
                dp[v] = span(pool.data() + used, height[v]);
                used += height[v];
                dfs2(v, work, merge);
                merge(u, v, dp[u], dp[v]);
            }
        work(u, dp[u]);
    }
    LongChainDP(int _n, const vector<pair<int, int>> &edges, int _root = 1)
        : n(_n), root(_root), used(0), G(n + 1), fa(n + 1), height(n + 1), son(n + 1), pool(n), dp(n + 1)
    {
        for (auto [u, v] : edges)
            G[u].emplace_back(v), G[v].emplace_back(u);
        dfs1(root, 0);
    }
    template <typename F, typename Merge>
    auto solve(F work, Merge merge)
    {
        fill(pool.begin(), pool.end(), T());
        dp[root] = span(pool.data(), height[root]);
        used = height[root];
        dfs2(root, work, merge);
    }
};
