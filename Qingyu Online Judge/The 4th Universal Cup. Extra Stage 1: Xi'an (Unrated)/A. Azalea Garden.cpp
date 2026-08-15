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
        int size;
        int cnt, len;
    };
#define lc (rt << 1)
#define rc (rt << 1 | 1)
    vector<info> tree;
    int n;
    segment() = default;
    segment(int _n) : n(_n)
    {
        tree.resize((n + 5) * 4);
        build(1, 1, n);
    }
    auto pushup(int rt)
    {
        if (tree[rt].cnt)
            tree[rt].len = tree[rt].size;
        else
            tree[rt].len = tree[lc].len + tree[rc].len;
    }
    auto build(int rt, int l, int r) -> void
    {
        tree[rt].size = r - l + 1;
        if (l == r)
            return;
        int mid = (l + r) >> 1;
        build(lc, l, mid);
        build(rc, mid + 1, r);
    }
    auto update(int rt, int l, int r, int x, int y, int v)
    {
        if (r < x || l > y)
            return;
        if (x <= l && r <= y)
        {
            tree[rt].cnt += v;
            if (l == r)
            {
                if (tree[rt].cnt)
                    tree[rt].len = tree[rt].size;
                else
                    tree[rt].len = 0;
            }
            else
                pushup(rt);
            return;
        }
        int mid = (l + r) >> 1;
        update(lc, l, mid, x, y, v);
        update(rc, mid + 1, r, x, y, v);
        pushup(rt);
    }
    auto query(int rt, int l, int r, int pos)
    {
        if (tree[rt].len == tree[rt].size)
            return l;
        if (l == r)
            return l + 1;
        int mid = (l + r) >> 1;
        if (pos <= mid)
            return query(lc, l, mid, pos);
        else
        {
            int res = query(rc, mid + 1, r, pos);
            return res == mid + 1 ? query(lc, l, mid, pos) : res;
        }
    }
    auto update(int l, int r, int v) { return update(1, 1, n, l, r, v); }
    auto query(int pos) { return query(1, 1, n, pos); }
};
struct othersegment
{
#define lc (rt << 1)
#define rc (rt << 1 | 1)
    struct info
    {
        int max, cnt;
        info() = default;
        info(int _max, int _cnt) : max(_max), cnt(_cnt) {}
        auto friend operator+(const info &lhs, const info &rhs)
        {
            return info(::max(lhs.max, rhs.max), lhs.cnt + rhs.cnt);
        }
    };
    vector<multiset<int>> se;
    vector<info> tree;
    int n;
    othersegment() = default;
    othersegment(int _n) : se(_n + 5), tree((_n + 5) * 4, info(INT_MIN, 0)), n(_n) {}
    auto pushup(int rt)
    {
        tree[rt] = tree[lc] + tree[rc];
    }
    auto add(int rt, int l, int r, int x, int y)
    {
        if (l == r)
        {
            se[l].insert(y);
            tree[rt] = info(se[l].empty() ? INT_MIN : *se[l].rbegin(),
                            (int)se[l].size());
            return;
        }
        int mid = (l + r) >> 1;
        if (x <= mid)
            add(lc, l, mid, x, y);
        else
            add(rc, mid + 1, r, x, y);
        pushup(rt);
    }
    auto del(int rt, int l, int r, int x, int y)
    {
        if (l == r)
        {
            se[l].erase(se[l].find(y));
            tree[rt] = info(se[l].empty() ? INT_MIN : *se[l].rbegin(),
                            (int)se[l].size());
            return;
        }
        int mid = (l + r) >> 1;
        if (x <= mid)
            del(lc, l, mid, x, y);
        else
            del(rc, mid + 1, r, x, y);
        pushup(rt);
    }
    auto query(int rt, int l, int r, int pos)
    {
        if (l == r)
            return tree[rt];
        int mid = (l + r) >> 1;
        if (pos <= mid)
            return query(lc, l, mid, pos) + tree[rc];
        else
            return query(rc, mid + 1, r, pos);
    }
    auto add(int x, int y) { add(1, 1, n, x, y); }
    auto del(int x, int y) { del(1, 1, n, x, y); }
    auto query(int pos)
    {
        if (pos > n)
            return info(INT_MIN, 0);
        return query(1, 1, n, pos);
    }
};
struct Main
{
    segment tree;
    othersegment other;
    int n, q;
    vector<pair<int, int>> a;
    vector<int> p;
    multiset<pair<int, int>> all;
    auto add(int l, int r)
    {
        all.emplace(l, r);
        if (l > r)
            tree.update(r, l - 1, 1);
        other.add(r, l);
    }
    auto del(int l, int r)
    {
        all.erase(all.find(make_pair(l, r)));
        if (l > r)
            tree.update(r, l - 1, -1);
        other.del(r, l);
    }
    Main()
    {
        cin >> n >> q;
        a.resize(n);
        for (auto &[x, y] : a)
        {
            cin >> x >> y;
            p.push_back(x), p.push_back(y);
        }
        vector<tuple<int, int, int>> query(q);
        for (auto &[id, x, y] : query)
        {
            cin >> id >> x >> y;
            p.push_back(x), p.push_back(y);
        }
        sort(p.begin(), p.end());
        p.erase(unique(p.begin(), p.end()), p.end());
        tree = segment((int)p.size()), other = othersegment((int)p.size());
        auto trans = [&](int x)
        {
            return (int)(lower_bound(p.begin(), p.end(), x) - p.begin() + 1);
        };
        for (auto &[x, y] : a)
            x = trans(x), y = trans(y);
        for (auto &[id, x, y] : query)
            x = trans(x), y = trans(y);
        auto get = [&]()
        {
            int maxx = all.rbegin()->first;
            auto [othera, othercnt] = other.query(maxx + 1);
            if (othercnt == 0)
                return 1;
            else if (othera == maxx)
                return othercnt;
            else
                return othercnt + (tree.query(maxx - 1) > othera);
        };
        for (auto [x, y] : a)
            add(x, y);
        cout << get() << '\n';
        for (auto [id, l, r] : query)
        {
            --id;
            del(a[id].first, a[id].second);
            a[id] = make_pair(l, r);
            add(a[id].first, a[id].second);
            cout << get() << '\n';
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
