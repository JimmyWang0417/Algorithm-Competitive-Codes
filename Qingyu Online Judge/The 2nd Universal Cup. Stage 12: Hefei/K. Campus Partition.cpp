#include <bits/stdc++.h>
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
struct segment
{
    struct node
    {
        int lc, rc;
        i64 X, Y;
        i64 tag;
        auto update(i64 v)
        {
            X += v, Y += v;
            tag += v;
        }
    };
    vector<node> tree;
#define lc(rt) tree[rt].lc
#define rc(rt) tree[rt].rc
    auto newnode()
    {
        tree.emplace_back();
        return (int)tree.size() - 1;
    }
    auto pushup(int rt)
    {
        tree[rt].X = max(tree[lc(rt)].X, tree[rc(rt)].X);
        tree[rt].Y = max(tree[lc(rt)].Y, tree[rc(rt)].Y);
    }
    auto pushdown(int rt)
    {
        if (tree[rt].tag)
        {
            if (lc(rt))
                tree[lc(rt)].update(tree[rt].tag);
            if (rc(rt))
                tree[rc(rt)].update(tree[rt].tag);
            tree[rt].tag = 0;
        }
    }
    auto update(int rt, int l, int r, int pos, int val)
    {
        if (!rt)
            rt = newnode();
        if (l == r)
        {
            tree[rt].X = val + pos;
            tree[rt].Y = val;
            return rt;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid)
            lc(rt) = update(lc(rt), l, mid, pos, val);
        else
            rc(rt) = update(rc(rt), mid + 1, r, pos, val);
        pushup(rt);
        return rt;
    }
    auto update(int rt, int l, int r, int x, int y, i64 v)
    {
        if (!rt || r < x || l > y)
            return;
        if (x <= l && r <= y)
            return tree[rt].update(v);
        int mid = (l + r) >> 1;
        pushdown(rt);
        update(lc(rt), l, mid, x, y, v);
        update(rc(rt), mid + 1, r, x, y, v);
        pushup(rt);
    }
    auto merge(int x, int y, int l, int r)
    {
        if (!x || !y)
            return x | y;
        if (l == r)
        {
            tree[x].X = max(tree[x].X, tree[y].X);
            tree[x].Y = max(tree[x].Y, tree[y].Y);
            return x;
        }
        int mid = (l + r) >> 1;
        pushdown(x), pushdown(y);
        lc(x) = merge(lc(x), lc(y), l, mid);
        rc(x) = merge(rc(x), rc(y), mid + 1, r);
        pushup(x);
        return x;
    }
    auto query(int x, int y, int l, int r) -> i64
    {
        if (!x || !y)
            return LLONG_MIN / 2;
        if (l == r)
            return max({tree[x].X + tree[y].Y, tree[y].X + tree[x].Y});
        int mid = (l + r) >> 1;
        pushdown(x), pushdown(y);
        return max({tree[lc(x)].X + tree[rc(y)].Y, tree[lc(y)].X + tree[rc(x)].Y,
                    query(lc(x), lc(y), l, mid), query(rc(x), rc(y), mid + 1, r)});
    }
    segment() : tree(1, {0, 0, LLONG_MIN / 2, LLONG_MIN / 2, 0}) {}
};
struct Main
{
    int n;
    vector<int> a;
    vector<int> root;
    vector<i64> dp;
    vector<vector<int>> G;
    segment t;
    auto dfs(int u, int _fa) -> void
    {
        root[u] = t.update(root[u], 1, 1e9, a[u], 0);
        i64 sum = 0;
        for (auto v : G[u])
        {
            if (v == _fa)
                continue;
            dfs(v, u);
            dp[u] = max(dp[u] + dp[v], t.query(root[u], root[v], 1, 1e9));
            t.update(root[v], 1, 1e9, 1, 1e9, sum);
            t.update(root[u], 1, 1e9, 1, 1e9, dp[v]);
            root[u] = t.merge(root[u], root[v], 1, 1e9);
            sum += dp[v];
        }
    }
    Main()
    {
        cin >> n;
        a.resize(n + 5);
        for (int i = 1; i <= n; ++i)
            cin >> a[i];
        G.resize(n + 5);
        for (int i = 1; i < n; ++i)
        {
            int u, v;
            cin >> u >> v;
            G[u].emplace_back(v);
            G[v].emplace_back(u);
        }
        root.resize(n + 5), dp.resize(n + 5);
        dfs(1, 0);
        cout << dp[1] << '\n';
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
