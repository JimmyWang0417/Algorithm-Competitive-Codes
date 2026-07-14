#pragma once
#include <vector>

template <typename T = long long>
struct dynamicSeg
{
    struct Node
    {
        int l = 0, r = 0;
        T sum = 0;
    };

    std::vector<Node> tree;

    dynamicSeg() { tree.assign(1, Node()); }

    auto newnode()
    {
        tree.push_back(Node());
        return (int)tree.size() - 1;
    }

    auto pushup(int rt)
    {
        tree[rt].sum = tree[tree[rt].l].sum + tree[tree[rt].r].sum;
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
            int child = tree[rt].l;
            update(child, l, mid, pos, val);
            tree[rt].l = child;
        }
        else
        {
            int child = tree[rt].r;
            update(child, mid + 1, r, pos, val);
            tree[rt].r = child;
        }
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

    auto kth(int rt, int l, int r, T k) const -> int
    {
        if (l == r)
            return l;
        int mid = (l + r) >> 1;
        if (k <= tree[tree[rt].l].sum)
            return kth(tree[rt].l, l, mid, k);
        return kth(tree[rt].r, mid + 1, r, k - tree[tree[rt].l].sum);
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
        tree[x].l = merge(tree[x].l, tree[y].l, l, mid);
        tree[x].r = merge(tree[x].r, tree[y].r, mid + 1, r);
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
        int leftPre = tree[pre].l, rightPre = tree[pre].r;
        int left = split(leftPre, l, mid, x, y);
        int right = split(rightPre, mid + 1, r, x, y);
        tree[pre].l = leftPre;
        tree[pre].r = rightPre;
        tree[rt].l = left;
        tree[rt].r = right;
        pushup(pre);
        pushup(rt);
        return rt;
    }
};
