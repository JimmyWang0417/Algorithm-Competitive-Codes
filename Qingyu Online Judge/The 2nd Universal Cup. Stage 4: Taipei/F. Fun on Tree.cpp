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
struct node
{
    i64 dis;
    int id;
    auto operator<=>(const node &rhs) const
    {
        return dis == rhs.dis ? rhs.id <=> id : dis <=> rhs.dis;
    }
    auto operator+(const i64 &rhs) const
    {
        return node{dis + rhs, id};
    }
    auto operator-(const i64 &rhs) const
    {
        return node{dis - rhs, id};
    }
};
struct SegmentTree
{
    int n;
    struct TreeNode
    {
        node A, B;
        i64 tag;
        auto update(i64 v)
        {
            A = A + v;
            B = B + v;
            tag += v;
        }
    };
#define lc (rt << 1)
#define rc (rt << 1 | 1)
    vector<set<node>> A, B;
    vector<TreeNode> tree;
    SegmentTree() = default;
    SegmentTree(int _n) : n(_n), A(_n + 5), B(_n + 5), tree(_n * 4) {}
    auto pushup(int rt)
    {
        tree[rt].A = max(tree[lc].A, tree[rc].A);
        tree[rt].B = max(tree[lc].B, tree[rc].B);
    }
    auto pushdown(int rt)
    {
        if (tree[rt].tag)
        {
            tree[lc].update(tree[rt].tag);
            tree[rc].update(tree[rt].tag);
            tree[rt].tag = 0;
        }
    }
    auto build(int rt, int l, int r)
    {
        tree[rt].A = tree[rt].B = node{LLONG_MIN / 2, 0};
        if (l == r)
            return;
        int mid = (l + r) >> 1;
        build(lc, l, mid);
        build(rc, mid + 1, r);
    }
    auto modify(int rt, int l, int r, int pos, node val, int typ)
    {
        if (l == r)
        {
            if (typ == 0)
            {
                A[l].insert(val - tree[rt].tag);
                tree[rt].A = (A[l].empty() ? node{LLONG_MIN / 2, 0} : *A[l].rbegin() + tree[rt].tag);
            }
            else if (typ == 1)
            {
                B[l].insert(val - tree[rt].tag);
                tree[rt].B = (B[l].empty() ? node{LLONG_MIN / 2, 0} : *B[l].rbegin() + tree[rt].tag);
            }
            else if (typ == 2)
            {
                A[l].erase(val - tree[rt].tag);
                tree[rt].A = (A[l].empty() ? node{LLONG_MIN / 2, 0} : *A[l].rbegin() + tree[rt].tag);
            }
            else if (typ == 3)
            {
                B[l].erase(val - tree[rt].tag);
                tree[rt].B = (B[l].empty() ? node{LLONG_MIN / 2, 0} : *B[l].rbegin() + tree[rt].tag);
            }
            return;
        }
        int mid = (l + r) >> 1;
        pushdown(rt);
        if (pos <= mid)
            modify(lc, l, mid, pos, val, typ);
        else
            modify(rc, mid + 1, r, pos, val, typ);
        pushup(rt);
    }
    auto update(int rt, int l, int r, int x, int y, i64 val)
    {
        if (r < x || l > y)
            return;
        if (x <= l && r <= y)
            return tree[rt].update(val);
        int mid = (l + r) >> 1;
        pushdown(rt);
        update(lc, l, mid, x, y, val);
        update(rc, mid + 1, r, x, y, val);
        pushup(rt);
    }
    auto query(int rt, int l, int r, int x, int y, bool typ)
    {
        if (r < x || l > y)
            return node{LLONG_MIN / 2, 0};
        if (x <= l && r <= y)
            return !typ ? tree[rt].A : tree[rt].B;
        int mid = (l + r) >> 1;
        pushdown(rt);
        return max(query(lc, l, mid, x, y, typ), query(rc, mid + 1, r, x, y, typ));
    }
    auto build() { return build(1, 1, n); }
    auto modify(int pos, node val, int typ) { return modify(1, 1, n, pos, val, typ); }
    auto update(int x, int y, i64 val) { return update(1, 1, n, x, y, val); }
    auto query(int x, int y, bool typ) { return query(1, 1, n, x, y, typ); }
};
struct Main
{
    int n, m;
    vector<int> a;
    vector<vector<pair<int, int>>> G;
    vector<int> fa, dep;
    vector<int> sze, son;
    vector<i64> dis;
    vector<int> top, btm;
    vector<int> dfn, rk;
    SegmentTree tree;
    int dfstime = 0;
    auto dfs1(int u, int _fa) -> void
    {
        dep[u] = dep[fa[u] = _fa] + 1;
        sze[u] = 1;
        for (auto [v, w] : G[u])
        {
            if (v == _fa)
                continue;
            dis[v] = dis[u] + w;
            dfs1(v, u);
            sze[u] += sze[v];
            if (sze[v] > sze[son[u]])
                son[u] = v;
        }
    }
    auto dfs2(int u, int topf) -> void
    {
        top[u] = topf;
        rk[dfn[u] = ++dfstime] = u;
        if (son[u])
        {
            dfs2(son[u], topf);
            btm[u] = btm[son[u]];
        }
        else
            btm[u] = u;
        for (auto [v, w] : G[u])
        {
            if (dfn[v])
                continue;
            dfs2(v, v);
        }
    }
    vector<node> dp;
    auto dfs3(int u, int _fa) -> void
    {
        dp[u] = {dis[u] - a[u], u};
        tree.modify(dfn[u], node{dis[u] - a[u], u}, 0);
        tree.modify(dfn[u], node{dis[u] - a[u] - 2 * dis[u], u}, 1);
        for (auto [v, w] : G[u])
        {
            if (v == _fa)
                continue;
            dfs3(v, u);
            dp[u] = max(dp[u], dp[v]);
            if (v != son[u])
                tree.modify(dfn[u], dp[v] - 2 * dis[u], 1);
        }
    }
    auto update(int u, int w)
    {
        for (int v = top[u]; fa[v]; v = top[fa[v]])
            tree.modify(dfn[fa[v]], tree.query(dfn[v], dfn[v] + sze[v] - 1, 0) - dis[fa[v]] * 2, 3);
        tree.update(dfn[u], dfn[u] + sze[u] - 1, w);
        for (int v = top[u]; fa[v]; v = top[u = fa[v]])
            tree.modify(dfn[fa[v]], tree.query(dfn[v], dfn[v] + sze[v] - 1, 0) - dis[fa[v]] * 2, 1);
    }
    auto query(int u)
    {
        node res{LLONG_MIN / 2, 0};
        for (int v = u, w = 0; v; v = fa[w = top[v]])
        {
            res = max(res, tree.query(dfn[top[v]], dfn[v] - 1, 1) + dis[u]);
            if (!w)
                res = max(res, tree.query(dfn[v], dfn[v] + sze[v] - 1, 0) + dis[u] - 2 * dis[v]);
            else
                res = max(res, max(tree.query(dfn[v], dfn[w] - 1, 0), tree.query(dfn[w] + sze[w], dfn[v] + sze[v] - 1, 0)) + dis[u] - 2 * dis[v]);
        }
        return res;
    }
    Main()
    {
        cin >> n >> m;
        G.resize(n + 5), a.resize(n + 5);
        for (int i = 1; i <= n; ++i)
            cin >> a[i];
        for (int i = 2; i <= n; ++i)
        {
            int p, w;
            cin >> p >> w;
            G[p].emplace_back(i, w);
        }
        fa.resize(n + 5), dep.resize(n + 5);
        sze.resize(n + 5), son.resize(n + 5);
        dis.resize(n + 5);
        dfn.resize(n + 5), rk.resize(n + 5);
        top.resize(n + 5), btm.resize(n + 5);
        dfs1(1, 0);
        dfs2(1, 1);
        tree = SegmentTree(n);
        dp.resize(n + 5);
        dfs3(1, 0);
        for (int i = 0; i < m; ++i)
        {
            int x, y, w;
            cin >> x >> y >> w;
            update(y, -w);
            auto ans = query(x);
            cout << ans.id << ' ' << ans.dis << '\n';
        }
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
