#pragma once
#include <algorithm>
#include <limits>
#include <vector>

#define lc(x) tree[x].l
#define rc(x) tree[x].r

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
    vector<Node> tree;
    vector<int> sta;

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
        return max(tree[lc(rt)].size, tree[rc(rt)].size) > tree[rt].size * alpha ||
               tree[rt].size - tree[rt].fact > tree[rt].size * 0.3;
    }

    auto ldr(int rt) -> void
    {
        if (!rt)
            return;
        ldr(lc(rt));
        if (tree[rt].exist)
            sta.push_back(rt);
        ldr(rc(rt));
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
        lift(l, mid - 1, lc(rt));
        lift(mid + 1, r, rc(rt));
        tree[rt].size = tree[lc(rt)].size + tree[rc(rt)].size + 1;
        tree[rt].fact = tree[lc(rt)].fact + tree[rc(rt)].fact + 1;
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
            int child = lc(rt);
            insert(child, val);
            lc(rt) = child;
        }
        else
        {
            int child = rc(rt);
            insert(child, val);
            rc(rt) = child;
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
            ok = erase(lc(rt), val);
        else
            ok = erase(rc(rt), val);
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
                rt = lc(rt);
            else
            {
                res += tree[lc(rt)].fact + tree[rt].exist;
                rt = rc(rt);
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
                rt = lc(rt);
            else
            {
                res += tree[lc(rt)].fact + tree[rt].exist;
                rt = rc(rt);
            }
        }
        return res;
    }

    auto kth(int k) const
    {
        int rt = root;
        while (rt)
        {
            if (k <= tree[lc(rt)].fact)
                rt = lc(rt);
            else if (k > tree[lc(rt)].fact + tree[rt].exist)
            {
                k -= tree[lc(rt)].fact + tree[rt].exist;
                rt = rc(rt);
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

#undef lc
#undef rc
