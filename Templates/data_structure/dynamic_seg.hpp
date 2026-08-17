#pragma once
#include <vector>

#define lc(x) tree[x].l
#define rc(x) tree[x].r

template <typename T = long long>
struct DynamicSeg
{
    struct Node
    {
        int l = 0, r = 0;
        T sum = 0;
    };

    vector<Node> tree;

    DynamicSeg() : tree(1) {}

    auto newnode()
    {
        tree.push_back(Node());
        return (int)tree.size() - 1;
    }

    auto pushup(int rt)
    {
        tree[rt].sum = tree[lc(rt)].sum + tree[rc(rt)].sum;
    }

    auto update(int &rt, int l, int r, int pos, T val) -> void
    {
        if (!rt)
            rt = newnode();
        tree[rt].sum += val;
        if (l == r)
            return;
        int mid = (l + r) >> 1;
        if (pos <= mid)
        {
            int child = lc(rt);
            update(child, l, mid, pos, val);
            lc(rt) = child;
        }
        else
        {
            int child = rc(rt);
            update(child, mid + 1, r, pos, val);
            rc(rt) = child;
        }
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

    auto kth(int rt, int l, int r, T k) const -> int
    {
        if (l == r)
            return l;
        int mid = (l + r) >> 1;
        if (k <= tree[lc(rt)].sum)
            return kth(lc(rt), l, mid, k);
        return kth(rc(rt), mid + 1, r, k - tree[lc(rt)].sum);
    }

    auto merge(int x, int y, int l, int r) -> int
    {
        if (!x || !y)
            return x | y;
        if (l == r)
        {
            tree[x].sum += tree[y].sum;
            return x;
        }
        int mid = (l + r) >> 1;
        lc(x) = merge(lc(x), lc(y), l, mid);
        rc(x) = merge(rc(x), rc(y), mid + 1, r);
        pushup(x);
        return x;
    }

    auto split(int &pre, int l, int r, int x, int y) -> int
    {
        if (!pre || r < x || l > y)
            return 0;
        if (x <= l && r <= y)
        {
            int rt = pre;
            pre = 0;
            return rt;
        }
        int rt = newnode(), mid = (l + r) >> 1;
        int leftPre = lc(pre), rightPre = rc(pre);
        int left = split(leftPre, l, mid, x, y);
        int right = split(rightPre, mid + 1, r, x, y);
        lc(pre) = leftPre;
        rc(pre) = rightPre;
        lc(rt) = left;
        rc(rt) = right;
        pushup(pre);
        pushup(rt);
        return rt;
    }
};

#undef lc
#undef rc
