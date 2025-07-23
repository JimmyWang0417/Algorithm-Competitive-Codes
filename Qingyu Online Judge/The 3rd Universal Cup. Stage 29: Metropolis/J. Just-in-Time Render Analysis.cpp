#include <bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
constexpr int N = 1e6 + 5;
struct Tree
{
    int tag;
    inline void update(int _val)
    {
        tag = _val;
    }
} tree[N * 4];
#define lc (rt << 1)
#define rc (rt << 1 | 1)
inline void pushdown(int rt)
{
    if (tree[rt].tag != -1)
    {
        tree[lc].update(tree[rt].tag);
        tree[rc].update(tree[rt].tag);
        tree[rt].tag = -1;
    }
}
inline void build(int rt, int l, int r)
{
    tree[rt].tag = 0;
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
}
inline void update(int rt, int l, int r, int x, int y, int val)
{
    if (r < x || l > y)
        return;
    if (x <= l && r <= y)
        return tree[rt].update(val);
    int mid = (l + r) >> 1;
    pushdown(rt);
    update(lc, l, mid, x, y, val);
    update(rc, mid + 1, r, x, y, val);
}
inline int query(int rt, int l, int r, int pos)
{
    if (l == r)
        return tree[rt].tag;
    int mid = (l + r) >> 1;
    pushdown(rt);
    if (pos <= mid)
        return query(lc, l, mid, pos);
    else
        return query(rc, mid + 1, r, pos);
}
int n, m;
struct node
{
    int x1, y1, x2, y2;
} a[N];
int p[N], tot;
vector<pair<int, int>> g;
vector<int> G[N];
int par[N];
int fa[N][23], dep[N];
int dfn[N], rk[N], dfstime;
inline void dfs(int u)
{
    rk[dfn[u] = ++dfstime] = u;
    dep[u] = dep[fa[u][0] = par[u]] + 1;
    for (int i = 0; i < 20; ++i)
        fa[u][i + 1] = fa[fa[u][i]][i];
    for (auto v : G[u])
        dfs(v);
}
inline int LCA(int u, int v)
{
    if (dep[u] < dep[v])
        swap(u, v);
    for (int i = 20; i >= 0; --i)
        if (dep[fa[u][i]] >= dep[v])
            u = fa[u][i];
    if (u == v)
        return u;
    for (int i = 20; i >= 0; --i)
        if (fa[u][i] != fa[v][i])
        {
            u = fa[u][i];
            v = fa[v][i];
        }
    return fa[u][0];
}
#define lowbit(x) ((x) & (-x))
int c[N];
inline void update(int pos, int val)
{
    for (int i = pos; i <= n; i += lowbit(i))
        c[i] += val;
}
inline void update(int l, int r, int val)
{
    update(l, val);
    update(r + 1, -val);
}
inline int query(int pos)
{
    int res = 0;
    for (int i = pos; i; i -= lowbit(i))
        res += c[i];
    return res;
}
inline void _main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
    {
        cin >> a[i].x1 >> a[i].y1 >> a[i].x2 >> a[i].y2;
        p[++tot] = a[i].y1, p[++tot] = a[i].y2;
        g.emplace_back(a[i].x1, i), g.emplace_back(a[i].x2, -i);
    }
    sort(g.begin(), g.end());

    sort(p + 1, p + 1 + tot);
    tot = (int)(unique(p + 1, p + 1 + tot) - p - 1);
    build(1, 1, tot);

    for (auto [x, i] : g)
        if (i > 0)
        {
            int l = (int)(lower_bound(p + 1, p + 1 + tot, a[i].y1) - p);
            int r = (int)(lower_bound(p + 1, p + 1 + tot, a[i].y2) - p);
            par[i] = query(1, 1, tot, l);
            update(1, 1, tot, l, r, i);
        }
        else
        {
            int l = (int)(lower_bound(p + 1, p + 1 + tot, a[-i].y1) - p);
            int r = (int)(lower_bound(p + 1, p + 1 + tot, a[-i].y2) - p);
            update(1, 1, tot, l, r, par[-i]);
        }

    for (int i = 1; i <= n; ++i)
        G[par[i]].emplace_back(i);


    dfs(0);
    set<pair<int, int>> se;

    for (int i = 1; i <= m; ++i)
    {
        char s;
        int x;
        cin >> s >> x;
        if (s == '^')
        {
            auto it = se.find(make_pair(dfn[x], x));
            if (it != se.end())
            {
                it = se.erase(it);
                int y = (it != se.end() ? LCA(it->second, x) : 0);
                if (it != se.begin())
                {
                    int z = LCA(prev(it)->second, x);
                    if (dep[z] > dep[y])
                        y = z;
                }
                update(dep[y], dep[x] - 1, -1);
            }
            else
            {
                it = se.upper_bound(make_pair(dfn[x], x));
                int y = (it != se.end() ? LCA(it->second, x) : 0);
                if (it != se.begin())
                {
                    int z = LCA(prev(it)->second, x);
                    if (dep[z] > dep[y])
                        y = z;
                }
                update(dep[y], dep[x] - 1, 1);
                se.emplace(dfn[x], x);
            }
        }
        else
            cout << query(x + 1) << '\n';
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--)
        _main();
    return 0;
}