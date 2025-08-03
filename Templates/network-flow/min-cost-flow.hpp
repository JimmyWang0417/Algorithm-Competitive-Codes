namespace networkFlow
{
    struct minCostFlow
    {
        vector<ll> dis;
        vector<int> head, cur;
        vector<bool> exist;
        struct edges
        {
            int next, to, cap, cost;
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
        auto spfa()
        {
            cur = head;
            fill(dis.begin(), dis.end(), LONG_LONG_MAX);
            fill(exist.begin(), exist.end(), 0);
            queue<int> q;
            dis[S] = 0;
            q.push(S);
            while (!q.empty())
            {
                int u = q.front();
                q.pop();
                exist[u] = false;
                for (int i = head[u]; i; i = edge[i].next)
                {
                    int v = edge[i].to;
                    if (dis[v] > dis[u] + edge[i].cost && edge[i].cap)
                    {
                        dis[v] = dis[u] + edge[i].cost;
                        if (!exist[v])
                        {
                            q.push(v);
                            exist[v] = true;
                        }
                    }
                }
            }
            return dis[T] < LONG_LONG_MAX;
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
                if (!exist[v] && dis[v] == dis[u] + edge[i].cost && edge[i].cap)
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
        auto addEdge(int from, int to, int cap, int cost, bool flag = true) -> void
        {
            edge[++numEdge].next = head[from];
            edge[numEdge].to = to;
            edge[numEdge].cap = cap;
            edge[numEdge].cost = cost;
            head[from] = numEdge;
            if (flag)
                addEdge(to, from, 0, -cost, false);
        }

        inline auto solve() -> pair<int, ll>
        {
            int flow = 0;
            ll res = 0;
            while (spfa())
            {
                int f = dinic(S, INT_MAX);
                flow += f;
                res += dis[T] * f;
            }
            return {flow, res};
        }

        // 最小费用最大流
        auto normal(int _n, const vector<array<int, 4>> &e, int s, int t)
        {
            S = s, T = t;
            init(_n, (int)e.size());
            for (auto [u, v, c, w] : e)
                addEdge(u, v, c, w);
            return solve();
        }

        // 上下界最小费用可行流
        auto special(int _n, const vector<array<int, 5>> &e, int s, int t) -> pair<int, ll>
        {
            S = 0, T = _n + 1;
            init(_n, _n + (int)e.size() + 1);
            vector<int> deg(n + 5);
            int sum = 0;
            ll cost = 0;
            for (auto [u, v, l, r, w] : e)
            {
                if (l < r)
                    addEdge(u, v, r - l, w);
                deg[u] -= l, deg[v] += l;
                cost += (ll)l * w;
            }
            auto lasHead = head;
            for (int i = 1; i <= n; ++i)
            {
                if (deg[i] > 0)
                {
                    addEdge(S, i, deg[i], 0);
                    sum += deg[i];
                }
                else if (deg[i] < 0)
                    addEdge(i, T, -deg[i], 0);
            }
            addEdge(t, s, INT_MAX, 0);
            auto [f, c] = solve();
            if (f < sum)
                return {-1, 0};

            return {edge[numEdge].cap, cost + c};
        }
        auto main(int _n, int _m)
        {
            vector<int> p(_n + 5);
            for (int i = 2; i <= numEdge; i += 2)
            {
                if (!edge[i].cap && edge[i].cost)
                {
                    int u = edge[i ^ 1].to;
                    if (_m + 1 < u && u <= _m + _n + 1)
                        p[edge[i ^ 1].to - _m - 1] = edge[i].cost;
                }
            }
            return p;
        }

        // 上下界最小费用最大流
        auto maxFlow(int _n, const vector<array<int, 5>> &e, int s, int t) -> pair<int, ll>
        {
            S = 0, T = _n + 1;
            init(_n, _n + (int)e.size() + 1);
            vector<int> deg(n + 5);
            int flow = 0, sum = 0;
            ll cost = 0;
            for (auto [u, v, l, r, w] : e)
            {
                addEdge(u, v, r - l, w);
                deg[u] -= l, deg[v] += l;
                cost += (ll)l * w;
            }
            auto lasHead = head;
            for (int i = 1; i <= n; ++i)
            {
                if (deg[i] > 0)
                {
                    addEdge(S, i, deg[i], 0);
                    sum += deg[i];
                }
                else if (deg[i] < 0)
                    addEdge(i, T, -deg[i], 0);
            }
            addEdge(t, s, INT_MAX, 0);
            auto [f, c] = solve();
            if (f < sum)
                return {-1, 0};
            cost += c;
            lasHead = head;

            flow = edge[numEdge].cap;
            head = lasHead;
            S = s, T = t;
            tie(f, c) = solve();

            return {flow, cost};
        }
    };
}