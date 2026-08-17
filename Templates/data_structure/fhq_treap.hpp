#pragma once
#include <chrono>
#include <limits>
#include <random>
#include <vector>

#define lc(x) tree[x].l
#define rc(x) tree[x].r

template <typename T = int>
struct fhqTreap
{
    struct Node
    {
        T val = 0;
        unsigned key = 0;
        int size = 0, l = 0, r = 0;
    };

    int root = 0;
    vector<Node> tree;
    mt19937 rnd;

    fhqTreap() : tree(1), rnd((unsigned)chrono::steady_clock::now().time_since_epoch().count()) {}

    auto size(int rt) const { return tree[rt].size; }

    auto newnode(T val)
    {
        tree.push_back({val, (unsigned)rnd(), 1, 0, 0});
        return (int)tree.size() - 1;
    }

    auto pushup(int rt)
    {
        if (rt)
            tree[rt].size = tree[lc(rt)].size + tree[rc(rt)].size + 1;
    }

    auto split(int rt, T val, int &x, int &y) -> void
    {
        if (!rt)
        {
            x = y = 0;
            return;
        }
        if (tree[rt].val <= val)
        {
            x = rt;
            split(rc(rt), val, rc(rt), y);
        }
        else
        {
            y = rt;
            split(lc(rt), val, x, lc(rt));
        }
        pushup(rt);
    }

    auto merge(int x, int y) -> int
    {
        if (!x || !y)
            return x | y;
        if (tree[x].key > tree[y].key)
        {
            rc(x) = merge(rc(x), y);
            pushup(x);
            return x;
        }
        lc(y) = merge(x, lc(y));
        pushup(y);
        return y;
    }

    auto insert(T val)
    {
        int x, y;
        split(root, val, x, y);
        root = merge(merge(x, newnode(val)), y);
    }

    auto erase(T val)
    {
        int x, y, z;
        split(root, val, x, z);
        split(x, val - 1, x, y);
        if (y)
            y = merge(lc(y), rc(y));
        root = merge(merge(x, y), z);
    }

    auto rank(T val)
    {
        int x, y;
        split(root, val - 1, x, y);
        int res = tree[x].size + 1;
        root = merge(x, y);
        return res;
    }

    auto kth(int k) const
    {
        int rt = root;
        while (rt)
        {
            if (k <= tree[lc(rt)].size)
                rt = lc(rt);
            else if (k > tree[lc(rt)].size + 1)
            {
                k -= tree[lc(rt)].size + 1;
                rt = rc(rt);
            }
            else
                return tree[rt].val;
        }
        return T();
    }

    auto pre(T val, T &res)
    {
        int x, y;
        split(root, val - 1, x, y);
        int rt = x;
        if (!rt)
        {
            root = merge(x, y);
            return false;
        }
        while (rc(rt))
            rt = rc(rt);
        res = tree[rt].val;
        root = merge(x, y);
        return true;
    }

    auto next(T val, T &res)
    {
        int x, y;
        split(root, val, x, y);
        int rt = y;
        if (!rt)
        {
            root = merge(x, y);
            return false;
        }
        while (lc(rt))
            rt = lc(rt);
        res = tree[rt].val;
        root = merge(x, y);
        return true;
    }

    auto pre(T val)
    {
        T res = numeric_limits<T>::lowest();
        pre(val, res);
        return res;
    }

    auto next(T val)
    {
        T res = numeric_limits<T>::max();
        next(val, res);
        return res;
    }
};

#undef lc
#undef rc
