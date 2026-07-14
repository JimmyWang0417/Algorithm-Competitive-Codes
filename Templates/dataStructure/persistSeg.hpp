#pragma once
#include <vector>

template <typename T = int>
struct persistSeg
{
    struct Node
    {
        int l = 0, r = 0;
        T sum = 0;
    };

    int n = 0;
    std::vector<Node> tree;
    std::vector<int> root;

    persistSeg() { clear(); }
    persistSeg(int _n) { build(_n); }

    auto clear()
    {
        n = 0;
        tree.assign(1, Node());
        root.assign(1, 0);
    }

    auto build(int _n)
    {
        clear();
        n = _n;
    }

    auto clone(int pre)
    {
        tree.push_back(tree[pre]);
        return (int)tree.size() - 1;
    }

    auto update(int pre, int l, int r, int pos, T val) -> int
    {
        int rt = clone(pre);
        tree[rt].sum += val;
        if (l == r)
            return rt;
        int mid = (l + r) >> 1;
        if (pos <= mid)
            tree[rt].l = update(tree[pre].l, l, mid, pos, val);
        else
            tree[rt].r = update(tree[pre].r, mid + 1, r, pos, val);
        return rt;
    }

    auto insert(int preRoot, int pos, T val = 1)
    {
        return update(preRoot, 1, n, pos, val);
    }

    auto insertVersion(int preVersion, int pos, T val = 1)
    {
        root.push_back(insert(root[preVersion], pos, val));
        return (int)root.size() - 1;
    }

    auto query(int rt, int l, int r, int x, int y) const -> T
    {
        if (!rt || r < x || l > y)
            return 0;
        if (x <= l && r <= y)
            return tree[rt].sum;
        int mid = (l + r) >> 1;
        return query(tree[rt].l, l, mid, x, y) + query(tree[rt].r, mid + 1, r, x, y);
    }

    auto query(int rt, int l, int r) const
    {
        return query(rt, 1, n, l, r);
    }

    auto kth(int leftRoot, int rightRoot, int l, int r, T k) const -> int
    {
        if (l == r)
            return l;
        int mid = (l + r) >> 1;
        T size = tree[tree[rightRoot].l].sum - tree[tree[leftRoot].l].sum;
        if (k <= size)
            return kth(tree[leftRoot].l, tree[rightRoot].l, l, mid, k);
        return kth(tree[leftRoot].r, tree[rightRoot].r, mid + 1, r, k - size);
    }

    auto kth(int leftRoot, int rightRoot, T k) const
    {
        return kth(leftRoot, rightRoot, 1, n, k);
    }
};
