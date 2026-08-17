#pragma once
#include <chrono>
#include <limits>
#include <random>
#include <vector>

#define lc(x) tree[x].ch[0]
#define rc(x) tree[x].ch[1]

template <typename T = int>
struct treap
{
    struct Node
    {
        int ch[2] = {0, 0};
        int size = 0, cnt = 0;
        unsigned key = 0;
        T val = 0;
    };

    int root = 0;
    vector<Node> tree;
    mt19937 rnd;

    treap() : tree(1), rnd((unsigned)chrono::steady_clock::now().time_since_epoch().count()) {}

    auto newnode(T val)
    {
        tree.push_back(Node());
        int rt = (int)tree.size() - 1;
        tree[rt].val = val;
        tree[rt].key = rnd();
        tree[rt].size = tree[rt].cnt = 1;
        return rt;
    }

    auto pushup(int rt)
    {
        tree[rt].size = tree[lc(rt)].size + tree[rc(rt)].size + tree[rt].cnt;
    }

    auto rotate(int &rt, int d)
    {
        int k = tree[rt].ch[d ^ 1];
        tree[rt].ch[d ^ 1] = tree[k].ch[d];
        tree[k].ch[d] = rt;
        pushup(rt), pushup(k);
        rt = k;
    }

    auto insert(int &rt, T val) -> void
    {
        if (!rt)
        {
            rt = newnode(val);
            return;
        }
        if (tree[rt].val == val)
        {
            ++tree[rt].cnt;
            pushup(rt);
            return;
        }
        int d = val > tree[rt].val;
        int child = tree[rt].ch[d];
        insert(child, val);
        tree[rt].ch[d] = child;
        if (tree[tree[rt].ch[d]].key > tree[rt].key)
            rotate(rt, d ^ 1);
        pushup(rt);
    }

    auto erase(int &rt, T val) -> void
    {
        if (!rt)
            return;
        if (val < tree[rt].val)
            erase(lc(rt), val);
        else if (val > tree[rt].val)
            erase(rc(rt), val);
        else
        {
            if (tree[rt].cnt > 1)
                --tree[rt].cnt;
            else if (!lc(rt) || !rc(rt))
                rt = lc(rt) | rc(rt);
            else
            {
                int d = tree[lc(rt)].key > tree[rc(rt)].key;
                rotate(rt, d);
                erase(tree[rt].ch[d], val);
            }
        }
        if (rt)
            pushup(rt);
    }

    auto insert(T val) { insert(root, val); }
    auto erase(T val) { erase(root, val); }

    auto rank(int rt, T val) const -> int
    {
        if (!rt)
            return 1;
        if (val <= tree[rt].val)
            return rank(lc(rt), val);
        return tree[lc(rt)].size + tree[rt].cnt + rank(rc(rt), val);
    }

    auto kth(int rt, int k) const -> T
    {
        if (k <= tree[lc(rt)].size)
            return kth(lc(rt), k);
        if (k > tree[lc(rt)].size + tree[rt].cnt)
            return kth(rc(rt), k - tree[lc(rt)].size - tree[rt].cnt);
        return tree[rt].val;
    }

    auto pre(T val) const
    {
        int rt = root;
        T res = numeric_limits<T>::lowest();
        while (rt)
        {
            if (tree[rt].val < val)
                res = tree[rt].val, rt = rc(rt);
            else
                rt = lc(rt);
        }
        return res;
    }

    auto next(T val) const
    {
        int rt = root;
        T res = numeric_limits<T>::max();
        while (rt)
        {
            if (tree[rt].val > val)
                res = tree[rt].val, rt = lc(rt);
            else
                rt = rc(rt);
        }
        return res;
    }

    auto rank(T val) const { return rank(root, val); }
    auto kth(int k) const { return kth(root, k); }
};

#undef lc
#undef rc
