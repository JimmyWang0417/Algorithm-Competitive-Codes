#include <bits/stdc++.h>
using namespace std;
struct segment
{
    struct node
    {
        int tag;
        int min;
        auto update(int v)
        {
            tag += v;
            min += v;
        }
    };
    int n;
    vector<node> tree;
    segment() = default;
    segment(int _n) : n(_n), tree(_n * 4, {0, INT_MAX / 2}) {}
#define lc (rt << 1)
#define rc (rt << 1 | 1)
    auto pushdown(int rt)
    {
        if (tree[rt].tag)
        {
            tree[lc].update(tree[rt].tag);
            tree[rc].update(tree[rt].tag);
            tree[rt].tag = 0;
        }
    }
    auto pushup(int rt)
    {
        tree[rt].min = min(tree[lc].min, tree[rc].min);
    }
    auto update(int rt, int l, int r, int pos, int val)
    {
        if (l == r)
        {
            tree[rt].min = min(tree[rt].min, val);
            return;
        }
        int mid = (l + r) >> 1;
        pushdown(rt);
        if (pos <= mid)
            update(lc, l, mid, pos, val);
        else
            update(rc, mid + 1, r, pos, val);
        pushup(rt);
    }
    auto update(int rt, int l, int r, int x, int y, int val)
    {
        if (r < x || l > y)
            return;
        if (x <= l && r <= y)
            return tree[rt].update(val);
        int mid = (l + r) >> 1;
        pushdown(rt);
        update(lc, l, mid, x, y, val);
        update(rc, mid + 1, r, x, y, val);
        pushup(rt);
    }
    auto query(int rt, int l, int r, int x, int y)
    {
        if (r < x || l > y)
            return INT_MAX / 2;
        if (x <= l && r <= y)
            return tree[rt].min;
        int mid = (l + r) >> 1;
        pushdown(rt);
        return min(query(lc, l, mid, x, y), query(rc, mid + 1, r, x, y));
    }
    auto update(int pos, int val)
    {
        update(1, 1, n, pos, val);
    }
    auto update(int l, int r, int val)
    {
        update(1, 1, n, l, r, val);
    }
    auto query(int x, int y)
    {
        return query(1, 1, n, x, y);
    }
};
struct Main
{
    int n, m, l, k;
    vector<int> a;
    vector<segment> tree;
    Main()
    {
        cin >> n >> l >> k;
        a.resize(n + 5);
        for (int i = 1; i <= n; ++i)
            cin >> a[i];
        {
            vector<int> p;
            for (int i = 1; i <= n; ++i)
                p.emplace_back(a[i]);
            sort(p.begin(), p.end());
            p.erase(unique(p.begin(), p.end()), p.end());
            for (int i = 1; i <= n; ++i)
                a[i] = (int)(lower_bound(p.begin(), p.end(), a[i]) - p.begin() + 1);
            m = (int)p.size();
        }
        tree.resize(k + 1, segment(m));
        tree[k - 1].update(a[l], 0);
        for (int i = l + 1; i <= n; ++i)
        {
            vector<int> dp(k - 1);
            for (int j = 0; j + 1 < k; ++j)
                dp[j] = tree[j + 1].query(1, a[i] - 1);
            for (int j = 0; j < k; ++j)
                tree[j].update(1, a[i] - 1, 1);
            for (int j = 0; j + 1 < k; ++j)
                tree[j].update(a[i], dp[j]);
        }
        int Lres = 0, Rres = tree[0].query(1, m);
        {
            for (int i = 1; i < l; ++i)
                Lres += (a[i] >= a[l]);
        }
        cout << (Lres + Rres > n ? -1 : Lres + Rres) << '\n';
    }
};
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    while (T--)
        Main();
    return 0;
}
