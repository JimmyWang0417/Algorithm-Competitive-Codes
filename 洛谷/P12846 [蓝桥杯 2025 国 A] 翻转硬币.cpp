#include <bits/stdc++.h>
#include <cassert>
using namespace std;
typedef int64_t i64;
typedef uint64_t u64;
typedef __int128_t i128;
typedef __uint128_t u128;
typedef __float80 f80;
typedef __float128 f128;
constexpr int mod = 998244353;
struct SegmentTree
{
    struct node
    {
        int sze;
        int cnt[2];
        bool rev;
        auto reverse()
        {
            swap(cnt[0], cnt[1]);
            rev ^= 1;
        }
    };
    int n;
    vector<bool> a;
    vector<node> tree;
#define lc (rt << 1)
#define rc (rt << 1 | 1)
    auto pushup(int rt)
    {
        tree[rt].cnt[0] = tree[lc].cnt[0] + tree[rc].cnt[0];
        tree[rt].cnt[1] = tree[lc].cnt[1] + tree[rc].cnt[1];
    }
    auto pushdown(int rt)
    {
        if (tree[rt].rev)
        {
            tree[lc].reverse();
            tree[rc].reverse();
            tree[rt].rev = false;
        }
    }
    auto build(int rt, int l, int r) -> void
    {
        if (l == r)
        {
            tree[rt].cnt[a[l]] = 1;
            tree[rt].cnt[a[l] ^ 1] = 0;
            return;
        }
        int mid = (l + r) >> 1;
        build(lc, l, mid);
        build(rc, mid + 1, r);
        pushup(rt);
    }
    auto update(int rt, int l, int r, int x, int y) -> void
    {
        if (r < x || l > y)
            return;
        if (x <= l && r <= y)
            return tree[rt].reverse();
        int mid = (l + r) >> 1;
        pushdown(rt);
        update(lc, l, mid, x, y);
        update(rc, mid + 1, r, x, y);
        pushup(rt);
    }
    auto query(int rt, int l, int r, int x, int y) -> int
    {
        if (r < x || l > y)
            return 0;
        if (x <= l && r <= y)
            return tree[rt].cnt[1];
        int mid = (l + r) >> 1;
        pushdown(rt);
        return query(lc, l, mid, x, y) + query(rc, mid + 1, r, x, y);
    }
    auto update(int x, int y)
    {
        if (!n || x > y)
            return;
        return update(1, 0, n - 1, x, y);
    }
    auto query(int x, int y)
    {
        if (!n || x > y)
            return 0;
        return query(1, 0, n - 1, x, y);
    }
    SegmentTree() = default;
    SegmentTree(const vector<bool> &_a) : n((int)_a.size()), a(_a), tree(4 * n)
    {
        if (!n)
            return;
        build(1, 0, n - 1);
    }
};
struct Main
{
    int n, m;
    vector<bool> f;
    SegmentTree tree[6];
    Main()
    {
        cin >> n >> m;
        f.resize(n);
        for (int i = 0; i < n; ++i)
        {
            int x;
            cin >> x;
            f[i] = x;
        }
        {
            vector<bool> g[6];
            for (int i = 0; i < n; ++i)
                g[i % 6].push_back(f[i]);
            for (int i = 0; i < 6; ++i)
                tree[i] = SegmentTree(g[i]);
        }
        while (m--)
        {
            int opt, l, r;
            cin >> opt >> l >> r;
            --l, --r;
            auto L = [](int x, int y)
            {
                if (x % 6 <= y)
                    return x / 6;
                else
                    return x / 6 + 1;
            };
            auto R = [](int x, int y)
            {
                if (x % 6 >= y)
                    return x / 6;
                else
                    return x / 6 - 1;
            };
            if (opt == 1)
            {
                for (int i = 0; i < 6; ++i)
                {
                    if ((l - i) % 2)
                        continue;
                    tree[i].update(L(l, i), R(r, i));
                }
            }
            else if (opt == 2)
            {
                for (int i = 0; i < 6; ++i)
                {
                    if ((l - i) % 3)
                        continue;
                    tree[i].update(L(l, i), R(r, i));
                }
            }
            else if (opt == 3)
            {
                for (int i = 0; i < 6; ++i)
                    tree[i].update(L(l, i), R(r, i));
            }
            else
            {
                int res = 0;
                for (int i = 0; i < 6; ++i)
                    res += tree[i].query(L(l, i), R(r, i));
                cout << res << '\n';
            }
        }
    }
};
signed main()
{
    // freopen("project.in", "r", stdin);
    // freopen("project.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--)
        Main();
    return 0;
}