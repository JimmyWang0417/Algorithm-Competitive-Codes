#pragma once
#include <algorithm>
#include <limits>
#include <vector>

#define lc (rt << 1)
#define rc (rt << 1 | 1)

template <typename T = long long>
struct segTree
{
    struct Node
    {
        int len = 0, lpos = 0, minPos = 0;
        T sum = 0, max = numeric_limits<T>::lowest() / 4;
        T min = numeric_limits<T>::max() / 4;
        T add = 0, setv = 0;
        bool hasSet = false;
    };

    int n = 0;
    vector<Node> tree;

    segTree() = default;
    segTree(int _n) : n(_n), tree(n * 4 + 5)
    {
        vector<T> a(n + 1);
        if (n)
            build(1, 1, n, a);
    }
    segTree(const vector<T> &a) : n((int)a.size() - 1), tree(n * 4 + 5)
    {
        if (n)
            build(1, 1, n, a);
    }

    auto init(int _n)
    {
        n = _n;
        tree.resize(n * 4 + 5);
    }

    auto merge(const Node &lhs, const Node &rhs) const
    {
        if (!lhs.len)
            return rhs;
        if (!rhs.len)
            return lhs;
        Node res;
        res.len = lhs.len + rhs.len;
        res.lpos = lhs.lpos;
        res.sum = lhs.sum + rhs.sum;
        res.max = max(lhs.max, rhs.max);
        res.min = min(lhs.min, rhs.min);
        res.minPos = lhs.min <= rhs.min ? lhs.minPos : rhs.minPos;
        return res;
    }

    auto pushup(int rt)
    {
        tree[rt] = merge(tree[lc], tree[rc]);
    }

    auto applySet(int rt, T val)
    {
        tree[rt].sum = val * tree[rt].len;
        tree[rt].max = tree[rt].min = val;
        tree[rt].minPos = tree[rt].lpos;
        tree[rt].setv = val;
        tree[rt].add = 0;
        tree[rt].hasSet = true;
    }

    auto applyAdd(int rt, T val)
    {
        tree[rt].sum += val * tree[rt].len;
        tree[rt].max += val;
        tree[rt].min += val;
        if (tree[rt].hasSet)
            tree[rt].setv += val;
        else
            tree[rt].add += val;
    }

    auto pushdown(int rt)
    {
        if (tree[rt].hasSet)
        {
            applySet(lc, tree[rt].setv);
            applySet(rc, tree[rt].setv);
            tree[rt].hasSet = false;
        }
        if (tree[rt].add)
        {
            applyAdd(lc, tree[rt].add);
            applyAdd(rc, tree[rt].add);
            tree[rt].add = 0;
        }
    }

    auto build(int rt, int l, int r, const vector<T> &a) -> void
    {
        tree[rt].len = r - l + 1;
        tree[rt].lpos = tree[rt].minPos = l;
        tree[rt].add = tree[rt].setv = 0;
        tree[rt].hasSet = false;
        if (l == r)
        {
            T val = l < (int)a.size() ? a[l] : T();
            tree[rt].sum = tree[rt].max = tree[rt].min = val;
            return;
        }
        int mid = (l + r) >> 1;
        build(lc, l, mid, a);
        build(rc, mid + 1, r, a);
        pushup(rt);
    }

    auto build(int _n)
    {
        init(_n);
        vector<T> a(n + 1);
        if (n)
            build(1, 1, n, a);
    }

    auto build(const vector<T> &a)
    {
        init((int)a.size() - 1);
        if (n)
            build(1, 1, n, a);
    }

    auto rangeAdd(int rt, int l, int r, int x, int y, T val) -> void
    {
        if (r < x || l > y)
            return;
        if (x <= l && r <= y)
            return applyAdd(rt, val);
        int mid = (l + r) >> 1;
        pushdown(rt);
        rangeAdd(lc, l, mid, x, y, val);
        rangeAdd(rc, mid + 1, r, x, y, val);
        pushup(rt);
    }

    auto rangeSet(int rt, int l, int r, int x, int y, T val) -> void
    {
        if (r < x || l > y)
            return;
        if (x <= l && r <= y)
            return applySet(rt, val);
        int mid = (l + r) >> 1;
        pushdown(rt);
        rangeSet(lc, l, mid, x, y, val);
        rangeSet(rc, mid + 1, r, x, y, val);
        pushup(rt);
    }

    auto query(int rt, int l, int r, int x, int y) -> Node
    {
        if (r < x || l > y)
            return Node();
        if (x <= l && r <= y)
            return tree[rt];
        int mid = (l + r) >> 1;
        pushdown(rt);
        return merge(query(lc, l, mid, x, y),
                     query(rc, mid + 1, r, x, y));
    }

    auto rangeAdd(int l, int r, T val)
    {
        if (l <= r && n)
            rangeAdd(1, 1, n, l, r, val);
    }

    auto rangeSet(int l, int r, T val)
    {
        if (l <= r && n)
            rangeSet(1, 1, n, l, r, val);
    }

    auto pointSet(int pos, T val)
    {
        rangeSet(pos, pos, val);
    }

    auto query(int l, int r)
    {
        return l <= r && n ? query(1, 1, n, l, r) : Node();
    }

    auto querySum(int l, int r) { return query(l, r).sum; }
    auto queryMax(int l, int r) { return query(l, r).max; }
    auto queryMin(int l, int r) { return query(l, r).min; }
    auto queryMinPos(int l, int r) { return query(l, r).minPos; }

    template <typename Func>
    auto findFirst(int rt, int l, int r, int x, int y, const Func &pred) -> int
    {
        if (r < x || l > y || !pred(tree[rt]))
            return -1;
        if (l == r)
            return l;
        int mid = (l + r) >> 1;
        pushdown(rt);
        int res = findFirst(lc, l, mid, x, y, pred);
        if (res != -1)
            return res;
        return findFirst(rc, mid + 1, r, x, y, pred);
    }

    template <typename Func>
    auto findLast(int rt, int l, int r, int x, int y, const Func &pred) -> int
    {
        if (r < x || l > y || !pred(tree[rt]))
            return -1;
        if (l == r)
            return l;
        int mid = (l + r) >> 1;
        pushdown(rt);
        int res = findLast(rc, mid + 1, r, x, y, pred);
        if (res != -1)
            return res;
        return findLast(lc, l, mid, x, y, pred);
    }

    template <typename Func>
    auto findFirst(int l, int r, const Func &pred)
    {
        return l <= r && n ? findFirst(1, 1, n, l, r, pred) : -1;
    }

    template <typename Func>
    auto findLast(int l, int r, const Func &pred)
    {
        return l <= r && n ? findLast(1, 1, n, l, r, pred) : -1;
    }
};

#undef lc
#undef rc
