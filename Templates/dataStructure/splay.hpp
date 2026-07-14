#pragma once
#include <limits>
#include <vector>

#define lc(x) tree[x].ch[0]
#define rc(x) tree[x].ch[1]

template <typename T = int>
struct splay
{
    struct Node
    {
        T val = 0;
        int ch[2] = {0, 0};
        int fa = 0, cnt = 0, size = 0;
    };

    int root = 0;
    vector<Node> tree;

    splay() : tree(1) {}

    auto newnode(T val, int fa)
    {
        tree.push_back(Node());
        int rt = (int)tree.size() - 1;
        tree[rt].val = val;
        tree[rt].fa = fa;
        tree[rt].cnt = tree[rt].size = 1;
        return rt;
    }

    auto pushup(int rt)
    {
        tree[rt].size = tree[lc(rt)].size + tree[rc(rt)].size + tree[rt].cnt;
    }

    auto check(int rt)
    {
        return rc(tree[rt].fa) == rt;
    }

    auto rotate(int x)
    {
        int y = tree[x].fa, z = tree[y].fa;
        int k = check(x), w = tree[x].ch[k ^ 1];
        tree[z].ch[rc(z) == y] = x;
        tree[x].fa = z;
        tree[y].ch[k] = w;
        tree[w].fa = y;
        tree[x].ch[k ^ 1] = y;
        tree[y].fa = x;
        pushup(y), pushup(x);
    }

    auto splayTo(int x, int target = 0)
    {
        while (tree[x].fa != target)
        {
            int y = tree[x].fa, z = tree[y].fa;
            if (z != target)
                rotate(check(x) == check(y) ? y : x);
            rotate(x);
        }
        if (!target)
            root = x;
    }

    auto find(T val)
    {
        int rt = root, las = 0;
        while (rt && tree[rt].val != val)
        {
            las = rt;
            rt = tree[rt].ch[val > tree[rt].val];
        }
        if (rt)
            splayTo(rt);
        else if (las)
            splayTo(las);
        return rt;
    }

    auto insert(T val)
    {
        if (!root)
        {
            root = newnode(val, 0);
            return;
        }
        int rt = root, las = 0;
        while (rt && tree[rt].val != val)
        {
            las = rt;
            rt = tree[rt].ch[val > tree[rt].val];
        }
        if (rt)
            ++tree[rt].cnt;
        else
        {
            rt = newnode(val, las);
            if (val < tree[las].val)
                lc(las) = rt;
            else
                rc(las) = rt;
        }
        splayTo(rt);
    }

    auto rank(T val)
    {
        int rt = root, res = 1;
        while (rt)
        {
            if (val <= tree[rt].val)
                rt = lc(rt);
            else
            {
                res += tree[lc(rt)].size + tree[rt].cnt;
                rt = rc(rt);
            }
        }
        return res;
    }

    auto kth(int k)
    {
        int rt = root;
        while (rt)
        {
            if (k <= tree[lc(rt)].size)
                rt = lc(rt);
            else if (k > tree[lc(rt)].size + tree[rt].cnt)
            {
                k -= tree[lc(rt)].size + tree[rt].cnt;
                rt = rc(rt);
            }
            else
            {
                splayTo(rt);
                return tree[rt].val;
            }
        }
        return T();
    }

    auto pre(T val, T &res)
    {
        int rt = root, ans = 0;
        while (rt)
        {
            if (tree[rt].val < val)
                ans = rt, rt = rc(rt);
            else
                rt = lc(rt);
        }
        if (!ans)
            return false;
        splayTo(ans);
        res = tree[ans].val;
        return true;
    }

    auto next(T val, T &res)
    {
        int rt = root, ans = 0;
        while (rt)
        {
            if (tree[rt].val > val)
                ans = rt, rt = lc(rt);
            else
                rt = rc(rt);
        }
        if (!ans)
            return false;
        splayTo(ans);
        res = tree[ans].val;
        return true;
    }

    auto erase(T val)
    {
        int rt = find(val);
        if (!rt)
            return;
        if (tree[rt].cnt > 1)
        {
            --tree[rt].cnt;
            pushup(rt);
            return;
        }
        if (!lc(rt) || !rc(rt))
        {
            root = lc(rt) | rc(rt);
            tree[root].fa = 0;
            return;
        }
        int x = lc(rt);
        while (rc(x))
            x = rc(x);
        splayTo(x, rt);
        rc(x) = rc(rt);
        tree[rc(x)].fa = x;
        tree[x].fa = 0;
        root = x;
        pushup(root);
    }

    auto pre(T val)
    {
        T res = numeric_limits<T>::lowest();
        pre(val, res);
        return res;
    }

    auto next(T val)
    {
        T res = numeric_limits<T>::max();
        next(val, res);
        return res;
    }
};

#undef lc
#undef rc
