struct SteinerTree
{
    int n, k;
    vector<vector<int>> dp;
    vector<vector<pair<int, int>>> g;
    auto dijkstra(vector<int> &dist)
    {
        vector<bool> vis(n + 1, false);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;

        for (int i = 1; i <= n; ++i)
            if (dist[i] < INT_MAX / 2)
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
                if (dist[v] > dist[u] + w)
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
        dp.resize(1 << k, vector<int>(n + 1, INT_MAX));
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
                    dp[S][i] = min(dp[S][i], dp[subs][i] + dp[S ^ subs][i]);
            // Dijkstra松弛
            dijkstra(dp[S]);
        }

        int ans = INT_MAX;
        for (int i = 1; i <= n; ++i)
            ans = min(ans, dp[(1 << k) - 1][i]);
        return ans;
    }
};