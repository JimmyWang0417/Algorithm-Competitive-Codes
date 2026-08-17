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
struct segment
{
    struct info
    {
        int tag, max;
        auto update(int v)
        {
            max += v;
            tag += v;
        }
    };
    int n;
    vector<info> tree;
    segment() = default;
    segment(int _n) : n(_n), tree((_n + 5) * 4) {}
#define lc (rt << 1)
#define rc (rt << 1 | 1)
    auto pushup(int rt)
    {
        tree[rt].max = max(tree[lc].max, tree[rc].max);
    }
    auto pushdown(int rt)
    {
        if (tree[rt].tag)
        {
            tree[lc].update(tree[rt].tag);
            tree[rc].update(tree[rt].tag);
            tree[rt].tag = 0;
        }
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
    auto query(int rt, int l, int r, int x, int y)
    {
        if (r < x || l > y)
            return INT_MIN;
        if (x <= l && r <= y)
            return tree[rt].max;
        int mid = (l + r) >> 1;
        pushdown(rt);
        return max(query(lc, l, mid, x, y), query(rc, mid + 1, r, x, y));
    }
    auto update(int x, int y, int v) { return update(1, 0, n, x, y, v); }
    auto query(int x, int y) { return query(1, 0, n, x, y); }
};
struct Main
{
    int n, m, L, q;
    vector<int> p;
    Main()
    {
        cin >> n >> L >> q;
        m = n * 4;
        p.resize(n);
        vector<bool> have(2 * n + 5);
        for (int &i : p)
        {
            cin >> i;
            have[i] = true;
        }
        sort(p.begin(), p.end());
        vector<int> cnt(m + 5);
        for (int i : p)
            ++cnt[i], --cnt[i + L];
        for (int i = 1; i <= m; ++i)
            cnt[i] += cnt[i - 1];
        vector<int> prefixq(m + 5), prefixq1(m + 5) /* (k - 1)*/, prefixq2(m + 5) /* (k + 1)*/;
        for (int i = 0; i <= m; ++i)
            prefixq[i] = (i > 0 ? prefixq[i - 1] : 0) + (cnt[i] == q);
        for (int i = 0; i <= m; ++i)
            prefixq1[i] = (i > 0 ? prefixq1[i - 1] : 0) + (cnt[i] == q - 1);
        for (int i = 0; i <= m; ++i)
            prefixq2[i] = (i > 0 ? prefixq2[i - 1] : 0) + (cnt[i] == q + 1);
        auto initialans = prefixq[m];
        vector<int> pre(3 * n + 5), suf(3 * n + 5);
        auto calc = [](auto &prefix, int l, int r)
        {
            auto res = prefix[r];
            if (l > 0)
                res -= prefix[l - 1];
            return res;
        };
        for (int i = 0; i <= 3 * n; ++i)
        {
            pre[i] = -calc(prefixq, i, i + L - 1) + calc(prefixq1, i, i + L - 1);
            suf[i] = -calc(prefixq, i, i + L - 1) + calc(prefixq1, i, i + L - 1);
        }
        for (int i = 1; i <= 3 * n; ++i)
            pre[i] = max(pre[i - 1], pre[i]);
        for (int i = 3 * n; i >= 1; --i)
            suf[i - 1] = max(suf[i - 1], suf[i]);
        int res = 0;
        for (int i = 0; i <= 2 * n; ++i)
            if (have[i])
            {
                if (i - L >= 0)
                    res = max(res, -calc(prefixq, i, i + L - 1) + calc(prefixq2, i, i + L - 1) + pre[i - L]);
                res = max(res, -calc(prefixq, i, i + L - 1) + calc(prefixq2, i, i + L - 1) + suf[i + L]);
            }
        segment tree(m);
        for (int i = 1; i <= 3 * n; ++i)
        {
            tree.update(0, i - 1, +(cnt[i - 1] == q - 1) - (cnt[i - 1] == q));
            tree.update(0, i - 1, +(cnt[i + L - 1] == q + 1) - (cnt[i + L - 1] == q));
            if (have[i])
                res = max(res, tree.query(i - L + 1, i - 1));
        }
        tree = segment(m);
        for (int i = 3 * n - 1; i >= 0; --i)
        {
            tree.update(i + 1, 3 * n, +(cnt[i] == q + 1) - (cnt[i] == q));
            tree.update(i + 1, 3 * n, +(cnt[i + L] == q - 1) - (cnt[i + L] == q));
            if (have[i])
                res = max(res, tree.query(i + 1, i + L - 1));
        }
        cout << initialans + res << '\n';
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
