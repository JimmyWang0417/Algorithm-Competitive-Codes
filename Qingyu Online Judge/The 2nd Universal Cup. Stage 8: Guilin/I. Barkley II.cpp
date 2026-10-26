#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
struct segment
{
    struct node
    {
        int lc, rc;
        int sze;
    };
    vector<node> tree;
    int n;
#define lc(rt) tree[rt].lc
#define rc(rt) tree[rt].rc
    segment() = default;
    segment(int _n) : tree(1), n(_n) {}
    auto newnode()
    {
        tree.emplace_back();
        return (int)tree.size() - 1;
    }
    auto update(int rt, int l, int r, int pos, int val)
    {
        int newrt = newnode();
        tree[newrt] = tree[rt];
        rt = newrt;
        tree[rt].sze += val;
        if (l == r)
            return rt;
        int mid = (l + r) >> 1;
        if (pos <= mid)
            lc(rt) = update(lc(rt), l, mid, pos, val);
        else
            rc(rt) = update(rc(rt), mid + 1, r, pos, val);
        return rt;
    }
    auto query(int rt, int l, int r, int x, int y)
    {
        if (!rt || r < x || l > y)
            return 0;
        if (x <= l && r <= y)
            return tree[rt].sze;
        int mid = (l + r) >> 1;
        return query(lc(rt), l, mid, x, y) + query(rc(rt), mid + 1, r, x, y);
    }
    auto update(int rt, int pos, int val)
    {
        return update(rt, 1, n, pos, val);
    }
    auto query(int rt, int x, int y)
    {
        return query(rt, 1, n, x, y);
    }
};
struct Main
{
    int n, m;
    vector<int> a, b;
    vector<int> root;
    segment tree;
    Main()
    {
        cin >> n >> m;
        a.resize(n + 5), b.resize(n + 5);
        for (int i = 1; i <= n; ++i)
            cin >> a[i];
        {
            vector<vector<int>> G(n);
            unordered_map<int, int> mp;
            for (int i = 1; i <= n; ++i)
            {
                b[i] = mp[a[i]];
                mp[a[i]] = i;
                G[b[i]].emplace_back(i);
            }
            tree = segment(n);
            root.resize(n);
            for (int i = 0; i < n; ++i)
            {
                if (i)
                    root[i] = root[i - 1];
                for (auto j : G[i])
                    root[i] = tree.update(root[i], j, 1);
            }
        }
        auto query = [&](int l, int r)
        {
            return tree.query(root[l - 1], l, r);
        };
        vector<vector<int>> H(n + 1);
        for (int i = 1; i <= n; ++i)
        {
            if (a[i] <= n)
                H[a[i]].emplace_back(i);
        }
        int answer = -1;
        for (int v = 1; v <= n; ++v)
        {
            auto p = H[v];
            p.insert(p.begin(), 0);
            p.push_back(n + 1);
            int res = 0;
            for (int i = 1; i < (int)p.size(); ++i)
            {
                if (p[i - 1] + 1 <= p[i] - 1)
                    res = max(res, query(p[i - 1] + 1, p[i] - 1));
            }
            answer = max(answer, res - v);
        }
        cout << answer << '\n';
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
