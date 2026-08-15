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
struct SegmentTree
{
    struct node
    {
        int max;
        int size;
    };
    int n;
    vector<node> tree;
#define lc (rt << 1)
#define rc (rt << 1 | 1)
    auto pushup(int rt)
    {
        tree[rt].max = max(tree[lc].max, tree[rc].max);
        tree[rt].size = tree[lc].size + tree[rc].size;
    }
    auto build(int rt, int l, int r, const vector<int> &a) -> void
    {
        if (l == r)
        {
            tree[rt].max = a[l];
            tree[rt].size = a[l] != -1;
            return;
        }
        int mid = (l + r) >> 1;
        build(lc, l, mid, a);
        build(rc, mid + 1, r, a);
        pushup(rt);
    }
    auto queryL(int rt, int l, int r, int p, int v)
    {
        if (tree[rt].max <= v)
            return -1;
        if (l == r)
            return l;
        int mid = (l + r) / 2;
        if (p <= mid)
        {
            int res = queryL(lc, l, mid, p, v);
            if (res == -1)
                res = queryL(rc, mid + 1, r, p, v);
            return res;
        }
        else
            return queryL(rc, mid + 1, r, p, v);
    }
    auto queryR(int rt, int l, int r, int p, int v)
    {
        if (tree[rt].max <= v)
            return -1;
        if (l == r)
            return l;
        int mid = (l + r) / 2;
        if (p > mid)
        {
            int res = queryR(rc, mid + 1, r, p, v);
            if (res == -1)
                res = queryR(lc, l, mid, p, v);
            return res;
        }
        else
            return queryR(lc, l, mid, p, v);
    }
    auto update(int rt, int l, int r, int pos)
    {
        if (l == r)
        {
            tree[rt].max = -1;
            tree[rt].size = (tree[rt].max != -1);
            return;
        }
        int mid = (l + r) / 2;
        if (pos <= mid)
            update(lc, l, mid, pos);
        else
            update(rc, mid + 1, r, pos);
        pushup(rt);
    }
    auto kth(int rt, int l, int r, int v)
    {
        if (l == r)
            return l;
        int mid = (l + r) / 2;
        if (tree[lc].size >= v)
            return kth(lc, l, mid, v);
        else
            return kth(rc, mid + 1, r, v - tree[lc].size);
    }
    auto build(const vector<int> &a) { build(1, 1, n, a); }
    auto queryL(int p, int v) { return queryL(1, 1, n, p, v); }
    auto queryR(int p, int v) { return queryR(1, 1, n, p, v); }
    auto update(int pos) { update(1, 1, n, pos); }
    auto kth(int v) { return kth(1, 1, n, v); }
    auto all() { return tree[1].size; }
    SegmentTree() = default;
    SegmentTree(int _n) : n(_n), tree(_n * 4) {}
};
struct Main
{
    int n, q;
    vector<int> a;
    vector<vector<pair<int, int>>> G;
    Main()
    {
        cin >> n >> q;
        a.resize(n + 5);
        for (int i = 1; i <= n; ++i)
            cin >> a[i];
        G.resize(n + 5);
        vector<int> answer(q);
        for (int i = 0; i < q; ++i)
        {
            int x, y;
            cin >> x >> y;
            if (x <= n)
                G[x].emplace_back(y, i);
            else
                answer[i] = -1;
        }
        int circle = 0;
        SegmentTree tree(n);
        tree.build(a);
        vector<int> L, R;
        int up = n;
        for (int i = 1; i <= n; ++i)
        {
            ++circle;
            if (i & 1)
            {
                {
                    int p = 0, v = L.empty() ? 0 : L.back();
                    while (true)
                    {
                        int w = tree.queryL(p + 1, v);
                        if (w == -1)
                            break;
                        p = w, v = a[w];
                        tree.update(p);
                        L.push_back(v);
                        // cout << "FUCK" << p << ' ' << v << '\n';
                    }
                }
                while (!L.empty() && L.back() == up)
                {
                    L.pop_back();
                    up--;
                }
                for (auto [u, id] : G[i])
                {
                    int &res = answer[id], v = u;
                    if (v <= (int)R.size())
                        res = R[(int)R.size() - v];
                    else
                    {
                        v -= (int)R.size();
                        if (v <= tree.all())
                            res = a[tree.kth(tree.all() - v + 1)];
                        else
                        {
                            v -= tree.all();
                            if (v <= (int)L.size())
                                res = L[v - 1];
                            else
                                res = u;
                        }
                    }
                }
            }
            else
            {
                {
                    int p = n + 1, v = R.empty() ? 0 : R.back();
                    while (true)
                    {
                        int w = tree.queryR(p - 1, v);
                        if (w == -1)
                            break;
                        p = w, v = a[w];
                        tree.update(p);
                        R.push_back(v);
                        // cout << p << ' ' << v << '\n';
                    }
                }
                while (!R.empty() && R.back() == up)
                {
                    R.pop_back();
                    up--;
                }
                for (auto [u, id] : G[i])
                {
                    int &res = answer[id], v = u;
                    if (v <= (int)L.size())
                        res = L[(int)L.size() - v];
                    else
                    {
                        v -= (int)L.size();
                        if (v <= tree.all())
                            res = a[tree.kth(v)];
                        else
                        {
                            v -= tree.all();
                            if (v <= (int)R.size())
                                res = R[v - 1];
                            else
                                res = u;
                        }
                    }
                }
            }
            if (up == 0)
                break;
        }
        {
            tree.build(a);
            L.clear(), R.clear();
            up = n;
            for (int i = 1; i < circle; ++i)
            {
                if (i & 1)
                {
                    {
                        int p = 0, v = L.empty() ? 0 : L.back();
                        while (true)
                        {
                            int w = tree.queryL(p + 1, v);
                            if (w == -1)
                                break;
                            p = w, v = a[w];
                            tree.update(p);
                            L.push_back(v);
                        }
                    }
                    while (!L.empty() && L.back() == up)
                    {
                        L.pop_back();
                        up--;
                    }
                }
                else
                {
                    {
                        int p = n + 1, v = R.empty() ? 0 : R.back();
                        while (true)
                        {
                            int w = tree.queryR(p - 1, v);
                            if (w == -1)
                                break;
                            p = w, v = a[w];
                            tree.update(p);
                            R.push_back(v);
                        }
                    }
                    while (!R.empty() && R.back() == up)
                    {
                        R.pop_back();
                        up--;
                    }
                }
            }
            vector<int> p;
            if ((circle - 1) & 1)
            {
                for (int j : views::reverse(R))
                    p.push_back(j);
                for (int j = tree.all(); j >= 1; --j)
                    p.push_back(a[tree.kth(j)]);
                for (int j : L)
                    p.push_back(j);
                for (int j = up + 1; j <= n; ++j)
                    p.push_back(j);
            }
            else
            {
                for (int j : views::reverse(L))
                    p.push_back(j);
                for (int j = 1; j <= tree.all(); ++j)
                    p.push_back(a[tree.kth(j)]);
                for (int j : R)
                    p.push_back(j);
                for (int j = up + 1; j <= n; ++j)
                    p.push_back(j);
            }
            bool flag = true;
            for (int i = 0; i < n; ++i)
            {
                if (i + 1 != p[i])
                {
                    flag = false;
                    break;
                }
            }
            if (flag)
                --circle;
        }
        for (auto [v, id] : G[0])
            answer[id] = a[v];
        for (int i = circle + 1; i <= n; ++i)
            for (auto [v, id] : G[i])
                answer[id] = -1;
        for (int i : answer)
            cout << i << '\n';
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

