#pragma once
#include <algorithm>
#include <chrono>
#include <random>
#include <vector>

#define lc(x) tree[x].l
#define rc(x) tree[x].r

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

    vector<Node> tree;
    vector<int> root;
    mt19937 rnd;

    persistImplicitTreap() : tree(1), root(1), rnd((unsigned)chrono::steady_clock::now().time_since_epoch().count()) {}
    persistImplicitTreap(const vector<T> &a)
        : tree(1), root(1), rnd((unsigned)chrono::steady_clock::now().time_since_epoch().count())
    {
        int rt = 0;
        for (int i = 1; i < (int)a.size(); ++i)
            rt = merge(rt, newnode(a[i]));
        root.push_back(rt);
    }

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
        tree[rt].size = tree[lc(rt)].size + tree[rc(rt)].size + 1;
        tree[rt].sum = tree[lc(rt)].sum + tree[rc(rt)].sum + tree[rt].val;
    }

    auto pushdown(int rt)
    {
        if (!rt || !tree[rt].rev)
            return;
        if (lc(rt))
            lc(rt) = clone(lc(rt));
        if (rc(rt))
            rc(rt) = clone(rc(rt));
        swap(lc(rt), rc(rt));
        if (lc(rt))
            tree[lc(rt)].rev ^= 1;
        if (rc(rt))
            tree[rc(rt)].rev ^= 1;
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
        if (tree[lc(rt)].size < size)
        {
            x = rt;
            int right = 0;
            split(rc(x), size - tree[lc(x)].size - 1, right, y);
            rc(x) = right;
            pushup(x);
        }
        else
        {
            y = rt;
            int left = 0;
            split(lc(y), size, x, left);
            lc(y) = left;
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
            rc(rt) = merge(rc(rt), y);
            pushup(rt);
            return rt;
        }
        int rt = clone(y);
        pushdown(rt);
        lc(rt) = merge(x, lc(rt));
        pushup(rt);
        return rt;
    }

    auto build(const vector<T> &a)
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
        int left = nowRev ? rc(rt) : lc(rt);
        int right = nowRev ? lc(rt) : rc(rt);
        int mid = l + tree[left].size;
        return query(left, l, mid - 1, x, y, nowRev) +
               (x <= mid && mid <= y ? tree[rt].val : 0) +
               query(right, mid + 1, r, x, y, nowRev);
    }

    auto query(int ver, int l, int r) const
    {
        return query(root[ver], 1, tree[root[ver]].size, l, r);
    }

    auto dfs(int rt, vector<T> &res, bool rev = false) const -> void
    {
        if (!rt)
            return;
        bool nowRev = rev ^ tree[rt].rev;
        int left = nowRev ? rc(rt) : lc(rt);
        int right = nowRev ? lc(rt) : rc(rt);
        dfs(left, res, nowRev);
        res.push_back(tree[rt].val);
        dfs(right, res, nowRev);
    }

    auto dump(int ver) const
    {
        vector<T> res;
        dfs(root[ver], res);
        return res;
    }

    auto copyVersion(int ver)
    {
        root.push_back(root[ver]);
        return (int)root.size() - 1;
    }
};

#undef lc
#undef rc
