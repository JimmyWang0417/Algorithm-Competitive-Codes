template <typename T = int>
struct odt
{
    struct node
    {
        int l, r;
        mutable T v;
        node(int _l, int _r, const T &_v) : l(_l), r(_r), v(_v) {}
        auto operator<=>(const node &rhs) const = default;
    };
    int n;
    set<node> tree;
    auto split(int x)
    {
        if (x > n)
            return tree.end();
        auto it = tree.lower_bound(node(x, 0, T()));
        if (it != tree.end() && it->l == x)
            return it;
        --it;
        auto [l, r, v] = *it;
        tree.erase(it);
        tree.emplace(l, x - 1, v);
        return tree.emplace(x, r, v).first;
    }
    auto assign(int l, int r, const T &v)
    {
        auto itr = split(r + 1), itl = split(l);
        tree.erase(itl, itr);
        tree.emplace(l, r, v);
    }
    template <typename F>
    auto perform(int l, int r, F func)
    {
        auto itr = split(r + 1), itl = split(l);
        for (auto it = itl; it != itr; ++it)
            func(*it);
    }
    odt(int _n, const T &v = T()) : n(_n)
    {
        if (n)
            tree.emplace(1, n, v);
    }
    odt(const vector<T> &a) : n((int)a.size() - 1)
    {
        for (int i = 1; i <= n; ++i)
            tree.emplace(i, i, a[i]);
    }
};
