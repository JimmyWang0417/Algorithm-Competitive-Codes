#include <bits/stdc++.h>
#define N 100005
using namespace std;
inline int read()
{
    int x = 0, f = 1;
    char c = getchar();
    while (c < 48)
    {
        if (c == '-')
            f = 0;
        c = getchar();
    }
    while (c >= 48)
        x = (x << 3) + (x << 1) + (c ^ 48), c = getchar();
    return f ? x : -x;
}
int n;
int a[N], p[N], fa[N], ans[N];
vector<int> g[N], G[N];
bool cmp(int x, int y) { return a[x] < a[y]; }
int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
void merge(int x, int y)
{
    G[x].push_back(find(y));
    fa[find(y)] = x;
}
void dfs(int u)
{
    for (auto v : G[u])
        ans[v] = ans[u] + 1, dfs(v);
}
void solve()
{
    n = read();
    for (int i = 1; i <= n; i++)
        g[i].clear(), G[i].clear();
    for (int i = 1; i < n; i++)
    {
        int u = read(), v = read();
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for (int i = 1; i <= n; i++)
        a[i] = read(), fa[i] = p[i] = i;
    sort(p + 1, p + n + 1, cmp);
    for (int i = 1; i <= n; i++)
    {
        int u = p[i];
        for (auto v : g[u])
            if (a[v] < a[u])
                merge(u, v);
    }
    ans[p[n]] = 1;
    dfs(p[n]);
    for (int i = 1; i <= n; i++)
        printf("%d\n", ans[i]);
}
signed main()
{
    int T = read();
    while (T--)
        solve();
}