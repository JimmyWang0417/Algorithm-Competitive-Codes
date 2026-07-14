#pragma once
#include <algorithm>
#include <chrono>
#include <random>
#include <vector>

template <typename T = long long>
struct persistImplicitTreap
{
    struct Node
    {
        int l = 0, r = 0, size = 0;
        unsigned key = 0;
        T val = 0, sum = 0;
        bool rev = false;
    };

    std::vector<Node> tree;
    std::vector<int> root;
    std::mt19937 rnd;

    persistImplicitTreap() : tree(1), root(1, 0), rnd((unsigned)std::chrono::steady_clock::now().time_since_epoch().count()) {}
    persistImplicitTreap(const std::vector<T> &a) : persistImplicitTreap() { build(a); }

    auto newnode(T val)
    {
        tree.push_back(Node());
        int rt = (int)tree.size() - 1;
        tree[rt].val = tree[rt].sum = val;
        tree[rt].size = 1;
        tree[rt].key = rnd();
        return rt;
    }

    auto clone(int rt)
    {
        if (!rt)
            return 0;
        tree.push_back(tree[rt]);
        return (int)tree.size() - 1;
    }

    auto pushup(int rt)
    {
        tree[rt].size = tree[tree[rt].l].size + tree[tree[rt].r].size + 1;
        tree[rt].sum = tree[tree[rt].l].sum + tree[tree[rt].r].sum + tree[rt].val;
    }

    auto pushdown(int rt)
    {
        if (!rt || !tree[rt].rev)
            return;
        if (tree[rt].l)
            tree[rt].l = clone(tree[rt].l);
        if (tree[rt].r)
            tree[rt].r = clone(tree[rt].r);
        std::swap(tree[rt].l, tree[rt].r);
        if (tree[rt].l)
            tree[tree[rt].l].rev ^= 1;
        if (tree[rt].r)
            tree[tree[rt].r].rev ^= 1;
        tree[rt].rev = false;
    }

    auto split(int rt, int size, int &x, int &y) -> void
    {
        if (!rt)
        {
            x = y = 0;
            return;
        }
        rt = clone(rt);
        pushdown(rt);
        if (tree[tree[rt].l].size < size)
        {
            x = rt;
            int right = 0;
            split(tree[x].r, size - tree[tree[x].l].size - 1, right, y);
            tree[x].r = right;
            pushup(x);
        }
        else
        {
            y = rt;
            int left = 0;
            split(tree[y].l, size, x, left);
            tree[y].l = left;
            pushup(y);
        }
    }

    auto merge(int x, int y) -> int
    {
        if (!x || !y)
            return x | y;
        if (tree[x].key > tree[y].key)
        {
            int rt = clone(x);
            pushdown(rt);
            tree[rt].r = merge(tree[rt].r, y);
            pushup(rt);
            return rt;
        }
        int rt = clone(y);
        pushdown(rt);
        tree[rt].l = merge(x, tree[rt].l);
        pushup(rt);
        return rt;
    }

    auto build(const std::vector<T> &a)
    {
        int rt = 0;
        for (int i = 1; i < (int)a.size(); ++i)
            rt = merge(rt, newnode(a[i]));
        root.push_back(rt);
        return (int)root.size() - 1;
    }

    auto insert(int ver, int pos, T val)
    {
        int x, y;
        split(root[ver], pos, x, y);
        root.push_back(merge(merge(x, newnode(val)), y));
        return (int)root.size() - 1;
    }

    auto erase(int ver, int pos)
    {
        int x, y, z;
        split(root[ver], pos - 1, x, y);
        split(y, 1, y, z);
        root.push_back(merge(x, z));
        return (int)root.size() - 1;
    }

    auto reverse(int ver, int l, int r)
    {
        int x, y, z;
        split(root[ver], l - 1, x, y);
        split(y, r - l + 1, y, z);
        if (y)
            tree[y].rev ^= 1;
        root.push_back(merge(x, merge(y, z)));
        return (int)root.size() - 1;
    }

    auto query(int rt, int l, int r, int x, int y, bool rev = false) const -> T
    {
        if (!rt || r < x || l > y)
            return 0;
        if (x <= l && r <= y)
            return tree[rt].sum;
        bool nowRev = rev ^ tree[rt].rev;
        int left = nowRev ? tree[rt].r : tree[rt].l;
        int right = nowRev ? tree[rt].l : tree[rt].r;
        int mid = l + tree[left].size;
        return query(left, l, mid - 1, x, y, nowRev) +
               (x <= mid && mid <= y ? tree[rt].val : 0) +
               query(right, mid + 1, r, x, y, nowRev);
    }

    auto query(int ver, int l, int r) const
    {
        return query(root[ver], 1, tree[root[ver]].size, l, r);
    }

    auto dfs(int rt, std::vector<T> &res, bool rev = false) const -> void
    {
        if (!rt)
            return;
        bool nowRev = rev ^ tree[rt].rev;
        int left = nowRev ? tree[rt].r : tree[rt].l;
        int right = nowRev ? tree[rt].l : tree[rt].r;
        dfs(left, res, nowRev);
        res.push_back(tree[rt].val);
        dfs(right, res, nowRev);
    }

    auto dump(int ver) const
    {
        std::vector<T> res;
        dfs(root[ver], res);
        return res;
    }

    auto copyVersion(int ver)
    {
        root.push_back(root[ver]);
        return (int)root.size() - 1;
    }
};
