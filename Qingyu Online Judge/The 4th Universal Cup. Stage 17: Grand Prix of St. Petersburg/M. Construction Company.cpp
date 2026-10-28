#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>
using namespace std;
typedef int64_t i64;
typedef uint64_t u64;
typedef __int128_t i128;
typedef __uint128_t u128;
typedef __float80 f80;
typedef __float128 f128;
constexpr int mod = 1e6 + 3;
template <typename T = int>
constexpr auto quickpow(i64 a, T b = mod - 2)
{
    a %= mod;
    i64 res = 1;
    while (b)
    {
        if (b & 1)
            (res *= a) %= mod;
        (a *= a) %= mod;
        b >>= 1;
    }
    return res;
}
struct NetworkFlow
{
    vector<int> head, cur, dis;
    vector<bool> exist;
    struct Edge
    {
        int next, to, cap;
    };
    vector<Edge> edge;
    int numEdge;
    int n, S, T;
    auto init(int _n, int _m)
    {
        n = _n;
        numEdge = 1;
        head.resize(n + 5);
        exist.resize(n + 5);
        dis.resize(n + 5);
        edge.resize(2 + 2 * _m);
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
    auto bfs() -> bool
    {
        cur = head;
        ranges::fill(dis, 0);
        ranges::fill(exist, false);
        queue<int> q;
        q.push(S);
        dis[S] = 1;
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            for (int i = head[u]; i; i = edge[i].next)
            {
                int v = edge[i].to;
                if (!dis[v] && edge[i].cap > 0)
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
            if (!exist[v] && dis[v] == dis[u] + 1 && edge[i].cap > 0)
            {
                int f = dinic(v, min(edge[i].cap, flow));
                if (f)
                {
                    res += f;
                    flow -= f;
                    edge[i].cap -= f;
                    edge[i ^ 1].cap += f;
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
        int res = 0;
        while (bfs())
            res += dinic(S, INT_MAX);
        return res;
    }
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
};
struct Main
{
    int a, b, m;
    Main()
    {
        cin >> a >> b >> m;
        vector<array<int, 4>> e;
        vector<int> pre(2 * m + 5);
        int S = 2 * m + 2, T = 2 * m + 1;
        for (int i = 1; i <= m; ++i)
        {
            int op, l, r;
            cin >> op >> l >> r;
            e.push_back({l, r + 1, op == 2, 1});
            pre[l]++, pre[r + 1]--;
        }
        e.push_back({S, 1, 0, a});
        for (int i = 1; i <= 2 * m; ++i)
        {
            pre[i] += pre[i - 1];
            if (a - (pre[i] - b) < 0)
            {
                cout << "No\n";
                return;
            }
            e.push_back({i, i + 1, 0, a - (pre[i] - b)});
        }
        cout << (NetworkFlow().maxFlow(2 * m + 2, e, S, T) == a ? "Yes\n" : "No\n");
    }
};
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    cin >> T;
    while (T--)
        Main();
    return 0;
}
