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
constexpr double eps = 1e-7;
struct segment
{
    struct info
    {
        i64 sum;
        bool tag;
        auto update()
        {
            sum = -sum;
            tag ^= 1;
        }
    };
    vector<info> tree;
    int n;
    segment() = default;
    segment(int _n) : tree((_n + 5) * 4), n(_n) {}
#define lc (rt << 1)
#define rc (rt << 1 | 1)
    auto pushup(int rt)
    {
        tree[rt].sum = tree[lc].sum + tree[rc].sum;
    }
    auto pushdown(int rt)
    {
        if (tree[rt].tag)
        {
            tree[lc].update();
            tree[rc].update();
            tree[rt].tag = false;
        }
    }
    auto build(int rt, int l, int r, const vector<int> &v)
    {
        if (l == r)
        {
            tree[rt].sum = v[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(lc, l, mid, v);
        build(rc, mid + 1, r, v);
        pushup(rt);
    }
    auto update(int rt, int l, int r, int x, int y)
    {
        if (r < x || l > y)
            return;
        if (x <= l && r <= y)
            return tree[rt].update();
        int mid = (l + r) >> 1;
        pushdown(rt);
        update(lc, l, mid, x, y);
        update(rc, mid + 1, r, x, y);
        pushup(rt);
    }
    auto query(int rt, int l, int r, int x, int y) -> i64
    {
        if (r < x || l > y)
            return 0;
        if (x <= l && r <= y)
            return tree[rt].sum;
        int mid = (l + r) >> 1;
        pushdown(rt);
        return query(lc, l, mid, x, y) + query(rc, mid + 1, r, x, y);
    }
    auto update(int x, int y) { return update(1, 1, n, x, y); }
    auto query(int x, int y) { return query(1, 1, n, x, y); }
};
struct Main
{
    int m, n, q;
    Main()
    {
        cin >> m >> n >> q;
        map<string, pair<int, int>> mp;
        while (m--)
        {
            int p, v;
            string s;
            cin >> p >> v >> s;
            mp[s] = make_pair(p, v);
        }
        vector<int> p(n + 5), v(n + 5);
        vector<i64> answer(q);
        for (int i = 1; i <= n; ++i)
        {
            string s;
            cin >> s;
            tie(p[i], v[i]) = mp[s];
        }
        segment tree(n);
        tree.build(1, 1, n, v);
        vector<vector<pair<int, int>>> g(n + 5);
        for (int i = 0; i < q; ++i)
        {
            int l, r;
            cin >> l >> r;
            g[r].emplace_back(l, i);
        }
        p[0] = 2e9;
        stack<int> st({0});
        for (int r = 1; r <= n; ++r)
        {
            while (!st.empty() && p[st.top()] < p[r])
                st.pop();
            tree.update(st.top() + 1, r - 1);
            for (auto [l, id] : g[r])
                answer[id] = tree.query(l, r);
            st.push(r);
        }
        for (auto i : answer)
            cout << i << '\n';
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

