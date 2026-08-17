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
struct SegmentTree
{
    struct node
    {
        int max;
        int tag;
        auto update(int v)
        {
            max += v;
            tag += v;
        }
    };
    int n;
    vector<node> tree;
    SegmentTree() = default;
    SegmentTree(int _n) : n(_n), tree(_n * 4 + 5) {}
    auto clear() { ranges::fill(tree, node()); }
#define lc (rt << 1)
#define rc (rt << 1 | 1)
    auto pushup(int rt)
    {
        tree[rt].max = max(tree[lc].max, tree[rc].max) + tree[rt].tag;
    }
    auto update(int rt, int l, int r, int x, int y, int v) -> void
    {
        if (r < x || l > y)
            return;
        if (x <= l && r <= y)
            return tree[rt].update(v);
        int mid = (l + r) >> 1;
        update(lc, l, mid, x, y, v);
        update(rc, mid + 1, r, x, y, v);
        pushup(rt);
    }
    auto update(int x, int y, int v) { return update(1, 1, n, x, y, v); }
    auto all() { return tree[1].max; }
};
struct Main
{
    int n;
    vector<vector<pair<int, int>>> G;
    vector<int> dfn, low, pa;
    vector<vector<int>> col, son, rt;
    int dfstime = 0;
    auto init(int u, int _fa) -> void
    {
        dfn[u] = ++dfstime;
        for (auto [v, a] : G[u])
        {
            if (v == _fa)
                continue;
            col[a].push_back(v);
            init(v, u);
        }
        low[u] = dfstime;
    }
    SegmentTree tree;
    auto modify(int a, int u, int v)
    {
        if (u)
        {
            tree.update(dfn[u], low[u], v);
            for (int w : son[u])
                tree.update(dfn[w], low[w], -v);
        }
        else
        {
            tree.update(1, n, v);
            for (int w : rt[a])
                tree.update(dfn[w], low[w], -v);
        }
    }
    auto dfs(int u, int _fa, int lim) -> bool
    {
        if (tree.all() == lim)
            return true;
        for (int i = 0, j = 0; i < (int)G[u].size(); i = j)
        {
            int a = G[u][i].second, p = -1;
            while (j < (int)G[u].size() && G[u][j].second == a)
                ++j;
            if (a < lim)
            {
                for (int k = i; k < j; ++k)
                    if (G[u][k].first != _fa)
                        p = pa[G[u][k].first];
                if (p >= 0)
                    modify(a, p, 1);
            }
            for (int k = i; k < j; ++k)
            {
                int v = G[u][k].first;
                if (v == _fa)
                    continue;
                if (a < lim)
                    modify(a, v, -1);
                if (dfs(v, u, lim))
                    return true;
                if (a < lim)
                    modify(a, v, 1);
            }
            if (a < lim && p >= 0)
                modify(a, p, -1);
        }
        return false;
    }
    auto check(int mid) -> bool
    {
        tree.clear();
        for (int i = 0; i < mid; ++i)
            for (int u : rt[i])
                tree.update(dfn[u], low[u], 1);
        return dfs(1, 0, mid);
    }
    Main()
    {
        cin >> n;
        G.resize(n + 5);
        dfn.resize(n + 5);
        low.resize(n + 5);
        pa.resize(n + 5);
        col.resize(n + 5);
        son.resize(n + 5);
        rt.resize(n + 5);
        for (int i = 1; i < n; ++i)
        {
            int u, v, a;
            cin >> u >> v >> a;
            G[u].emplace_back(v, a);
            G[v].emplace_back(u, a);
        }
        for (int i = 1; i <= n; ++i)
            ranges::sort(G[i], {}, &pair<int, int>::second);
        init(1, 0);
        for (int i = 0; i < n; ++i)
            for (int u : col[i])
            {
                for (int v : col[i])
                    if (dfn[v] < dfn[u] && dfn[u] <= low[v] && dfn[v] > dfn[pa[u]])
                        pa[u] = v;
                if (pa[u])
                    son[pa[u]].push_back(u);
                else
                    rt[i].push_back(u);
            }
        tree = SegmentTree(n);
        int l = 1, r = 0, res = 0;
        while (r < n && !col[r].empty())
            ++r;
        while (l <= r)
        {
            int mid = (l + r) >> 1;
            if (check(mid))
                res = mid, l = mid + 1;
            else
                r = mid - 1;
        }
        cout << res << '\n';
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

