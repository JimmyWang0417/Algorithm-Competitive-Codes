#pragma once
#include <algorithm>
#include <limits>
#include <vector>

template <typename T = int>
struct scapegoat
{
    static constexpr double alpha = 0.75;

    struct Node
    {
        int l = 0, r = 0;
        int size = 0, fact = 0;
        T val = 0;
        bool exist = false;
    };

    int root = 0;
    std::vector<Node> tree;
    std::vector<int> sta;

    scapegoat() : tree(1) {}

    auto newnode(int &rt, T val)
    {
        tree.push_back(Node());
        rt = (int)tree.size() - 1;
        tree[rt].val = val;
        tree[rt].size = tree[rt].fact = 1;
        tree[rt].exist = true;
    }

    auto imbalence(int rt)
    {
        return std::max(tree[tree[rt].l].size, tree[tree[rt].r].size) > tree[rt].size * alpha ||
               tree[rt].size - tree[rt].fact > tree[rt].size * 0.3;
    }

    auto ldr(int rt) -> void
    {
        if (!rt)
            return;
        ldr(tree[rt].l);
        if (tree[rt].exist)
            sta.push_back(rt);
        ldr(tree[rt].r);
    }

    auto lift(int l, int r, int &rt) -> void
    {
        if (l > r)
        {
            rt = 0;
            return;
        }
        int mid = (l + r) >> 1;
        while (l < mid && tree[sta[mid]].val == tree[sta[mid - 1]].val)
            --mid;
        rt = sta[mid];
        lift(l, mid - 1, tree[rt].l);
        lift(mid + 1, r, tree[rt].r);
        tree[rt].size = tree[tree[rt].l].size + tree[tree[rt].r].size + 1;
        tree[rt].fact = tree[tree[rt].l].fact + tree[tree[rt].r].fact + 1;
    }

    auto rebuild(int &rt)
    {
        sta.clear();
        ldr(rt);
        lift(0, (int)sta.size() - 1, rt);
    }

    auto insert(int &rt, T val) -> void
    {
        if (!rt)
        {
            newnode(rt, val);
            return;
        }
        ++tree[rt].size;
        ++tree[rt].fact;
        if (val < tree[rt].val)
        {
            int child = tree[rt].l;
            insert(child, val);
            tree[rt].l = child;
        }
        else
        {
            int child = tree[rt].r;
            insert(child, val);
            tree[rt].r = child;
        }
        if (imbalence(rt))
            rebuild(rt);
    }

    auto erase(int &rt, T val) -> bool
    {
        if (!rt)
            return false;
        if (tree[rt].exist && tree[rt].val == val)
        {
            tree[rt].exist = false;
            --tree[rt].fact;
            return true;
        }
        bool ok = false;
        if (val < tree[rt].val)
            ok = erase(tree[rt].l, val);
        else
            ok = erase(tree[rt].r, val);
        if (ok)
        {
            --tree[rt].fact;
            if (imbalence(rt))
                rebuild(rt);
        }
        return ok;
    }

    auto rank(T val) const
    {
        int rt = root, res = 1;
        while (rt)
        {
            if (val <= tree[rt].val)
                rt = tree[rt].l;
            else
            {
                res += tree[tree[rt].l].fact + tree[rt].exist;
                rt = tree[rt].r;
            }
        }
        return res;
    }

    auto upperRank(T val) const
    {
        int rt = root, res = 1;
        while (rt)
        {
            if (val < tree[rt].val)
                rt = tree[rt].l;
            else
            {
                res += tree[tree[rt].l].fact + tree[rt].exist;
                rt = tree[rt].r;
            }
        }
        return res;
    }

    auto kth(int k) const
    {
        int rt = root;
        while (rt)
        {
            if (k <= tree[tree[rt].l].fact)
                rt = tree[rt].l;
            else if (k > tree[tree[rt].l].fact + tree[rt].exist)
            {
                k -= tree[tree[rt].l].fact + tree[rt].exist;
                rt = tree[rt].r;
            }
            else
                return tree[rt].val;
        }
        return T();
    }

    auto insert(T val) { insert(root, val); }
    auto erase(T val)
    {
        erase(root, val);
    }
    auto pre(T val) const { return kth(rank(val) - 1); }
    auto next(T val) const { return kth(upperRank(val)); }
};
