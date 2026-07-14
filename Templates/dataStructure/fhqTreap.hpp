#pragma once
#include <chrono>
#include <limits>
#include <random>
#include <vector>

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
    std::vector<Node> tree;
    std::mt19937 rnd;

    fhqTreap() : tree(1), rnd((unsigned)std::chrono::steady_clock::now().time_since_epoch().count()) {}

    auto size(int rt) const { return tree[rt].size; }

    auto newnode(T val)
    {
        tree.push_back({val, (unsigned)rnd(), 1, 0, 0});
        return (int)tree.size() - 1;
    }

    auto pushup(int rt)
    {
        if (rt)
            tree[rt].size = tree[tree[rt].l].size + tree[tree[rt].r].size + 1;
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
            split(tree[rt].r, val, tree[rt].r, y);
        }
        else
        {
            y = rt;
            split(tree[rt].l, val, x, tree[rt].l);
        }
        pushup(rt);
    }

    auto merge(int x, int y) -> int
    {
        if (!x || !y)
            return x | y;
        if (tree[x].key > tree[y].key)
        {
            tree[x].r = merge(tree[x].r, y);
            pushup(x);
            return x;
        }
        tree[y].l = merge(x, tree[y].l);
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
            y = merge(tree[y].l, tree[y].r);
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
            if (k <= tree[tree[rt].l].size)
                rt = tree[rt].l;
            else if (k > tree[tree[rt].l].size + 1)
            {
                k -= tree[tree[rt].l].size + 1;
                rt = tree[rt].r;
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
        while (tree[rt].r)
            rt = tree[rt].r;
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
        while (tree[rt].l)
            rt = tree[rt].l;
        res = tree[rt].val;
        root = merge(x, y);
        return true;
    }

    auto pre(T val)
    {
        T res = std::numeric_limits<T>::lowest();
        pre(val, res);
        return res;
    }

    auto next(T val)
    {
        T res = std::numeric_limits<T>::max();
        next(val, res);
        return res;
    }
};
