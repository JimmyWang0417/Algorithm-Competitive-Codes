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
    int n, m;
    vector<int> a;
    array<vector<int>, 23> _min, _max;
    vector<int> Log;
    struct Tree
    {
        int min, tag;
        auto update(int v)
        {
            min += v;
            tag += v;
        }
    };
    vector<Tree> tree;
#define lc (rt << 1)
#define rc (rt << 1 | 1)
    auto pushup(int rt)
    {
        tree[rt].min = min(tree[lc].min, tree[rc].min);
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
    auto update(int rt, int l, int r, int x, int y, int v)
    {
        if (r < x || l > y)
            return;
        if (x <= l && r <= y)
            return tree[rt].update(v);
        int mid = (l + r) >> 1;
        pushdown(rt);
        update(lc, l, mid, x, y, v);
        update(rc, mid + 1, r, x, y, v);
        pushup(rt);
    }
    auto query(int rt, int l, int r)
    {
        if (l == r)
            return l;
        int mid = (l + r) >> 1;
        pushdown(rt);
        if (!tree[lc].min)
            return query(lc, l, mid);
        else
            return query(rc, mid + 1, r);
    }
    auto calcmin(int l, int r)
    {
        int k = Log[r - l + 1];
        return min(_min[k][l], _min[k][r - (1 << k) + 1]);
    }
    auto calcmax(int l, int r)
    {
        int k = Log[r - l + 1];
        return max(_max[k][l], _max[k][r - (1 << k) + 1]);
    }
    auto check(int l, int r)
    {
        return r - l == calcmax(l, r) - calcmin(l, r);
    }
    vector<int> id;
    vector<vector<int>> G;
    struct node
    {
        int l, r, m;
        bool typ;
    };
    vector<node> p;
    vector<array<int, 23>> fa;
    vector<int> dep;
    auto dfs(int u, int _fa) -> void
    {
        dep[u] = dep[fa[u][0] = _fa] + 1;
        for (int i = 0; i < 20; ++i)
            fa[u][i + 1] = fa[fa[u][i]][i];
        for (int v : G[u])
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
    auto jump(int u, int k)
    {
        for (int i = 20; i >= 0; --i)
            if ((k >> i) & 1)
                u = fa[u][i];
        return u;
    }
    Main() : G(1), p(1)
    {
        cin >> n;
        a.resize(n + 5);
        for (int i = 1; i <= n; ++i)
            cin >> a[i];
        Log.resize(n + 5);
        _min.fill(vector<int>(n + 5));
        _max.fill(vector<int>(n + 5));
        Log[0] = -1;
        for (int i = 1; i <= n; ++i)
        {
            Log[i] = Log[i >> 1] + 1;
            _min[0][i] = _max[0][i] = a[i];
        }
        for (int j = 0; j < Log[n]; ++j)
            for (int i = 1; i + (2 << j) - 1 <= n; ++i)
            {
                _min[j + 1][i] = min(_min[j][i], _min[j][i + (1 << j)]);
                _max[j + 1][i] = max(_max[j][i], _max[j][i + (1 << j)]);
            }
        vector<int> st1(n + 5), st2(n + 5), st(n + 5);
        int top1 = 0, top2 = 0, top = 0;
        id.resize(n + 5);
        tree.resize(4 * n);
        for (int i = 1; i <= n; ++i)
        {
            while (top1 && a[st1[top1]] >= a[i])
            {
                update(1, 1, n, st1[top1 - 1] + 1, st1[top1], a[st1[top1]] - a[i]);
                --top1;
            }
            while (top2 && a[st2[top2]] <= a[i])
            {
                update(1, 1, n, st2[top2 - 1] + 1, st2[top2], a[i] - a[st2[top2]]);
                --top2;
            }
            st1[++top1] = st2[++top2] = i;

            p.emplace_back(i, i);
            G.emplace_back();
            int u = id[i] = (int)p.size() - 1;
            int le = query(1, 1, n);
            while (top && p[st[top]].l >= le)
            {
                if (p[st[top]].typ && check(p[st[top]].m, i))
                {
                    p[st[top]].r = i;
                    p[st[top]].m = p[u].l;
                    G[st[top]].emplace_back(u);
                    u = st[top--];
                }
                else if (check(p[st[top]].l, i))
                {
                    p.emplace_back(p[st[top]].l, i, p[u].l, true);
                    G.emplace_back();
                    int v = (int)p.size() - 1;
                    G[v].emplace_back(st[top--]);
                    G[v].emplace_back(u);
                    u = v;
                }
                else
                {
                    G.emplace_back();
                    int v = (int)G.size() - 1;
                    G[v].emplace_back(u);
                    while (top && !check(p[st[top]].l, i))
                        G[v].emplace_back(st[top--]);
                    p.emplace_back(p[st[top]].l, i);
                    G[v].emplace_back(st[top--]);
                    u = v;
                }
            }
            st[++top] = u;
            update(1, 1, n, 1, i, -1);
        }
        dep.resize(p.size());
        fa.resize(p.size());
        int root = st[1];
        dfs(root, 0);
        cin >> m;
        while (m--)
        {
            int l, r;
            cin >> l >> r;
            int x = id[l], y = id[r], z = lca(x, y);
            if (p[z].typ)
                cout << p[jump(x, dep[x] - dep[z] - 1)].l << ' ' << p[jump(y, dep[y] - dep[z] - 1)].r << '\n';
            else
                cout << p[z].l << ' ' << p[z].r << '\n';
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
