#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
namespace dataStructure
{
    struct decomposition
    {
        vector<int> dep, fa;
        vector<int> sze, son;
        vector<int> dfn, top;
        decomposition() = default;
        decomposition(int n, const vector<vector<int>> &g)
            : dep(n + 5), fa(n + 5), sze(n + 5), son(n + 5), top(n + 5)
        {
            function<void(int, int)> dfs1 = [&](int u, int _fa)
            {
                sze[u] = 1;
                dep[u] = dep[fa[u] = _fa] + 1;
                for (auto v : g[u])
                {
                    if (v == _fa)
                        continue;
                    dfs1(v, u);
                    sze[u] += sze[v];
                    if (sze[v] > sze[son[u]])
                        son[u] = v;
                }
            };
            int dfstime = 0;
            function<void(int, int)> dfs2 = [&](int u, int topf)
            {
                dfn[u] = ++dfstime;
                top[u] = topf;
                if (son[u])
                    dfs2(son[u], topf);
                for (auto v : g[u])
                {
                    if (dfn[v])
                        continue;
                    dfs2(v, v);
                }
            };
            dfs1(1, 0);
            dfs2(1, 1);
        }
    };
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
    struct satt
    {
        struct tag
        {
            int k, b;
            tag(int _k = 1, int _b = 0) : k(_k), b(_b) {}
            auto friend operator+(int x, tag y) { return y.k * x + y.b; }
            auto operator+(tag rhs) { return tag(k * rhs.k, b * rhs.k + rhs.b); }
            auto ne() { return k != 1 || b != 0; }
        };
        struct data
        {
            int sze, min, max, sum;
            data(int _sze = 0, int _min = INT_MAX, int _max = INT_MIN, int _sum = 0)
                : sze(_sze), min(_min), max(_max), sum(_sum) {}
            auto operator+(tag rhs) const
            {
                return data(sze,
                            min == INT_MAX ? INT_MAX : min + rhs,
                            max == INT_MIN ? INT_MIN : max + rhs,
                            sum * rhs.k + sze * rhs.b);
            }
            auto operator+(data rhs) const
            {
                return data(sze + rhs.sze, ::min(min, rhs.min), ::max(max, rhs.max), sum + rhs.sum);
            }
        };
        struct node
        {
            int ch[3], fa;
            int left, right;
            int val;
            data pat, sub;
            tag tpat, tsub;
            bool rev;
            auto reverse()
            {
                rev ^= 1;
                swap(ch[0], ch[1]);
                swap(left, right);
            }
            auto path(tag _tag)
            {
                val = val + _tag;
                pat = pat + _tag;
                tpat = tpat + _tag;
            }
            auto subtree(tag _tag)
            {
                sub = sub + _tag;
                tsub = tsub + _tag;
            }
        };
        vector<node> tree;
#define lc(x) tree[x].ch[0]
#define rc(x) tree[x].ch[1]
#define mc(x) tree[x].ch[2]
#define fa(x) tree[x].fa
        stack<int, vector<int>> rec;
        auto newnode()
        {
            if (!rec.empty())
            {
                int now = rec.top();
                rec.pop();
                tree[now] = node();
                return now;
            }
            else
            {
                tree.emplace_back();
                return (int)tree.size() - 1;
            }
        }
        auto recycle(int x) { rec.push(x); }
        auto direction(int x) { return lc(fa(x)) == x ? 0 : (rc(fa(x)) == x ? 1 : 2); }
        auto nroot(int x) { return lc(fa(x)) == x || rc(fa(x)) == x; }
        auto set(int x, int fa, int t)
        {
            if (x)
            {
                tree[fa(x)].ch[direction(x)] = 0;
                fa(x) = fa;
            }
            tree[fa].ch[t] = x;
        }
        auto pushup(int x, int t)
        {
            tree[x].left = lc(x) ? tree[lc(x)].left : x;
            tree[x].right = rc(x) ? tree[rc(x)].right : x;
            if (!t)
            {
                tree[x].pat = tree[lc(x)].pat + data(1, tree[x].val, tree[x].val, tree[x].val) + tree[rc(x)].pat;
                tree[x].sub = tree[lc(x)].sub + tree[mc(x)].sub + tree[rc(x)].sub;
            }
            else
                tree[x].sub = tree[lc(x)].sub + tree[rc(x)].sub + tree[mc(x)].sub + tree[mc(x)].pat;
        }
        auto pushdown(int x, int t)
        {
            if (!t)
            {
                if (tree[x].rev)
                {
                    if (lc(x))
                        tree[lc(x)].reverse();
                    if (rc(x))
                        tree[rc(x)].reverse();
                    tree[x].rev = false;
                }
                if (tree[x].tpat.ne())
                {
                    if (lc(x))
                        tree[lc(x)].path(tree[x].tpat);
                    if (rc(x))
                        tree[rc(x)].path(tree[x].tpat);
                    tree[x].tpat = tag();
                }
                if (tree[x].tsub.ne())
                {
                    if (lc(x))
                        tree[lc(x)].subtree(tree[x].tsub);
                    if (rc(x))
                        tree[rc(x)].subtree(tree[x].tsub);
                    if (mc(x))
                        tree[mc(x)].subtree(tree[x].tsub);
                    tree[x].tsub = tag();
                }
            }
            else
            {
                if (tree[x].tsub.ne())
                {
                    if (lc(x))
                        tree[lc(x)].subtree(tree[x].tsub);
                    if (rc(x))
                        tree[rc(x)].subtree(tree[x].tsub);
                    if (mc(x))
                    {
                        tree[mc(x)].path(tree[x].tsub);
                        tree[mc(x)].subtree(tree[x].tsub);
                    }
                    tree[x].tsub = tag();
                }
            }
        }
        auto rotate(int x, int t)
        {
            int y = fa(x), z = fa(y), k = direction(x), w = tree[x].ch[k ^ 1];
            if (z)
                tree[z].ch[direction(y)] = x;
            fa(x) = z;

            tree[x].ch[k ^ 1] = y;
            fa(y) = x;

            tree[y].ch[k] = w;
            if (w)
                fa(w) = y;

            pushup(y, t), pushup(x, t);
        }
        stack<int, vector<int>> st;
        auto splay(int x, int t, int tar = 0)
        {
            st.push(x);
            for (int y = x; nroot(y); y = fa(y))
                st.push(fa(y));
            while (!st.empty())
            {
                pushdown(st.top(), t);
                st.pop();
            }
            while (nroot(x) && fa(x) != tar)
            {
                if (nroot(fa(x)) && fa(fa(x)) != tar)
                    rotate(direction(fa(x)) == direction(x) ? fa(x) : x, t);
                rotate(x, t);
            }
        }
        auto del(int x)
        {
            if (lc(x))
            {
                int y = tree[lc(x)].right;
                splay(y, 1, x);
                set(rc(x), y, 1);
                set(y, fa(x), 2);
                pushup(y, 1), pushup(fa(x), 0);
            }
            else
            {
                set(rc(x), fa(x), 2);
                pushup(fa(x), 0);
            }
            recycle(x);
        }
        auto splice(int x)
        {
            splay(x, 1);
            int y = fa(x);
            splay(y, 0);
            pushdown(x, 1);
            if (rc(y))
            {
                swap(fa(mc(x)), fa(rc(y)));
                swap(mc(x), rc(y));
                pushup(x, 1), pushup(y, 0);
            }
            else
            {
                set(mc(x), y, 1);
                del(x);
                pushup(y, 0);
            }
        }
        auto access(int x)
        {
            splay(x, 0);
            if (rc(x))
            {
                int y = newnode();
                set(mc(x), y, 0);
                set(rc(x), y, 2);
                set(y, x, 2);
                pushup(y, 1), pushup(x, 0);
            }
            for (int y = x; fa(y); y = fa(y))
                splice(fa(y));
            splay(x, 0);
        }
        auto findroot(int x)
        {
            access(x);
            return tree[x].left;
        }
        auto makeroot(int x)
        {
            access(x);
            tree[x].reverse();
        }
        auto expose(int x, int y)
        {
            makeroot(x);
            access(y);
        }
        auto link(int x, int y)
        {
            access(x);
            makeroot(y);
            set(y, x, 1);
            pushup(x, 0);
        }
        auto cut(int x, int y)
        {
            expose(x, y);
            fa(x) = lc(y) = 0;
            pushup(y, 0);
        }
        int root;
        auto modify(int x, tag y)
        {
            expose(root, x);
            tree[x].val = tree[x].val + y;
            tree[mc(x)].subtree(y);
            pushup(x, 0);
        }
        auto modify(int x, int y, tag z)
        {
            expose(x, y);
            tree[y].path(z);
            pushup(y, 0);
        }
        auto query(int x)
        {
            expose(root, x);
            return tree[mc(x)].sub + data(1, tree[x].val, tree[x].val, tree[x].val);
        }
        auto query(int x, int y)
        {
            expose(x, y);
            return tree[y].pat;
        }
        auto changeFa(int x, int y)
        {
            if (x == root || x == y)
                return;
            expose(root, x);
            int p = tree[lc(x)].right;
            lc(x) = fa(lc(x)) = 0;
            pushup(x, 0);
            if (findroot(x) == findroot(y))
                link(x, p);
            else
                link(x, y);
        }
        satt() = default;
        satt(const vector<int> &p, int _root) : tree(p.size()), root(_root)
        {
            for (int i = 1; i < (int)p.size(); ++i)
            {
                tree[i].val = p[i];
                pushup(i, 0);
            }
        }
#undef lc
#undef rc
#undef ms
#undef fa
    };
};
auto _main()
{
    int n, m, root;
    cin >> n >> m;
    vector<int> p(n + 1);
    vector<pair<int, int>> edges(n - 1);
    for (auto &[x, y] : edges)
        cin >> x >> y;
    for (int i = 1; i <= n; ++i)
        cin >> p[i];
    cin >> root;
    dataStructure::satt satt(p, root);
    for (auto [x, y] : edges)
        satt.link(x, y);
    while (m--)
    {
        int opt, x, y, z;
        cin >> opt >> x;
        if (opt == 0 || opt == 5)
        {
            cin >> y;
            satt.modify(x, dataStructure::satt::tag(opt == 5, y));
        }
        else if (opt == 1)
            satt.root = x;
        else if (opt == 2 || opt == 6)
        {
            cin >> y >> z;
            satt.modify(x, y, dataStructure::satt::tag(opt == 6, z));
        }
        else if (opt == 3)
            cout << satt.query(x).min << '\n';
        else if (opt == 4)
            cout << satt.query(x).max << '\n';
        else if (opt == 11)
            cout << satt.query(x).sum << '\n';
        else
        {
            cin >> y;
            if (opt == 7)
                cout << satt.query(x, y).min << '\n';
            else if (opt == 8)
                cout << satt.query(x, y).max << '\n';
            else if (opt == 10)
                cout << satt.query(x, y).sum << '\n';
            else
                satt.changeFa(x, y);
        }
    }
}
signed main()
{
#ifdef PAPERDOG
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--)
        _main();
    return 0;
}
