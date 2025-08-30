namespace networkFlow
{
    struct networkFlow
    {
        vector<int> head, cur, dis;
        vector<bool> exist;
        struct edges
        {
            int next, to, cap;
        };
        vector<edges> edge; // next, to, cap
        int numEdge;
        int n, S, T;
        auto init(int _n, int _m)
        {
            n = _n;
            numEdge = 1;
            head.resize(n + 5);
            dis.resize(n + 5);
            exist.resize(n + 5);
            edge.resize(2 + 2 * _m);
        }
        auto bfs() -> bool
        {
            cur = head;
            fill(dis.begin(), dis.end(), 0);
            fill(exist.begin(), exist.end(), 0);
            queue<int> q;
            dis[S] = 1;
            q.push(S);
            while (!q.empty())
            {
                int u = q.front();
                q.pop();
                for (int i = head[u]; i; i = edge[i].next)
                {
                    int v = edge[i].to;
                    if (!dis[v] && edge[i].cap)
                    {
                        dis[v] = dis[u] + 1;
                        q.push(v);
                    }
                }
            }
            return dis[T];
        }
        auto dinic(int u, int flow)
        {
            if (u == T)
                return flow;
            int res = 0;
            exist[u] = true;
            for (int &i = cur[u]; i; i = edge[i].next)
            {
                int v = edge[i].to;
                if (!exist[v] && dis[v] == dis[u] + 1 && edge[i].cap)
                {
                    int f = dinic(v, min(flow, edge[i].cap));
                    if (f)
                    {
                        edge[i].cap -= f;
                        edge[i ^ 1].cap += f;
                        res += f;
                        flow -= f;
                        if (!flow)
                        {
                            exist[u] = false;
                            break;
                        }
                    }
                }
            }
            return res;
        }
        auto addEdge(int from, int to, int cap, bool flag = true) -> void
        {
            edge[++numEdge].next = head[from];
            edge[numEdge].to = to;
            edge[numEdge].cap = cap;
            head[from] = numEdge;
            if (flag)
                addEdge(to, from, 0, false);
        }

        inline auto solve()
        {
            int flow = 0;
            while (bfs())
                flow += dinic(S, INT_MAX);
            return flow;
        }

        // 网络流
        auto normal(int _n, const vector<array<int, 3>> &e, int s, int t)
        {
            S = s, T = t;
            init(_n, (int)e.size());
            for (auto [u, v, c] : e)
                addEdge(u, v, c);
            return solve();
        }

        // 有源上下界最大流
        auto maxFlow(int _n, const vector<array<int, 4>> &e, int s, int t)
        { // 返回-1则说明没有可行流
            S = 0, T = _n + 1;
            init(_n, _n + (int)e.size() + 1);
            vector<int> deg(n + 5);
            for (auto [u, v, l, r] : e)
            {
                addEdge(u, v, r - l);
                deg[u] -= l, deg[v] += l;
            }
            auto lasHead = head;

            int sum = 0;
            for (int i = 1; i <= n; ++i)
            {
                if (deg[i] > 0)
                {
                    addEdge(S, i, deg[i]);
                    sum += deg[i];
                }
                else if (deg[i] < 0)
                    addEdge(i, T, -deg[i]);
            }
            addEdge(t, s, INT_MAX);
            if (solve() < sum)
                return -1;

            int flow = edge[numEdge].cap;
            head = lasHead;
            S = s, T = t;

            return flow + solve();
        }
        // 有源上下界最小流
        auto minFlow(int _n, const vector<array<int, 4>> &e, int s, int t)
        { // 返回-1则说明没有可行流
            S = 0, T = _n + 1;
            init(_n, _n + (int)e.size() + 1);
            vector<int> deg(n + 5);
            for (auto [u, v, l, r] : e)
            {
                addEdge(u, v, r - l);
                deg[u] -= l, deg[v] += l;
            }
            auto lasHead = head;

            int sum = 0;
            for (int i = 1; i <= n; ++i)
            {
                if (deg[i] > 0)
                {
                    addEdge(S, i, deg[i]);
                    sum += deg[i];
                }
                else if (deg[i] < 0)
                    addEdge(i, T, -deg[i]);
            }
            addEdge(t, s, INT_MAX);
            if (solve() < sum)
                return -1;

            int flow = edge[numEdge].cap;
            head = lasHead;
            S = t, T = s;

            return flow - solve();
        }
    };
}