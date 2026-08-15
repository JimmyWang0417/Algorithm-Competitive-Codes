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
struct segmentTree
{
    struct node
    {
        i64 k, b;
        node(i64 _k = 0, i64 _b = LLONG_MIN) : k(_k), b(_b) {}
        auto calc(i64 x) { return k * x + b; }
    };
    vector<i64> p;
    vector<node> tree;
#define lc (rt << 1)
#define rc (rt << 1 | 1)
    auto update(int rt, int l, int r, int x, int y, node val)
    {
        if (r < x || l > y)
            return;
        int mid = (l + r) >> 1;
        if (x <= l && r <= y)
        {
            // cout << rt << ' ' << l << ' ' << r << ' ' << x << ' ' << y << ' ' << val.k << ' ' << val.b << '\n';
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
    auto query(int rt, int l, int r, int pos)
    {
        // cout << rt << ' ' << pos << ' ' << p[pos] << ' ' << tree[rt].calc(p[pos]) << '\n';
        if (l == r)
            return tree[rt].calc(p[pos]);
        int mid = (l + r) >> 1;
        return max(tree[rt].calc(p[pos]),
                   pos <= mid ? query(lc, l, mid, pos) : query(rc, mid + 1, r, pos));
    }
    auto update(node val) { update(1, 0, (int)p.size() - 1, 0, (int)p.size() - 1, val); }
    auto query(i64 val)
    {
        int pos = (int)(lower_bound(p.begin(), p.end(), val) - p.begin());
        return query(1, 0, (int)p.size() - 1, pos);
    }
    segmentTree() = default;
    segmentTree(const vector<i64> &_p) : p(_p)
    {
        sort(p.begin(), p.end());
        p.erase(unique(p.begin(), p.end()), p.end());
        tree.resize(p.size() * 4);
    }
};
struct Main
{
    int n;
    vector<int> a;
    vector<i64> b, c;
    Main()
    {
        cin >> n;
        a.resize(n + 5);
        b.resize(n + 5);
        c.resize(n + 5);
        for (int i = 1; i <= n; ++i)
        {
            cin >> a[i];
            b[i] = b[i - 1] + a[i];
            c[i] = c[i - 1] + (i64)i * a[i];
        }
        vector<i64> p, q;
        for (int i = 1; i <= n; ++i)
        {
            p.emplace_back(-2 * b[i] + a[i] - a[i + 1]);
            q.emplace_back(i);
        }
        vector<i64> dp0(n + 1), dp1(n + 1);
        segmentTree tree0(p), tree1(q);
        dp0[1] = a[1], dp1[1] = a[1];
        auto update = [&](int p)
        {
            tree0.update(segmentTree::node(p,
                                           dp0[p] - 2 * c[p] + b[p] * (2 * p - 3) + 2 * a[p]));
            tree1.update(segmentTree::node(-2 * b[p] + a[p] + a[p - 1],
                                           dp1[p] - 3 * b[p] + 2 * c[p] - (i64)p * (a[p] + a[p - 1])));
        };
        for (int i = 2; i <= n; ++i)
        {
            update(i - 1);
            dp0[i] = tree1.query(i) +
                     (b[i] * (2 * i + 3) - 2 * c[i]);
            dp1[i] = tree0.query(-2 * b[i] + a[i] - a[i + 1]) +
                     (3 * b[i] - (i64)(i + 2) * a[i] + (i64)i * a[i + 1] + 2 * c[i]);
        }
        cout << max(dp0[n], dp1[n]) << '\n';
    }
};
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    cin >> T;
    while (T--)
        Main();
    return 0;
}

