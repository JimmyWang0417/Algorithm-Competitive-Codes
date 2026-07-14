#pragma once
#include <limits>
#include <vector>

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
    std::vector<Node> tree;

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
        tree[rt].size = tree[tree[rt].ch[0]].size + tree[tree[rt].ch[1]].size + tree[rt].cnt;
    }

    auto direction(int rt)
    {
        return tree[tree[rt].fa].ch[1] == rt;
    }

    auto rotate(int x)
    {
        int y = tree[x].fa, z = tree[y].fa;
        int k = direction(x), w = tree[x].ch[k ^ 1];
        tree[z].ch[tree[z].ch[1] == y] = x;
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
                rotate(direction(x) == direction(y) ? y : x);
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
            tree[las].ch[val > tree[las].val] = rt;
        }
        splayTo(rt);
    }

    auto rank(T val)
    {
        int rt = root, res = 1;
        while (rt)
        {
            if (val <= tree[rt].val)
                rt = tree[rt].ch[0];
            else
            {
                res += tree[tree[rt].ch[0]].size + tree[rt].cnt;
                rt = tree[rt].ch[1];
            }
        }
        return res;
    }

    auto kth(int k)
    {
        int rt = root;
        while (rt)
        {
            if (k <= tree[tree[rt].ch[0]].size)
                rt = tree[rt].ch[0];
            else if (k > tree[tree[rt].ch[0]].size + tree[rt].cnt)
            {
                k -= tree[tree[rt].ch[0]].size + tree[rt].cnt;
                rt = tree[rt].ch[1];
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
                ans = rt, rt = tree[rt].ch[1];
            else
                rt = tree[rt].ch[0];
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
                ans = rt, rt = tree[rt].ch[0];
            else
                rt = tree[rt].ch[1];
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
        if (!tree[rt].ch[0] || !tree[rt].ch[1])
        {
            root = tree[rt].ch[0] | tree[rt].ch[1];
            tree[root].fa = 0;
            return;
        }
        int x = tree[rt].ch[0];
        while (tree[x].ch[1])
            x = tree[x].ch[1];
        splayTo(x, rt);
        tree[x].ch[1] = tree[rt].ch[1];
        tree[tree[x].ch[1]].fa = x;
        tree[x].fa = 0;
        root = x;
        pushup(root);
    }

    auto pre(T val)
    {
        T res = std::numeric_limits<T>::lowest();
        pre(val, res);
        return res;
    }

    auto next(T val)
    {
        T res = std::numeric_limits<T>::max();
        next(val, res);
        return res;
    }
};
