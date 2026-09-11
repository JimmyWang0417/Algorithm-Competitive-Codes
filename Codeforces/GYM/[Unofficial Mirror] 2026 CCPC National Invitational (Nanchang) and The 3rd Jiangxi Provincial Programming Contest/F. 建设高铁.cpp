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
    int n, m, q;
    int dfstime = 0;
    int root;
    vector<int> dep, dfn;
    vector<vector<int>> G;
    vector<array<int, 21>> fa;
    auto dfs(int u, int _fa) -> void
    {
        dfn[u] = ++dfstime;
        dep[u] = dep[fa[u][0] = _fa] + 1;
        for (int i = 0; i < 20; ++i)
            fa[u][i + 1] = fa[fa[u][i]][i];
        for (auto v : G[u])
            dfs(v, u);
    }
    auto lca(int u, int v)
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
    struct UnionSet : vector<int>
    {
        using vector<int>::vector;
        UnionSet(size_t n) : vector(n) { iota(begin(), end(), 0); }
        auto find(int x) -> int
        {
            return at(x) == x ? x : at(x) = find(at(x));
        }
    };
    UnionSet us;
    vector<tuple<int, int, int>> e;
    vector<tuple<int, int, int>> queries;
    vector<pair<int, int>> p;
    vector<int> a;
    auto merge(int x, int y)
    {
        if (!x || !y)
            return x | y;
        return lca(x, y);
    }
    struct Tree
    {
        int lca;
        int sze;
    };
    vector<Tree> tree;
#define lc (rt << 1)
#define rc (rt << 1 | 1)
    auto pushup(int rt)
    {
        tree[rt].lca = merge(tree[lc].lca, tree[rc].lca);
        tree[rt].sze = tree[lc].sze + tree[rc].sze;
    }
    auto add(int rt, int l, int r, int pos, int val)
    {
        if (l == r)
        {
            tree[rt].lca = val;
            tree[rt].sze = 1;
            return;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid)
            add(lc, l, mid, pos, val);
        else
            add(rc, mid + 1, r, pos, val);
        pushup(rt);
    }
    auto del(int rt, int l, int r, int pos)
    {
        if (l == r)
        {
            tree[rt].lca = 0;
            tree[rt].sze = 0;
            return;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid)
            del(lc, l, mid, pos);
        else
            del(rc, mid + 1, r, pos);
        pushup(rt);
    }
    auto query(int rt, int l, int r, int kth)
    {
        if (l == r)
            return tree[rt].lca;
        int mid = (l + r) >> 1;
        if (kth <= tree[lc].sze)
            return query(lc, l, mid, kth);
        else
            return merge(tree[lc].lca, query(rc, mid + 1, r, kth - tree[lc].sze));
    }
    Main()
    {
        cin >> n >> m >> q;
        a.resize(n + 5);
        for (int i = 1; i <= n; ++i)
        {
            cin >> a[i];
            p.emplace_back(-a[i], i);
        }
        e.resize(m);
        for (auto &[x, y, z] : e)
            cin >> x >> y >> z;
        dep.resize(n + m + 5), dfn.resize(n + m + 5);
        G.resize(n + m + 5), fa.resize(n + m + 5);
        us = UnionSet(n + m + 1);
        ranges::sort(e, {}, [](auto x)
                     { return get<2>(x); });
        for (int i = 0; i < m; ++i)
        {
            auto [x, y, z] = e[i];
            x = us.find(x), y = us.find(y);
            if (x == y) continue;
            us[x] = us[y] = i + n + 1;
            G[i + n + 1].emplace_back(x);
            G[i + n + 1].emplace_back(y);
        }
        root = us.find(1);
        dfs(root, 0);
        queries.resize(q);
        for (auto &[o, c, t] : queries)
        {
            cin >> o >> c;
            if (o == 1)
            {
                cin >> t;
                p.emplace_back(-t, c);
            }
        }
        ranges::sort(p);
        p.erase(unique(p.begin(), p.end()), p.end());
        auto posi = [&](int x)
        {
            return (int)(ranges::lower_bound(p, make_pair(-a[x], x)) - p.begin() + 1);
        };
        tree.resize(p.size() * 4);
        for (int i = 1; i <= n; ++i)
            add(1, 1, (int)p.size(), posi(i), i);
        for (auto [o, c, t] : queries)
        {
            if (o == 1)
            {
                del(1, 1, (int)p.size(), posi(c));
                a[c] = t;
                add(1, 1, (int)p.size(), posi(c), c);
            }
            else
            {
                int x = query(1, 1, (int)p.size(), c);
                cout << (x <= n ? 0 : get<2>(e[x - n - 1])) << '\n';
            }
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