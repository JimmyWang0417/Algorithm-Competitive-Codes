#pragma once
#include <algorithm>
#include <array>
#include <utility>
#include <vector>

struct decompTree
{
    int n = 0, root = 0;
    std::vector<int> a, Log;
    std::array<std::vector<int>, 23> _min, _max;

    std::vector<int> id, dep;
    std::vector<std::vector<int>> G;
    struct node
    {
        int l = 0, r = 0, m = 0;
        bool typ = false;
    };
    std::vector<node> p;
    std::vector<std::array<int, 23>> fa;

    struct Tree
    {
        int min = 0, tag = 0;
        auto update(int v)
        {
            min += v;
            tag += v;
        }
    };
    std::vector<Tree> tree;

    decompTree() = default;

    auto newnode(int l, int r, int m = 0, bool typ = false)
    {
        p.push_back({l, r, m, typ});
        G.emplace_back();
        return (int)p.size() - 1;
    }

    auto pushup(int rt)
    {
        int lc = rt << 1, rc = rt << 1 | 1;
        tree[rt].min = std::min(tree[lc].min, tree[rc].min);
    }

    auto pushdown(int rt)
    {
        if (!tree[rt].tag)
            return;
        int lc = rt << 1, rc = rt << 1 | 1;
        tree[lc].update(tree[rt].tag);
        tree[rc].update(tree[rt].tag);
        tree[rt].tag = 0;
    }

    auto update(int rt, int l, int r, int x, int y, int v) -> void
    {
        if (r < x || l > y)
            return;
        if (x <= l && r <= y)
            return tree[rt].update(v);
        int mid = (l + r) >> 1;
        pushdown(rt);
        update(rt << 1, l, mid, x, y, v);
        update(rt << 1 | 1, mid + 1, r, x, y, v);
        pushup(rt);
    }

    auto query(int rt, int l, int r)
    {
        if (l == r)
            return l;
        int mid = (l + r) >> 1;
        pushdown(rt);
        if (!tree[rt << 1].min)
            return query(rt << 1, l, mid);
        return query(rt << 1 | 1, mid + 1, r);
    }

    auto calcmin(int l, int r)
    {
        int k = Log[r - l + 1];
        return std::min(_min[k][l], _min[k][r - (1 << k) + 1]);
    }

    auto calcmax(int l, int r)
    {
        int k = Log[r - l + 1];
        return std::max(_max[k][l], _max[k][r - (1 << k) + 1]);
    }

    auto check(int l, int r)
    {
        return calcmax(l, r) - calcmin(l, r) == r - l;
    }

    auto dfs(int u, int f) -> void
    {
        dep[u] = dep[fa[u][0] = f] + 1;
        for (int i = 0; i < 20; ++i)
            fa[u][i + 1] = fa[fa[u][i]][i];
        for (int v : G[u])
            dfs(v, u);
    }

    auto lca(int u, int v)
    {
        if (dep[u] < dep[v])
            std::swap(u, v);
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

    decompTree(const std::vector<int> &_a) : G(1), p(1)
    {
        a = _a;
        n = (int)a.size() - 1;
        id.assign(n + 2, 0);
        tree.assign(4 * n + 5, {});
        if (!n)
            return;

        Log.assign(n + 2, 0);
        Log[0] = -1;
        _min.fill(std::vector<int>(n + 2));
        _max.fill(std::vector<int>(n + 2));
        for (int i = 1; i <= n; ++i)
        {
            Log[i] = Log[i >> 1] + 1;
            _min[0][i] = _max[0][i] = a[i];
        }
        for (int j = 0; j < Log[n]; ++j)
            for (int i = 1; i + (2 << j) - 1 <= n; ++i)
            {
                _min[j + 1][i] = std::min(_min[j][i], _min[j][i + (1 << j)]);
                _max[j + 1][i] = std::max(_max[j][i], _max[j][i + (1 << j)]);
            }

        std::vector<int> st1(n + 2), st2(n + 2), st(n + 2);
        int top1 = 0, top2 = 0, top = 0;
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

            int u = id[i] = newnode(i, i);
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
                    int v = newnode(p[st[top]].l, i, p[u].l, true);
                    G[v].emplace_back(st[top--]);
                    G[v].emplace_back(u);
                    u = v;
                }
                else
                {
                    std::vector<int> son;
                    while (top && !check(p[st[top]].l, i))
                        son.emplace_back(st[top--]);
                    int v = newnode(p[st[top]].l, i);
                    G[v].emplace_back(st[top--]);
                    G[v].insert(G[v].end(), son.rbegin(), son.rend());
                    G[v].emplace_back(u);
                    u = v;
                }
            }
            st[++top] = u;
            update(1, 1, n, 1, i, -1);
        }

        root = st[1];
        dep.assign(p.size(), 0);
        fa.resize(p.size());
        dfs(root, 0);
    }

    auto getId(int pos)
    {
        return id[pos];
    }

    auto query(int l, int r)
    {
        if (l > r)
            std::swap(l, r);
        int x = id[l], y = id[r], z = lca(x, y);
        if (p[z].typ)
        {
            int u = jump(x, dep[x] - dep[z] - 1);
            int v = jump(y, dep[y] - dep[z] - 1);
            return std::pair<int, int>{p[u].l, p[v].r};
        }
        return std::pair<int, int>{p[z].l, p[z].r};
    }
};
