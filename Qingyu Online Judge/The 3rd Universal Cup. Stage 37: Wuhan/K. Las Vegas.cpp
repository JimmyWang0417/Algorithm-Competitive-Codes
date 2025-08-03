#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr int N = 1.5e5 + 5;
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
inline void _main()
{
    int n, m;
    cin >> n >> m;
    vector<array<int, 5>> edge;
    vector<int> cnt(m + 5);
    const int S = n + m + 2, T = n + m + 3, me = m + 1;
    for (int i = 1; i <= n; ++i)
    {
        map<int, int> mp;
        for (int j = 1; j <= m; ++j)
        {
            int x;
            cin >> x;
            if (mp.find(x) != mp.end())
                mp[x] = 0;
            else
                mp[x] = j;
        }
        int mx = 0, id = 0;
        auto it = mp.rbegin();
        for (; it != mp.rend(); ++it)
        {
            auto [x, y] = *it;
            if (y)
            {
                mx = x;
                id = y;
                break;
            }
        }
        assert(!(mx && it == mp.rend()));
        if (mx)
            edge.push_back({id, m + 1 + i, 0, 1, 0});
        else
            edge.push_back({S, m + 1 + i, 0, 1, 0});

        if (mx)
            ++cnt[id];

        for (int j = mx + 1; j; ++j)
        {
            if (mp.find(j) != mp.end())
                continue;
            edge.push_back({m + 1 + i, me, 0, 1, j});
            break;
        }
        if (mx)
        {
            mp.erase(0);
            for (++it; it != mp.rend(); ++it)
                if (it->second)
                {
                    edge.push_back({m + 1 + i, it->second, 0, 1, mx});
                    break;
                }
            if (it == mp.rend())
                edge.push_back({m + 1 + i, T, 0, 1, mx});
        }
    }
    ll ans = LONG_LONG_MAX;
    vector<int> answer(n + 5);
    for (int mid = 0; mid <= n; ++mid)
    {
        auto e = edge;
        for (int i = 1; i <= m; ++i)
        {
            if (cnt[i] > mid)
                e.push_back({S, i, cnt[i] - mid, cnt[i], 0});
            else
            {
                e.push_back({S, i, 0, cnt[i], 0});
                e.push_back({i, T, 0, mid - cnt[i], 0});
            }
        }
        e.push_back({me, T, mid, mid, 0});
        networkFlow::minCostFlow flow;
        auto [u, v] = flow.special(n + m + 3, e, S, T);
        if (u != -1 && ans > v)
        {
            ans = v;
            answer = flow.main(n, m);
        }
    }
    for (int i = 1; i <= n; ++i)
        cout << answer[i] << ' ';
    cout << '\n';
}
inline void _clear()
{
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    cin >> T;
    for (int cas = 1; cas <= T; ++cas)
    {
        _main();
        _clear();
    }
    return 0;
}