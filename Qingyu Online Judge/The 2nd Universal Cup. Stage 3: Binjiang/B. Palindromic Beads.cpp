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
    static constexpr int K = 20;
    int n;
    int dfstime = 0;
    vector<int> dfn, low;
    vector<int> dep, fa;
    vector<array<int, K>> up;
    vector<vector<int>> G;
    auto dfs(int u, int _fa) -> void
    {
        dep[u] = dep[fa[u] = _fa] + 1;
        up[u][0] = _fa;
        for (int i = 1; i < K; ++i)
            up[u][i] = up[up[u][i - 1]][i - 1];
        dfn[u] = ++dfstime;
        for (auto v : G[u])
        {
            if (v == _fa)
                continue;
            dfs(v, u);
        }
        low[u] = dfstime;
    }
    auto lca(int x, int y)
    {
        if (dep[x] < dep[y])
            swap(x, y);
        for (int i = K - 1; i >= 0; --i)
            if (dep[up[x][i]] >= dep[y])
                x = up[x][i];
        if (x == y)
            return x;
        for (int i = K - 1; i >= 0; --i)
            if (up[x][i] != up[y][i])
                x = up[x][i], y = up[y][i];
        return fa[x];
    }
    auto jump(int x, int d)
    {
        for (int i = 0; i < K; ++i)
            if (d >> i & 1)
                x = up[x][i];
        return x;
    }
    auto sub(int x, int y)
    {
        return dfn[x] <= dfn[y] && dfn[y] <= low[x];
    }
    vector<vector<int>> a;
    struct path
    {
        int x, y, len;
    };
    vector<path> p;
    vector<int> root;
    struct node
    {
        int lc, rc;
        int max;
    };
    vector<node> tree;
#define lc(rt) (tree[rt].lc)
#define rc(rt) (tree[rt].rc)
    auto newnode()
    {
        tree.emplace_back();
        return (int)tree.size() - 1;
    }
    auto update(int rt, int l, int r, int x, int v)
    {
        if (!rt)
            rt = newnode();
        tree[rt].max = max(tree[rt].max, v);
        if (l == r)
            return rt;
        int mid = (l + r) >> 1;
        if (x <= mid)
            lc(rt) = update(lc(rt), l, mid, x, v);
        else
            rc(rt) = update(rc(rt), mid + 1, r, x, v);
        return rt;
    }
    auto update(int rt, int l, int r, int x, int y, int v)
    {
        root[rt] = update(root[rt], 1, n, y, v);
        if (l == r)
            return;
        int mid = (l + r) >> 1;
        if (x <= mid)
            update(rt << 1, l, mid, x, y, v);
        else
            update(rt << 1 | 1, mid + 1, r, x, y, v);
    }
    auto query(int rt, int l, int r, int x, int y)
    {
        if (!rt || r < x || l > y)
            return 0;
        if (x <= l && r <= y)
            return tree[rt].max;
        int mid = (l + r) >> 1;
        return max(query(lc(rt), l, mid, x, y), query(rc(rt), mid + 1, r, x, y));
    }
    auto query(int rt, int l, int r, int xl, int xr, int yl, int yr)
    {
        if (r < xl || l > xr)
            return 0;
        if (xl <= l && r <= xr)
            return query(root[rt], 1, n, yl, yr);
        int mid = (l + r) >> 1;
        return max(query(rt << 1, l, mid, xl, xr, yl, yr),
                   query(rt << 1 | 1, mid + 1, r, xl, xr, yl, yr));
    }
    Main() : tree(1)
    {
        cin >> n;
        G.resize(n + 5);
        a.resize(n + 5);
        for (int i = 1; i <= n; ++i)
        {
            int x;
            cin >> x;
            a[x].emplace_back(i);
        }
        for (int i = 1; i < n; ++i)
        {
            int u, v;
            cin >> u >> v;
            G[u].emplace_back(v);
            G[v].emplace_back(u);
        }
        dfn.resize(n + 5), low.resize(n + 5);
        dep.resize(n + 5), fa.resize(n + 5);
        up.resize(n + 5);
        dfs(1, 0);
        for (int i = 1; i <= n; ++i)
        {
            if (a[i].size() <= 1)
                continue;
            int x = a[i][0], y = a[i][1];
            if (dfn[x] > dfn[y])
                swap(x, y);
            p.push_back({x, y, dep[x] + dep[y] - 2 * dep[lca(x, y)]});
        }
        ranges::sort(p, greater{}, &path::len);
        root.resize(4 * n);
        vector<int> dp(p.size());
        int ans = 1;
        for (int i = 0; i < (int)p.size(); ++i)
        {
            auto [x, y, len] = p[i];
            if (sub(x, y))
            {
                int z = jump(y, dep[y] - dep[x] - 1);
                dp[i] = max(query(1, 1, n, 1, dfn[z] - 1, dfn[y], low[y]),
                            query(1, 1, n, dfn[y], low[y], low[z] + 1, n));
            }
            else
                dp[i] = query(1, 1, n, dfn[x], low[x], dfn[y], low[y]);
            dp[i] += 2;
            ans = max(ans, dp[i]);
            if (len > 1)
                ans = max(ans, dp[i] + 1);
            update(1, 1, n, dfn[x], dfn[y], dp[i]);
        }
        cout << ans << '\n';
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