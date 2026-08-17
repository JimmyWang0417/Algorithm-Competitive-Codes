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
constexpr int inf = INT_MAX / 2;
struct segmentTree
{
    struct node
    {
        int l, r;
        int amin, amax;
        int bmin, bmax;
        int ans;
        int tagL, tagR;
        auto L(int x)
        {
            amin = x - 2 * r, amax = x - 2 * l;
            bmin = bmax = x;
            ans = x - l;
            tagL = x, tagR = 0;
        }
        auto R(int x)
        {
            amin = amax = -x;
            bmin = 2 * l - x, bmax = 2 * r - x;
            ans = r - x;
            tagL = 0, tagR = x;
        }
    };
    int n;
    vector<node> tree;
#define lc (rt << 1)
#define rc (rt << 1 | 1)
    auto pushup(int rt)
    {
        tree[rt].amin = min(tree[lc].amin, tree[rc].amin);
        tree[rt].amax = max(tree[lc].amax, tree[rc].amax);
        tree[rt].bmin = min(tree[lc].bmin, tree[rc].bmin);
        tree[rt].bmax = max(tree[lc].bmax, tree[rc].bmax);
        tree[rt].ans = max(tree[lc].ans, tree[rc].ans);
    }
    auto pushdown(int rt)
    {
        if (tree[rt].tagL)
        {
            tree[lc].L(tree[rt].tagL);
            tree[rc].L(tree[rt].tagL);
            tree[rt].tagL = 0;
        }
        if (tree[rt].tagR)
        {
            tree[lc].R(tree[rt].tagR);
            tree[rc].R(tree[rt].tagR);
            tree[rt].tagR = 0;
        }
    }
    auto build(int rt, int l, int r)
    {
        tree[rt].l = l, tree[rt].r = r;
        if (l == r)
        {
            tree[rt].amin = tree[rt].amax = inf - l;
            tree[rt].bmin = tree[rt].bmax = inf + l;
            tree[rt].ans = inf;
            return;
        }
        int mid = (l + r) >> 1;
        build(lc, l, mid);
        build(rc, mid + 1, r);
        pushup(rt);
    }
    auto updateL(int rt, int l, int r, int pos)
    {
        if (pos >= tree[rt].bmax)
            return;
        if (r <= pos && pos < tree[rt].bmin)
            return tree[rt].L(pos);
        int mid = (l + r) >> 1;
        pushdown(rt);
        updateL(lc, l, mid, pos);
        if (pos > mid)
            updateL(rc, mid + 1, r, pos);
        pushup(rt);
    }
    auto updateR(int rt, int l, int r, int pos)
    {
        if (-pos >= tree[rt].amax)
            return;
        if (pos <= l && -pos < tree[rt].amin)
            return tree[rt].R(pos);
        int mid = (l + r) >> 1;
        pushdown(rt);
        if (pos <= mid)
            updateR(lc, l, mid, pos);
        updateR(rc, mid + 1, r, pos);
        pushup(rt);
    }
    auto query(int rt, int l, int r, int x, int y)
    {
        if (r < x || l > y)
            return -inf;
        if (x <= l && r <= y)
            return tree[rt].ans;
        int mid = (l + r) >> 1;
        pushdown(rt);
        return max(query(lc, l, mid, x, y), query(rc, mid + 1, r, x, y));
    }
    auto updateL(int pos) { return updateL(1, 1, n, pos); }
    auto updateR(int pos) { return updateR(1, 1, n, pos); }
    auto query(int x, int y) { return query(1, 1, n, x, y); }
    segmentTree() = default;
    segmentTree(int _n) : n(_n), tree(n * 4) { build(1, 1, n); }
};
struct Main
{
    int n, q;
    Main()
    {
        cin >> n >> q;
        segmentTree tree(n);
        while (q--)
        {
            int opt, x, y;
            cin >> opt >> x >> y;
            if (opt == 1)
            {
                if (x == 0)
                    tree.updateL(y);
                else
                    tree.updateR(y);
            }
            else
            {
                int res = tree.query(x, y);
                if (res == inf)
                    res = -1;
                cout << res << '\n';
            }
        }
    }
};
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--)
        Main();
    return 0;
}

