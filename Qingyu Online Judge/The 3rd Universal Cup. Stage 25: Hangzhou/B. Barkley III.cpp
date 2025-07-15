#include <bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
constexpr int N = 1e6 + 5;
int n, m;
ull a[N];
struct Tree
{
    int size;
    ull tag;
    ull f, g;
    inline void update(ull val)
    {
        tag &= val;
        if (size > 1)
            f &= val;
        g &= val;
    }
} tree[N * 4];
#define lc (rt << 1)
#define rc (rt << 1 | 1)
inline void pushdown(int rt)
{
    if (tree[rt].tag != ULONG_LONG_MAX)
    {
        tree[lc].update(tree[rt].tag);
        tree[rc].update(tree[rt].tag);
        tree[rt].tag = ULONG_LONG_MAX;
    }
}
inline void pushup(int rt)
{
    tree[rt].f = (tree[lc].f & tree[rc].g) | (tree[lc].g & tree[rc].f);
    tree[rt].g = tree[lc].g & tree[rc].g;
}
inline void build(int rt, int l, int r)
{
    tree[rt].size = r - l + 1;
    tree[rt].tag = ULONG_LONG_MAX;
    if (l == r)
    {
        tree[rt].f = ULONG_LONG_MAX;
        tree[rt].g = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
    pushup(rt);
}
inline void update(int rt, int l, int r, int pos, ull val)
{
    if (l == r)
    {
        tree[rt].g = val;
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
inline void update(int rt, int l, int r, int x, int y, ull val)
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
inline pair<ull, ull> query(int rt, int l, int r, int x, int y)
{
    if (r < x || l > y)
        return make_pair(ULONG_LONG_MAX, ULONG_LONG_MAX);
    if (x <= l && r <= y)
        return make_pair(tree[rt].f, tree[rt].g);
    int mid = (l + r) >> 1;
    pushdown(rt);
    auto L = query(lc, l, mid, x, y), R = query(rc, mid + 1, r, x, y);
    return make_pair((L.first & R.second) | (L.second & R.first), L.second & R.second);
}
inline pair<int, bool> query(int rt, int l, int r, int x, int y, ull val)
{
    if (l == r)
        return make_pair(l, (tree[rt].g & val) == val);
    int mid = (l + r) >> 1;
    pushdown(rt);
    if (y <= mid)
        return query(lc, l, mid, x, y, val);
    if (x > mid)
        return query(rc, mid + 1, r, x, y, val);
    if (x <= l && r <= y)
    {
        if ((tree[rt].g & val) == val)
            return make_pair(0, 1);
        if ((tree[rc].g & val) == val)
            return query(lc, l, mid, x, y, val);
        else
            return query(rc, mid + 1, r, x, y, val);
    }
    auto L = query(lc, l, mid, x, y, val), R = query(rc, mid + 1, r, x, y, val);
    if (R.second)
        return L;
    else
        return R;
}
inline void _main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    build(1, 1, n);
    while (m--)
    {
        int opt;
        cin >> opt;
        if (opt == 1)
        {
            int l, r;
            ull x;
            cin >> l >> r >> x;
            update(1, 1, n, l, r, x);
        }
        else if (opt == 2)
        {
            int pos;
            ull val;
            cin >> pos >> val;
            update(1, 1, n, pos, val);
        }
        else
        {
            int l, r;
            cin >> l >> r;
            auto [f, g] = query(1, 1, n, l, r);
            auto ans = f ^ g;
            if (!ans)
                cout << f << '\n';
            else
            {
                int where = (int)__lg(ans);
                ans = (ans & ~((1ull << where) - 1)) | (1ull << where);
                int pos = query(1, 1, n, l, r, ans).first;
                ull res = ULONG_LONG_MAX;
                if (l < pos)
                    res = res & query(1, 1, n, l, pos - 1).second;
                if (pos < r)
                    res = res & query(1, 1, n, pos + 1, r).second;
                cout << res << '\n';
            }
        }
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--)
        _main();
    return 0;
}