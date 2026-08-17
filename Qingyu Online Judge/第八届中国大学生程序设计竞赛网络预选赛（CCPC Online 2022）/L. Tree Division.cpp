#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
constexpr int N = 4e5 + 5;
constexpr int mod = 998244353;
auto _main()
{
    int n;
    cin >> n;
    vector<vector<int>> g(n + 5);
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<int> sze(n + 5), son(n + 5);
    function<void(int, int)> dfs1 = [&](int u, int _fa)
    {
        sze[u] = 1;
        for (int v : g[u])
        {
            if (v == _fa)
                continue;
            dfs1(v, u);
            if (sze[v] > sze[son[u]])
                son[u] = v;
            sze[u] += sze[v];
        }
    };
    struct node
    {
        int tag, max;
        auto update(int _tag)
        {
            tag += _tag;
            max += _tag;
        }
    };
    vector<node> tree(n * 4);
#define lc (rt << 1)
#define rc (rt << 1 | 1)
    auto pushup = [&](int rt)
    {
        tree[rt].max = max(tree[lc].max, tree[rc].max);
    };
    auto pushdown = [&](int rt)
    {
        if (tree[rt].tag)
        {
            tree[lc].update(tree[rt].tag);
            tree[rc].update(tree[rt].tag);
            tree[rt].tag = 0;
        }
    };
    function<void(int, int, int)> build = [&](int rt, int l, int r)
    {
        if (l == r)
        {
            tree[rt].max = -l;
            return;
        }
        int mid = (l + r) >> 1;
        build(lc, l, mid);
        build(rc, mid + 1, r);
        pushup(rt);
    };
    function<void(int, int, int, int, int, int)> cover = [&](int rt, int l, int r, int x, int y, int z)
    {
        if (r < x || l > y)
            return;
        if (x <= l && r <= y)
            return tree[rt].update(z);
        int mid = (l + r) >> 1;
        pushdown(rt);
        cover(lc, l, mid, x, y, z);
        cover(rc, mid + 1, r, x, y, z);
        pushup(rt);
    };
    function<void(int, int, int, int, const vector<int> &)> add = [&](int rt, int l, int r, int pos, const vector<int> &a)
    {
        if (l == r)
        {
            tree[rt].max += a[l];
            return;
        }
        int mid = (l + r) >> 1;
        pushdown(rt);
        add(lc, l, mid, pos, a);
        if (mid < pos)
            add(rc, mid + 1, r, pos, a);
        pushup(rt);
    };
    function<void(int, int, int, int, vector<int> &)> query = [&](int rt, int l, int r, int pos, vector<int> &a)
    {
        if (l == r)
        {
            a[l] += tree[rt].max + l;
            tree[rt].max = -l;
            return;
        }
        int mid = (l + r) >> 1;
        pushdown(rt);
        query(lc, l, mid, pos, a);
        if (mid < pos)
            query(rc, mid + 1, r, pos, a);
        pushup(rt);
    };
    vector<int> answer(n + 5);
    function<void(int, int, int)> solve = [&](int rt, int l, int r)
    {
        if (tree[rt].max < 0)
            return;
        if (l == r)
        {
            ++answer[l];
            tree[rt].max = -l;
            return;
        }
        int mid = (l + r) >> 1;
        pushdown(rt);
        solve(lc, l, mid);
        solve(rc, mid + 1, r);
        pushup(rt);
    };
    function<void(int, int)> dfs2 = [&](int u, int _fa)
    {
        vector<int> tmp;
        for (int v : g[u])
        {
            if (v == _fa || v == son[u])
                continue;
            dfs2(v, u);
            if ((int)tmp.size() <= sze[v])
                tmp.resize(sze[v]);
            query(1, 1, n, sze[v], tmp);
        }
        if (son[u])
            dfs2(son[u], u);
        if (!tmp.empty())
            add(1, 1, n, (int)tmp.size() - 1, tmp);
        cover(1, 1, n, 1, sze[u], 1);
        for (int v : g[u])
        {
            if (v == _fa)
                continue;
            cover(1, 1, n, sze[v] + 1, sze[u], sze[v]);
        }
        solve(1, 1, n);
    };
    dfs1(1, 0);
    build(1, 1, n);
    dfs2(1, 0);
    vector<int> pre(n + 5);
    for (int i = 1; i <= n; ++i)
        pre[answer[i]] = max(pre[answer[i]], i);
    for (int i = n; i >= 2; --i)
        pre[i - 1] = max(pre[i - 1], pre[i]);
    for (int i = 1; i <= n; ++i)
        cout << pre[i] << '\n';
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
