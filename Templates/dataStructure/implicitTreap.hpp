#pragma once
#include <algorithm>
#include <chrono>
#include <random>
#include <vector>

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
    std::vector<Node> tree;
    std::mt19937 rnd;

    implicitTreap() : tree(1), rnd((unsigned)std::chrono::steady_clock::now().time_since_epoch().count()) {}
    implicitTreap(const std::vector<T> &a) : implicitTreap() { build(a); }

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
        tree[rt].size = tree[tree[rt].l].size + tree[tree[rt].r].size + 1;
        tree[rt].sum = tree[tree[rt].l].sum + tree[tree[rt].r].sum + tree[rt].val;
    }

    auto pushdown(int rt)
    {
        if (!rt || !tree[rt].rev)
            return;
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
        pushdown(rt);
        if (tree[tree[rt].l].size < size)
        {
            x = rt;
            split(tree[rt].r, size - tree[tree[rt].l].size - 1, tree[rt].r, y);
        }
        else
        {
            y = rt;
            split(tree[rt].l, size, x, tree[rt].l);
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
            tree[x].r = merge(tree[x].r, y);
            pushup(x);
            return x;
        }
        pushdown(y);
        tree[y].l = merge(x, tree[y].l);
        pushup(y);
        return y;
    }

    auto build(const std::vector<T> &a)
    {
        root = 0;
        tree.assign(1, Node());
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
            if (pos <= tree[tree[rt].l].size)
                rt = tree[rt].l;
            else if (pos > tree[tree[rt].l].size + 1)
            {
                pos -= tree[tree[rt].l].size + 1;
                rt = tree[rt].r;
            }
            else
                return tree[rt].val;
        }
        return T();
    }

    auto dfs(int rt, std::vector<T> &res)
    {
        if (!rt)
            return;
        pushdown(rt);
        dfs(tree[rt].l, res);
        res.push_back(tree[rt].val);
        dfs(tree[rt].r, res);
    }

    auto dump()
    {
        std::vector<T> res;
        dfs(root, res);
        return res;
    }
};
