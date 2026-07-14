#pragma once
#include <chrono>
#include <limits>
#include <random>
#include <vector>

template <typename T = int>
struct persistTreap
{
    struct Node
    {
        int l = 0, r = 0, size = 0;
        unsigned key = 0;
        T val = 0;
    };

    std::vector<Node> tree;
    std::vector<int> root;
    std::mt19937 rnd;

    persistTreap() : tree(1), root(1, 0), rnd((unsigned)std::chrono::steady_clock::now().time_since_epoch().count()) {}

    auto newnode(T val)
    {
        tree.push_back({0, 0, 1, (unsigned)rnd(), val});
        return (int)tree.size() - 1;
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
            x = clone(rt);
            int right = 0;
            split(tree[x].r, val, right, y);
            tree[x].r = right;
            pushup(x);
        }
        else
        {
            y = clone(rt);
            int left = 0;
            split(tree[y].l, val, x, left);
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
            tree[rt].r = merge(tree[rt].r, y);
            pushup(rt);
            return rt;
        }
        int rt = clone(y);
        tree[rt].l = merge(x, tree[rt].l);
        pushup(rt);
        return rt;
    }

    auto insert(int ver, T val)
    {
        int x, y;
        split(root[ver], val, x, y);
        root.push_back(merge(merge(x, newnode(val)), y));
        return (int)root.size() - 1;
    }

    auto erase(int ver, T val)
    {
        int x, y, z;
        split(root[ver], val, x, z);
        split(x, val - 1, x, y);
        if (y)
            y = merge(tree[y].l, tree[y].r);
        root.push_back(merge(merge(x, y), z));
        return (int)root.size() - 1;
    }

    auto rankRoot(int rt, T val) const
    {
        int res = 1;
        while (rt)
        {
            if (val <= tree[rt].val)
                rt = tree[rt].l;
            else
            {
                res += tree[tree[rt].l].size + 1;
                rt = tree[rt].r;
            }
        }
        return res;
    }

    auto kthRoot(int rt, int k) const
    {
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

    auto rank(int ver, T val) const { return rankRoot(root[ver], val); }
    auto kth(int ver, int k) const { return kthRoot(root[ver], k); }

    auto pre(int ver, T val) const
    {
        int rt = root[ver];
        T res = std::numeric_limits<T>::lowest();
        while (rt)
        {
            if (tree[rt].val < val)
                res = tree[rt].val, rt = tree[rt].r;
            else
                rt = tree[rt].l;
        }
        return res;
    }

    auto next(int ver, T val) const
    {
        int rt = root[ver];
        T res = std::numeric_limits<T>::max();
        while (rt)
        {
            if (tree[rt].val > val)
                res = tree[rt].val, rt = tree[rt].l;
            else
                rt = tree[rt].r;
        }
        return res;
    }

    auto copyVersion(int ver)
    {
        root.push_back(root[ver]);
        return (int)root.size() - 1;
    }
};
