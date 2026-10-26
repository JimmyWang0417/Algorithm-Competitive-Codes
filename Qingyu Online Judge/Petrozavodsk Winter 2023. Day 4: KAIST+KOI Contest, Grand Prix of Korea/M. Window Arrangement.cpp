#include <bits/stdc++.h>
using namespace std;
typedef int64_t i64;
struct MinCostMaxFlow
{
    int n;
    int S, T;
    struct node
    {
        int next, to, cap, cost;
    };
    int numEdge;
    vector<int> head, cur;
    vector<i64> dis;
    vector<bool> exist;
    vector<node> edge;
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
    MinCostMaxFlow() = default;
    MinCostMaxFlow(int _n, int _S, int _T, const vector<array<int, 4>> &edges)
    {
        n = _n, S = _S, T = _T;
        head.resize(n + 5), cur.resize(n + 5), dis.resize(n + 5);
        exist.resize(n + 5);
        numEdge = 1;
        edge.resize(edges.size() * 2 + 5);
        for (auto [u, v, cap, cost] : edges)
            addEdge(u, v, cap, cost);
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
    auto solve()
    {
        int flow = 0;
        i64 res = 0;
        while (spfa())
        {
            int f = dinic(S, INT_MAX);
            flow += f, res += f * dis[T];
        }
        return make_pair(flow, res);
    }
};
struct Main
{
    int n, m;
    vector<vector<int>> a, b;
    int S = 0, T = 0;
    vector<vector<int>> A, B;
    Main()
    {
        cin >> n >> m;
        int tot = 0;
        a.resize(n, vector<int>(m));
        b.resize(n, vector<int>(m));
        A.resize(n, vector<int>(m));
        B.resize(n, vector<int>(m));
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                cin >> a[i][j];
                A[i][j] = ++tot;
            }
        }
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                cin >> b[i][j];
        vector<array<int, 4>> edges;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                edges.push_back({S, A[i][j], b[i][j], 0});
        auto check = [&](int x, int y)
        {
            return x >= 0 && x < n && y >= 0 && y < m;
        };
        T = ++tot;
        for (int i = -1; i < n; ++i)
            for (int j = -1; j < m; ++j)
            {
                {
                    int u = ++tot;
                    if (check(i, j))
                        edges.push_back({A[i][j], u, 1, 0});
                    if (check(i + 1, j))
                        edges.push_back({A[i + 1][j], u, 1, 0});
                    edges.push_back({u, T, 1, 0});
                    if (check(i, j) && check(i + 1, j))
                        edges.push_back({u, T, 1, a[i][j] * a[i + 1][j]});
                }
                {
                    int u = ++tot;
                    if (check(i, j))
                        edges.push_back({A[i][j], u, 1, 0});
                    if (check(i, j + 1))
                        edges.push_back({A[i][j + 1], u, 1, 0});
                    edges.push_back({u, T, 1, 0});
                    if (check(i, j) && check(i, j + 1))
                        edges.push_back({u, T, 1, a[i][j] * a[i][j + 1]});
                }
            }
        auto e = MinCostMaxFlow(tot, S, T, edges);
        auto [flow, cost] = e.solve();
        cout << cost << '\n';
    }
};
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    while (T--)
        Main();
    return 0;
}
