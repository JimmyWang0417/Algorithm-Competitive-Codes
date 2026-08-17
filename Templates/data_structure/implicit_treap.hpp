#pragma once
#include <algorithm>
#include <chrono>
#include <random>
#include <vector>

#define lc(x) tree[x].l
#define rc(x) tree[x].r

template <typename T = long long>
struct implicitTreap
{
    struct Node
    {
        int l = 0, r = 0, size = 0;
        unsigned key = 0;
        T val = 0, sum = 0;
        bool rev = false;
    };

    int root = 0;
    vector<Node> tree;
    mt19937 rnd;

    implicitTreap() : tree(1), rnd((unsigned)chrono::steady_clock::now().time_since_epoch().count()) {}
    implicitTreap(const vector<T> &a)
        : tree(1), rnd((unsigned)chrono::steady_clock::now().time_since_epoch().count())
    {
        for (int i = 1; i < (int)a.size(); ++i)
            root = merge(root, newnode(a[i]));
    }

    auto newnode(T val)
    {
        tree.push_back(Node());
        int rt = (int)tree.size() - 1;
        tree[rt].val = tree[rt].sum = val;
        tree[rt].key = rnd();
        tree[rt].size = 1;
        return rt;
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
        pushdown(rt);
        if (tree[lc(rt)].size < size)
        {
            x = rt;
            split(rc(rt), size - tree[lc(rt)].size - 1, rc(rt), y);
        }
        else
        {
            y = rt;
            split(lc(rt), size, x, lc(rt));
        }
        pushup(rt);
    }

    auto merge(int x, int y) -> int
    {
        if (!x || !y)
            return x | y;
        if (tree[x].key > tree[y].key)
        {
            pushdown(x);
            rc(x) = merge(rc(x), y);
            pushup(x);
            return x;
        }
        pushdown(y);
        lc(y) = merge(x, lc(y));
        pushup(y);
        return y;
    }

    auto build(const vector<T> &a)
    {
        root = 0;
        tree.resize(1);
        tree[0] = Node();
        for (int i = 1; i < (int)a.size(); ++i)
            root = merge(root, newnode(a[i]));
    }

    auto insert(int pos, T val)
    {
        int x, y;
        split(root, pos, x, y);
        root = merge(merge(x, newnode(val)), y);
    }

    auto erase(int pos)
    {
        int x, y, z;
        split(root, pos - 1, x, y);
        split(y, 1, y, z);
        root = merge(x, z);
    }

    auto reverse(int l, int r)
    {
        int x, y, z;
        split(root, l - 1, x, y);
        split(y, r - l + 1, y, z);
        if (y)
            tree[y].rev ^= 1;
        root = merge(x, merge(y, z));
    }

    auto query(int l, int r)
    {
        int x, y, z;
        split(root, l - 1, x, y);
        split(y, r - l + 1, y, z);
        T res = tree[y].sum;
        root = merge(x, merge(y, z));
        return res;
    }

    auto kth(int pos)
    {
        int rt = root;
        while (rt)
        {
            pushdown(rt);
            if (pos <= tree[lc(rt)].size)
                rt = lc(rt);
            else if (pos > tree[lc(rt)].size + 1)
            {
                pos -= tree[lc(rt)].size + 1;
                rt = rc(rt);
            }
            else
                return tree[rt].val;
        }
        return T();
    }

    auto dfs(int rt, vector<T> &res)
    {
        if (!rt)
            return;
        pushdown(rt);
        dfs(lc(rt), res);
        res.push_back(tree[rt].val);
        dfs(rc(rt), res);
    }

    auto dump()
    {
        vector<T> res;
        dfs(root, res);
        return res;
    }
};

#undef lc
#undef rc
