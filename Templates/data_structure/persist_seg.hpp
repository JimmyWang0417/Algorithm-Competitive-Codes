#pragma once
#include <vector>

#define lc(x) tree[x].l
#define rc(x) tree[x].r

template <typename T = int>
struct PersistSeg
{
    struct Node
    {
        int l = 0, r = 0;
        T sum = 0;
    };

    int n = 0;
    vector<Node> tree;
    vector<int> root;

    PersistSeg() : tree(1), root(1) {}
    PersistSeg(int _n) : n(_n), tree(1), root(1) {}

    auto clear()
    {
        n = 0;
        tree.resize(1);
        root.resize(1);
        tree[0] = Node();
        root[0] = 0;
    }

    auto build(int _n)
    {
        n = _n;
        tree.resize(1);
        root.resize(1);
        tree[0] = Node();
        root[0] = 0;
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
            lc(rt) = update(lc(pre), l, mid, pos, val);
        else
            rc(rt) = update(rc(pre), mid + 1, r, pos, val);
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
        return query(lc(rt), l, mid, x, y) + query(rc(rt), mid + 1, r, x, y);
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
        T size = tree[lc(rightRoot)].sum - tree[lc(leftRoot)].sum;
        if (k <= size)
            return kth(lc(leftRoot), lc(rightRoot), l, mid, k);
        return kth(rc(leftRoot), rc(rightRoot), mid + 1, r, k - size);
    }

    auto kth(int leftRoot, int rightRoot, T k) const
    {
        return kth(leftRoot, rightRoot, 1, n, k);
    }
};

#undef lc
#undef rc
