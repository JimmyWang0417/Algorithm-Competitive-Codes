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
constexpr int mod = 1e9 + 7;
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
    string s;
    struct node
    {
        int sze[2];
        int tag;
        auto update(int v)
        {
            sze[v] = sze[0] + sze[1];
            sze[v ^ 1] = 0;
            tag = v;
        }
    };
    vector<node> tree;
#define lc (rt << 1)
#define rc (rt << 1 | 1)
    auto pushup(int rt)
    {
        for (int i = 0; i < 2; ++i)
            tree[rt].sze[i] = tree[lc].sze[i] + tree[rc].sze[i];
    }
    auto pushdown(int rt)
    {
        if (tree[rt].tag != -1)
        {
            tree[lc].update(tree[rt].tag);
            tree[rc].update(tree[rt].tag);
            tree[rt].tag = -1;
        }
    }
    auto build(int rt, int l, int r)
    {
        tree[rt].tag = -1;
        if (l == r)
        {
            tree[rt].sze[s[l - 1] == 'N'] = 1;
            return;
        }
        int mid = (l + r) >> 1;
        build(lc, l, mid);
        build(rc, mid + 1, r);
        pushup(rt);
    }
    auto update(int rt, int l, int r, int x, int y, int v)
    {
        if (r < x || l > y)
            return;
        if (x <= l && r <= y)
            return tree[rt].update(v);
        int mid = (l + r) >> 1;
        pushdown(rt);
        update(lc, l, mid, x, y, v);
        update(rc, mid + 1, r, x, y, v);
        pushup(rt);
    }
    auto queryL(int rt, int l, int r, int p, int v)
    {
        if (r <= p && !tree[rt].sze[v])
            return l - 1;
        if (l == r)
            return !tree[rt].sze[v] ? l - 1 : l;
        int mid = (l + r) >> 1;
        pushdown(rt);
        if (p <= mid)
            return queryL(lc, l, mid, p, v);
        else
        {
            int res = queryL(rc, mid + 1, r, p, v);
            if (res == mid)
                res = queryL(lc, l, mid, p, v);
            return res;
        }
    }
    auto queryR(int rt, int l, int r, int p, int v)
    {
        if (p <= l && !tree[rt].sze[v])
            return r + 1;
        if (l == r)
            return !tree[rt].sze[v] ? r + 1 : r;
        int mid = (l + r) >> 1;
        pushdown(rt);
        if (p <= mid)
        {
            int res = queryR(lc, l, mid, p, v);
            if (res == mid + 1)
                res = queryR(rc, mid + 1, r, p, v);
            return res;
        }
        else
            return queryR(rc, mid + 1, r, p, v);
    }
    auto addL(int p, i64 k)
    {
        for (int i = 0; i < 60 && p - i >= 1; ++i)
            if ((k >> i) & 1)
            {
                int q = queryL(1, 1, n, p - i, 0);
                update(1, 1, n, q, q, 1);
                update(1, 1, n, q + 1, p - i, 0);
            }
    }
    auto subL(int p, i64 k)
    {
        for (int i = 0; i < 60 && p - i >= 1; ++i)
            if ((k >> i) & 1)
            {
                int q = queryL(1, 1, n, p - i, 1);
                update(1, 1, n, q, q, 0);
                update(1, 1, n, q + 1, p - i, 1);
            }
    }
    auto addR(int p, i64 k)
    {
        for (int i = 0; i < 60 && p + i <= n; ++i)
            if ((k >> i) & 1)
            {
                int q = queryR(1, 1, n, p + i, 0);
                update(1, 1, n, q, q, 1);
                update(1, 1, n, p + i, q - 1, 0);
            }
    }
    auto subR(int p, i64 k)
    {
        for (int i = 0; i < 60 && p + i <= n; ++i)
            if ((k >> i) & 1)
            {
                int q = queryR(1, 1, n, p + i, 1);
                update(1, 1, n, q, q, 0);
                update(1, 1, n, p + i, q - 1, 1);
            }
    }
    auto query(int rt, int l, int r, string &ans)
    {
        if (l == r)
        {
            ans.push_back(tree[rt].sze[0] ? 'H' : 'N');
            return;
        }
        int mid = (l + r) >> 1;
        pushdown(rt);
        query(lc, l, mid, ans);
        query(rc, mid + 1, r, ans);
    }
    Main()
    {
        cin >> n >> m >> s;
        tree.resize(4 * n);
        build(1, 1, n);
        while (m--)
        {
            int o, p;
            i64 k;
            cin >> o >> p >> k;
            if (o == 1)
                subR(p, k);
            else if (o == 2)
                addR(p, k);
            else if (o == 3)
                subL(p, k);
            else
                addL(p, k);
        }
        string ans;
        query(1, 1, n, ans);
        cout << ans << '\n';
    }
};
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--)
        Main();
    return 0;
}

