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
template <typename T = int>
constexpr auto quickpow(i64 a, T b = mod - 2)
{
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
struct Main
{
    int n, m, W, H, K;
    int S, T;
    vector<int> fa, a;
    vector<vector<int>> G;
    struct Edge
    {
        int next, to, flow, cap;
        i64 cost;
    };
    vector<Edge> edge;
    vector<int> head, cur;
    vector<bool> exist;
    vector<i64> dis;
    auto addEdge(int from, int to, int cap, i64 cost, bool flag = true) -> void
    {
        edge.emplace_back(head[from], to, 0, cap, cost);
        head[from] = (int)edge.size() - 1;
        if (flag)
            addEdge(to, from, 0, -cost, false);
    }
    auto spfa()
    {
        ranges::fill(dis, LLONG_MAX / 2);
        ranges::fill(exist, false);
        cur = head;
        queue<int> q;
        q.emplace(S);
        dis[S] = 0;
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            exist[u] = false;
            for (int i = head[u]; i; i = edge[i].next)
            {
                int v = edge[i].to;
                if (edge[i].cap > edge[i].flow && dis[v] > dis[u] + edge[i].cost)
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
        return dis[T] < LLONG_MAX / 2;
    }
    auto dinic(int u, int flow)
    {
        if (u == T)
            return flow;
        int res = 0;
        exist[u] = true;
        for (auto &i = cur[u]; i; i = edge[i].next)
        {
            int v = edge[i].to;
            if (!exist[v] && edge[i].cap > edge[i].flow && dis[v] == dis[u] + edge[i].cost)
            {
                int f = dinic(v, min(edge[i].cap - edge[i].flow, flow));
                if (f)
                {
                    res += f;
                    edge[i].flow += f;
                    edge[i ^ 1].flow -= f;
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
    Main() : edge(2)
    {
        cin >> n >> m >> W >> H >> K;
        fa.resize(W + H + 5), a.resize(W + 1);
        for (int i = 1; i <= W + H; ++i)
            cin >> fa[i];
        for (int i = 1; i <= W; ++i)
            cin >> a[i];
        S = 0, T = W + H + n * m + 1;
        head.resize(T + 1);
        dis.resize(T + 1), exist.resize(T + 1);
        vector<int> id(W + 1);
        for (int i = 1; i <= W; ++i)
        {
            addEdge(fa[i], i, K, 0);
            id[i] = (int)edge.size() - 2;
        }
        for (int i = 1; i <= H; ++i)
        {
            int l;
            cin >> l;
            addEdge(fa[W + i], W + i, 1, 0);
            while (l--)
            {
                int x, y;
                cin >> x >> y;
                addEdge(W + i, W + H + (x - 1) * m + y, 1, 0);
            }
        }
        for (int i = 1; i <= n * m; ++i)
            addEdge(W + H + i, T, 1, 0);
        i64 res = 0;
        for (int t = 1; t <= K; ++t)
        {
            if (spfa())
            {
                int f = dinic(S, 1);
                res += f * dis[T];
            }
            else
            {
                cout << "-1\n";
                return;
            }
            for (int i = 1; i <= W; ++i)
            {
                int u = id[i], f = edge[u].flow;
                edge[id[i]].cost = (i64)f * (a[i] - a[fa[i]]);
                edge[id[i] ^ 1].cost = -(i64)(f - 1) * (a[i] - a[fa[i]]);
            }
        }
        cout << res << '\n';
    }
};
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--)
        Main();
    return 0;
}
