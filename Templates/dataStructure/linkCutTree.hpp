namespace dataStructure
{
    struct linkCutTree
    {
        struct node
        {
            int ch[2], fa;
            bool rev;
            int val, ans;
            auto reverse() { rev ^= 1; }
        };
        vector<node> tree;
#define lc(x) tree[x].ch[0]
#define rc(x) tree[x].ch[1]
#define fa(x) tree[x].fa
        auto direction(int x) { return rc(fa(x)) == x; }
        auto nroot(int x) { return lc(fa(x)) == x || rc(fa(x)) == x; }
        auto pushup(int x)
        {
            tree[x].ans = tree[lc(x)].ans ^ tree[x].val ^ tree[rc(x)].ans;
        }
        auto pushdown(int x)
        {
            if (tree[x].rev)
            {
                if (lc(x))
                    tree[lc(x)].reverse();
                if (rc(x))
                    tree[rc(x)].reverse();
                swap(lc(x), rc(x));
                tree[x].rev = false;
            }
        }
        auto rotate(int x)
        {
            int y = fa(x), z = fa(y), k = direction(x), w = tree[x].ch[k ^ 1];
            if (nroot(y))
                tree[z].ch[direction(y)] = x;
            fa(x) = z;

            tree[x].ch[k ^ 1] = y;
            fa(y) = x;

            tree[y].ch[k] = w;
            if (w)
                fa(w) = y;

            pushup(y), pushup(x), pushup(z);
        }
        stack<int, vector<int>> st;
        auto splay(int x)
        {
            st.push(x);
            for (int y = x; nroot(y); y = fa(y))
                st.push(fa(y));
            while (!st.empty())
            {
                pushdown(st.top());
                st.pop();
            }
            while (nroot(x))
            {
                if (nroot(fa(x)))
                    rotate(direction(fa(x)) == direction(x) ? fa(x) : x);
                rotate(x);
            }
        }
        auto access(int x)
        {
            for (int y = 0; x; x = fa(y = x))
            {
                splay(x);
                rc(x) = y;
                pushup(x);
            }
        }
        auto findroot(int x)
        {
            access(x);
            splay(x);
            while (pushdown(x), lc(x))
                x = lc(x);
            return x;
        }
        auto makeroot(int x)
        {
            access(x);
            splay(x);
            tree[x].reverse();
        }
        auto split(int x, int y)
        {
            makeroot(x);
            access(y);
            splay(y);
        }
        auto link(int x, int y)
        {
            if (findroot(x) == findroot(y))
                return;
            makeroot(x);
            fa(x) = y;
            splay(y);
        }
        auto cut(int x, int y)
        {
            split(x, y);
            if (lc(y) != x || rc(x))
                return;
            fa(x) = lc(y) = 0;
            pushup(y);
        }
        auto update(int x, int y)
        {
            splay(x);
            tree[x].val = y;
            pushup(x);
        }
        linkCutTree() = default;
        linkCutTree(const vector<int> &p) : tree(p.size())
        {
            for (int i = 1; i < (int)p.size(); ++i)
            {
                tree[i].val = p[i];
                pushup(i);
            }
        }
#undef lc
#undef rc
#undef fa
    };
};