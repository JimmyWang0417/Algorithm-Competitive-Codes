#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr int N = 1e6 + 5;
constexpr int mod = 998244353;
int n, m;
struct Edge
{
    int next, to;
    bool vis;
} edge[N * 2];
int head[N], num_edge = 1;
inline void add_edge(int from, int to)
{
    edge[++num_edge].next = head[from];
    edge[num_edge].to = to;
    edge[num_edge].vis = false;
    head[from] = num_edge;
}
int deg[N];
int top, tot;
pair<int, int> st[N], p[N];
bool vis[N];
inline void dfs(int u, int lasedge)
{
    vis[u] = true;
    for (int &i = head[u]; i; i = edge[i].next)
    {
        if (edge[i].vis)
            continue;
        int v = edge[i].to;
        edge[i].vis = edge[i ^ 1].vis = true;
        dfs(v, i);
    }
    p[++tot] = make_pair(u, lasedge / 2);
}
bool exist[N];
int col[N], color;
inline void clear()
{
    for (int i = 1; i <= n; ++i)
    {
        head[i] = 0;
        deg[i] = 0;
        vis[i] = false;
    }
    num_edge = 1;
    top = tot = color = 0;
}
inline void _main()
{
    cin >> n >> m;
    for (int i = 1; i <= m; ++i)
    {
        int u, v;
        cin >> u >> v;
        add_edge(u, v);
        add_edge(v, u);
        ++deg[u], ++deg[v];
    }
    int las = 0;
    for (int i = 1; i <= n; ++i)
        if (deg[i] & 1)
        {
            if (las)
            {
                add_edge(i, las);
                add_edge(las, i);
                las = 0;
            }
            else
                las = i;
        }
    for (int S = 1; S <= n; ++S)
    {
        if (vis[S])
            continue;
        dfs(S, 0);
        for (int i = tot; i >= 1; --i)
        {
            auto [u, le] = p[i];
            if (!exist[u])
            {
                exist[u] = true;
                st[++top] = make_pair(u, le);
            }
            else
            {
                col[le] = ++color;
                while (st[top].first != u)
                {
                    exist[st[top].first] = false;
                    col[st[top--].second] = color;
                }
            }
        }
        while (top)
            exist[st[top--].first] = false;
        top = 0, tot = 0;
    }
    for (int i = 1; i <= m; ++i)
        cout << col[i] << ' ';
    cout << '\n';
    clear();
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    cin >> T;
    while (T--)
        _main();
    return 0;
}