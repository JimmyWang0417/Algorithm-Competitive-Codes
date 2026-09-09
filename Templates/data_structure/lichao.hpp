struct lichao
{
    struct node
    {
        i64 k, b;
        node(i64 _k = 0, i64 _b = LLONG_MIN) : k(_k), b(_b) {}
        auto calc(i64 x) const { return k * x + b; }
    };
    vector<i64> p;
    vector<node> tree;
#define lc (rt << 1)
#define rc (rt << 1 | 1)
    auto update(int rt, int l, int r, int x, int y, node val) -> void
    {
        if (r < x || l > y)
            return;
        int mid = (l + r) >> 1;
        if (x <= l && r <= y)
        {
            if (val.calc(p[mid]) > tree[rt].calc(p[mid]))
                swap(val, tree[rt]);
            if (l == r)
                return;
            if (val.k < tree[rt].k)
                update(lc, l, mid, x, y, val);
            else if (val.k > tree[rt].k)
                update(rc, mid + 1, r, x, y, val);
            return;
        }
        update(lc, l, mid, x, y, val);
        update(rc, mid + 1, r, x, y, val);
    }
    auto query(int rt, int l, int r, int pos) const -> i64
    {
        if (l == r)
            return tree[rt].calc(p[pos]);
        int mid = (l + r) >> 1;
        return max(tree[rt].calc(p[pos]),
                   pos <= mid ? query(lc, l, mid, pos) : query(rc, mid + 1, r, pos));
    }
    auto update(node val) { update(1, 0, (int)p.size() - 1, 0, (int)p.size() - 1, val); }
    auto query(i64 val) const
    {
        int pos = (int)(lower_bound(p.begin(), p.end(), val) - p.begin());
        return query(1, 0, (int)p.size() - 1, pos);
    }
    lichao(const vector<i64> &_p) : p(_p)
    {
        sort(p.begin(), p.end());
        p.erase(unique(p.begin(), p.end()), p.end());
        tree.resize(p.size() * 4);
    }
#undef lc
#undef rc
};
