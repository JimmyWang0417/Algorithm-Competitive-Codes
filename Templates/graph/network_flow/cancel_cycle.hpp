template <typename T = i64>
struct CancelCycle
{
    int n;
    vector<T> dis;
    vector<pair<int, int>> pre;
    vector<int> cnt;
    vector<bool> exist;
    CancelCycle(int _n) : n(_n), dis(n + 1), pre(n + 1), cnt(n + 1), exist(n + 1) {}
    template <typename E, typename F>
    auto spfa(const vector<vector<E>> &G, F valid)
    {
        fill(dis.begin(), dis.end(), 0);
        fill(pre.begin(), pre.end(), pair(-1, -1));
        fill(cnt.begin(), cnt.end(), 0);
        fill(exist.begin(), exist.end(), true);
        queue<int> que;
        for (int i = 1; i <= n; ++i)
            que.push(i);
        while (!que.empty())
        {
            int u = que.front();
            que.pop(), exist[u] = false;
            for (int i = 0; i < (int)G[u].size(); ++i)
            {
                const auto &e = G[u][i];
                if (valid(e) && dis[e.to] > dis[u] + e.cost)
                {
                    dis[e.to] = dis[u] + e.cost;
                    pre[e.to] = {u, i};
                    cnt[e.to] = cnt[u] + 1;
                    if (cnt[e.to] >= n)
                        return e.to;
                    if (!exist[e.to])
                        que.push(e.to), exist[e.to] = true;
                }
            }
        }
        return -1;
    }
};
