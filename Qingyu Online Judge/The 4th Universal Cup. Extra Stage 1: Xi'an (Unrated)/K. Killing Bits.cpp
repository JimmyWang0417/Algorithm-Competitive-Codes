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
constexpr int mod = 998244353;

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

    auto normal(int _n, const vector<array<int, 3>> &e, int s, int t)
    {
        S = s, T = t;
        init(_n, (int)e.size());
        for (auto [u, v, c] : e)
            addEdge(u, v, c);
        return solve();
    }
};
struct Main
{
    int n;
    Main()
    {
        cin >> n;
        vector<int> a(n + 5), b(n + 5);
        for (int i = 1; i <= n; ++i)
            cin >> a[i];
        for (int i = 1; i <= n; ++i)
            cin >> b[i];
        if (a == b)
        {
            cout << "Yes\n";
            return;
        }
        for (int i = 1; i <= n; ++i)
            if ((a[i] & b[i]) != b[i])
            {
                cout << "No\n";
                return;
            }
        int S = n, T = n + 1;
        vector<array<int, 3>> edges;
        for (int i = 0; i < n; ++i)
            edges.push_back({S, i, 1});
        for (int i = 1; i <= n; ++i)
            edges.push_back({b[i], T, 1});
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; (1 << j) <= i; ++j)
                if ((i >> j) & 1)
                    edges.push_back({i, i ^ (1 << j), INT_MAX});
        }
        cout << ((networkFlow().normal(n + 1, edges, S, T) == n) ? "Yes\n" : "No\n");
    }
};
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    cin >> T;
    while (T--)
        Main();
    return 0;
}
