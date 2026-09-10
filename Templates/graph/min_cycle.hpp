template <typename T = i64>
struct MinimumCycle
{
    static constexpr T inf = numeric_limits<T>::max() / 4;
    int n;
    T weight = inf;
    vector<int> path;
    vector<vector<T>> G, dis;
    vector<vector<int>> pos;
    auto getpath(int u, int v) -> void
    {
        if (!pos[u][v])
            return;
        int k = pos[u][v];
        getpath(u, k);
        path.emplace_back(k);
        getpath(k, v);
    }
    MinimumCycle(int _n, const vector<tuple<int, int, T>> &edges)
        : n(_n), G(n + 1, vector<T>(n + 1, inf)), pos(n + 1, vector<int>(n + 1))
    {
        for (int i = 1; i <= n; ++i)
            G[i][i] = 0;
        for (auto [u, v, w] : edges)
            G[u][v] = G[v][u] = min(G[u][v], w);
        dis = G;
        for (int k = 1; k <= n; ++k)
        {
            for (int i = 1; i < k; ++i)
                for (int j = 1; j < k; ++j)
                {
                    if (i == j)
                        continue;
                    T now = dis[i][j] + G[j][k] + G[k][i];
                    if (now < weight)
                    {
                        weight = now;
                        path = {i};
                        getpath(i, j);
                        path.emplace_back(j);
                        path.emplace_back(k);
                    }
                }
            for (int i = 1; i <= n; ++i)
                for (int j = 1; j <= n; ++j)
                    if (dis[i][j] > dis[i][k] + dis[k][j])
                    {
                        dis[i][j] = dis[i][k] + dis[k][j];
                        pos[i][j] = k;
                    }
        }
    }
};
