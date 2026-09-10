namespace NetworkFlow
{
    template <typename T = i64>
    struct CancelCycle
    {
        struct edges
        {
            int next, to, cap, origin;
            T cost;
        };
        int n, s, t, numEdge = 1;
        vector<int> head, cur, dep, pre, cnt;
        vector<T> dis;
        vector<bool> exist;
        vector<edges> edge;
        CancelCycle(int _n, const vector<tuple<int, int, int, T>> &_edges, int _s, int _t)
            : n(_n), s(_s), t(_t), head(n + 1), cur(n + 1), dep(n + 1), pre(n + 1),
              cnt(n + 1), dis(n + 1), exist(n + 1), edge(2 * _edges.size() + 2)
        {
            for (auto [u, v, cap, cost] : _edges)
                addEdge(u, v, cap, cost);
        }
        auto addEdge(int from, int to, int cap, T cost, bool flag = true) -> void
        {
            edge[++numEdge] = {head[from], to, cap, cap, cost};
            head[from] = numEdge;
            if (flag)
                addEdge(to, from, 0, -cost, false);
        }
        auto bfs()
        {
            fill(dep.begin(), dep.end(), 0);
            queue<int> que;
            dep[s] = 1;
            que.push(s);
            while (!que.empty())
            {
                int u = que.front();
                que.pop();
                for (int i = head[u]; i; i = edge[i].next)
                {
                    int v = edge[i].to;
                    if (edge[i].cap && !dep[v])
                        dep[v] = dep[u] + 1, que.push(v);
                }
            }
            return dep[t];
        }
        auto dinic(int u, int flow)
        {
            if (u == t)
                return flow;
            int res = 0;
            for (int &i = cur[u]; i && flow; i = edge[i].next)
            {
                int v = edge[i].to;
                if (edge[i].cap && dep[v] == dep[u] + 1)
                {
                    int f = dinic(v, min(flow, edge[i].cap));
                    edge[i].cap -= f, edge[i ^ 1].cap += f;
                    flow -= f, res += f;
                }
            }
            return res;
        }
        auto maxFlow()
        {
            int flow = 0;
            while (bfs())
                cur = head, flow += dinic(s, INT_MAX);
            return flow;
        }
        auto spfa()
        {
            fill(dis.begin(), dis.end(), 0);
            fill(pre.begin(), pre.end(), 0);
            fill(cnt.begin(), cnt.end(), 0);
            fill(exist.begin(), exist.end(), true);
            queue<int> que;
            for (int i = 1; i <= n; ++i)
                que.push(i);
            while (!que.empty())
            {
                int u = que.front();
                que.pop(), exist[u] = false;
                for (int i = head[u]; i; i = edge[i].next)
                {
                    int v = edge[i].to;
                    if (edge[i].cap && dis[v] > dis[u] + edge[i].cost)
                    {
                        dis[v] = dis[u] + edge[i].cost;
                        pre[v] = i;
                        cnt[v] = cnt[u] + 1;
                        if (cnt[v] >= n)
                            return v;
                        if (!exist[v])
                            que.push(v), exist[v] = true;
                    }
                }
            }
            return -1;
        }
        auto cancel(int x)
        {
            for (int i = 0; i < n; ++i)
                x = edge[pre[x] ^ 1].to;
            int start = x, flow = INT_MAX;
            T cost = 0;
            do
            {
                int i = pre[x];
                flow = min(flow, edge[i].cap);
                cost += edge[i].cost;
                x = edge[i ^ 1].to;
            } while (x != start);
            do
            {
                int i = pre[x];
                edge[i].cap -= flow, edge[i ^ 1].cap += flow;
                x = edge[i ^ 1].to;
            } while (x != start);
            return cost * flow;
        }
        auto cost() const
        {
            T res = 0;
            for (int i = 2; i <= numEdge; i += 2)
                res += (T)(edge[i].origin - edge[i].cap) * edge[i].cost;
            return res;
        }
        auto solve() -> pair<int, T>
        {
            int flow = maxFlow();
            T res = cost();
            for (int x = spfa(); x != -1; x = spfa())
                res += cancel(x);
            return {flow, res};
        }
    };
}
