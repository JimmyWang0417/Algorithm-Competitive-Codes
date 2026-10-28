#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>
using namespace std;
typedef int64_t i64;
typedef uint64_t u64;
typedef __int128_t i128;
typedef __uint128_t u128;
typedef __float80 f80;
typedef __float128 f128;
constexpr int mod = 998244353;
template <typename T = int>
constexpr auto quickpow(i64 a, T b = mod - 2)
{
    i64 res = 1;
    while (b)
    {
        if (b & 1)
            (res *= a) %= mod;
        (a *= a) %= mod;
        b >>= 1;
    }
    return res;
}
struct Main
{
    int n, m;
    struct node : array<tuple<int, i64, i64>, 26>
    {
        auto friend operator+(const node &lhs, const node &rhs)
        {
            node res = lhs;
            for (int i = 0, s = 0; i < 26; ++i)
            {
                s += get<0>(lhs[i]);
                auto [x, y, z] = rhs[i];
                get<0>(res[i]) += x;
                get<1>(res[i]) += y + (i64)x * s;
                get<2>(res[i]) += z + y * s + (i64)x * s * (s + 1) / 2;
            }
            return res;
        }
    };
    struct Tree
    {
        node val;
        int sze;
        bool tag;
        auto modify()
        {
            tag = true;
            for (int i = 0, s = 0; i < 26; ++i)
            {
                auto x = get<0>(val[i]);
                get<1>(val[i]) = (i64)(x + s) * (x + s - 1) / 2 -
                                 (i64)s * (s - 1) / 2;
                get<2>(val[i]) = (i64)(x + s + 1) * (x + s) * (x + s - 1) / 6 -
                                 (i64)(s + 1) * s * (s - 1) / 6;
                s += x;
            }
        }
        auto update(int v)
        {
            val = {};
            val[v] = {sze,
                      (i64)sze * (sze - 1) / 2,
                      (i64)(sze + 1) * sze * (sze - 1) / 6};
        }
    };
    vector<Tree> tree;
    string s;
#define lc (rt << 1)
#define rc (rt << 1 | 1)
    auto pushup(int rt)
    {
        tree[rt].val = tree[lc].val + tree[rc].val;
    }
    auto pushdown(int rt)
    {
        if (tree[rt].tag)
        {
            {
                auto res = tree[rt].val;
                int rem = tree[lc].sze;
                for (int i = 0; i < 26; ++i)
                {
                    int v = min(get<0>(res[i]), rem);
                    get<0>(res[i]) -= v, rem -= v;
                    get<0>(tree[lc].val[i]) = v;
                }
                tree[rc].val = res;
            }
            tree[lc].modify();
            tree[rc].modify();
            tree[rt].tag = false;
        }
    }
    auto build(int rt, int l, int r) -> void
    {
        tree[rt].sze = r - l + 1;
        if (l == r)
        {
            tree[rt].update(s[l - 1] - 'A');
            return;
        }
        int mid = (l + r) >> 1;
        pushdown(rt);
        build(lc, l, mid);
        build(rc, mid + 1, r);
        pushup(rt);
    }
    auto update(int rt, int l, int r, int pos, int val) -> void
    {
        if (l == r)
        {
            tree[rt].update(val);
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
    auto modify(int rt, int l, int r, int x, int y, array<tuple<int, i64, i64>, 26> &cur) -> void
    {
        if (r < x || l > y)
            return;
        if (x <= l && r <= y)
        {
            for (int i = 0, rem = tree[rt].sze; i < 26; ++i)
            {
                int v = min(get<0>(cur[i]), rem);
                get<0>(cur[i]) -= v, rem -= v;
                get<0>(tree[rt].val[i]) = v;
            }
            return tree[rt].modify();
        }
        int mid = (l + r) >> 1;
        pushdown(rt);
        modify(lc, l, mid, x, y, cur);
        modify(rc, mid + 1, r, x, y, cur);
        pushup(rt);
    }
    auto query(int rt, int l, int r, int x, int y) -> node
    {
        if (r < x || l > y)
            return {};
        if (x <= l && r <= y)
            return tree[rt].val;
        int mid = (l + r) >> 1;
        pushdown(rt);
        return query(lc, l, mid, x, y) + query(rc, mid + 1, r, x, y);
    }
    Main()
    {
        cin >> n >> m;
        cin >> s;
        tree.resize(4 * n + 5);
        build(1, 1, n);
        while (m--)
        {
            int o, p, q;
            char c;
            cin >> o >> p;
            if (o == 1)
            {
                cin >> c;
                update(1, 1, n, p, c - 'A');
            }
            else
            {
                cin >> q;
                i64 res = (i64)(q - p + 2) * (q - p + 1) * (q - p) / 6;
                auto cur = query(1, 1, n, p, q);
                for (int i = 0; i < 26; ++i)
                    res -= get<2>(cur[i]);
                cout << res << '\n';
                if (o == 3)
                    modify(1, 1, n, p, q, cur);
            }
        }
    }
};
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    cin >> T;
    while (T--)
        Main();
    return 0;
}
