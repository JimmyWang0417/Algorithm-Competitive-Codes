struct SteinerTree
{
    static constexpr i64 INF = LONG_LONG_MAX / 2;
    int n, k;
    vector<vector<i64>> dp;
    vector<vector<pair<int, int>>> g;
    auto dijkstra(vector<i64> &dist)
    {
        vector<bool> vis(n + 1, false);
        priority_queue<pair<i64, int>, vector<pair<i64, int>>, greater<pair<i64, int>>> q;
        for (int i = 1; i <= n; ++i)
            if (dist[i] < INF)
                q.emplace(dist[i], i);
        while (!q.empty())
        {
            int u = q.top().second;
            q.pop();
            if (vis[u])
                continue;
            vis[u] = true;
            for (auto [v, w] : g[u])
            {
                if (dist[u] < INF && dist[v] > dist[u] + w)
                {
                    dist[v] = dist[u] + w;
                    q.emplace(dist[v], v);
                }
            }
        }
    }
    // 构造函数：n个节点，k个关键点
    SteinerTree(int _n, const vector<tuple<int, int, int>> &edges, const vector<int> &p)
        : n(_n), k((int)p.size())
    {
        g.resize(n + 1);
        dp.resize(1 << k, vector<i64>(n + 1, INF));
        for (auto [u, v, w] : edges)
        {
            g[u].emplace_back(v, w);
            g[v].emplace_back(u, w);
        }
        for (int i = 0; i < (int)p.size(); ++i)
            dp[1 << i][p[i]] = 0;
    }
    // 计算最小斯坦纳树的总权重
    auto solve()
    {
        for (int S = 1; S < (1 << k); ++S)
        {
            // 子集转移
            for (int i = 1; i <= n; ++i)
                for (int subs = S & (S - 1); subs; subs = S & (subs - 1))
                    if (dp[subs][i] < INF && dp[S ^ subs][i] < INF)
                        dp[S][i] = min(dp[S][i], dp[subs][i] + dp[S ^ subs][i]);
            // Dijkstra松弛
            dijkstra(dp[S]);
        }
        i64 ans = INF;
        for (int i = 1; i <= n; ++i)
            ans = min(ans, dp[(1 << k) - 1][i]);
        return ans;
    }
};
