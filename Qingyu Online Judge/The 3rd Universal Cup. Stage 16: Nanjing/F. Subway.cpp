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
struct node
{
    i64 k, b;
    node() = default;
    node(i64 _k, i64 _b) : k(_k), b(_b) {}
    auto calc(int x) { return k * x + b; }
};
struct segment
{
    struct Tree
    {
        int lc, rc;
        node ans;
    };
    vector<Tree> tree;
    int cnt;
#define lc(rt) tree[rt].lc
#define rc(rt) tree[rt].rc
    auto update(int &rt, int l, int r, node val)
    {
        if (!rt)
            tree[rt = ++cnt] = tree[0];
        int mid = (l + r) >> 1;
        auto ans = tree[rt].ans.calc(mid), res = val.calc(mid);
        if (l == r)
        {
            if (res < ans)
                tree[rt].ans = val;
            return;
        }
        if (tree[rt].ans.k < val.k)
        {
            if (res < ans)
            {
                update(rc(rt), mid + 1, r, tree[rt].ans);
                tree[rt].ans = val;
            }
            else
                update(lc(rt), l, mid, val);
        }
        else if (tree[rt].ans.k > val.k)
        {
            if (res < ans)
            {
                update(lc(rt), l, mid, tree[rt].ans);
                tree[rt].ans = val;
            }
            else
                update(rc(rt), mid + 1, r, val);
        }
        else
        {
            if (res < ans)
                tree[rt].ans = val;
        }
    }
    auto query(int rt, int l, int r, int pos) -> i64
    {
        if (!rt)
            return LONG_LONG_MAX;
        if (l == r)
            return tree[rt].ans.calc(pos);
        int mid = (l + r) >> 1;
        return min(tree[rt].ans.calc(pos),
                   pos <= mid ? query(lc(rt), l, mid, pos) : query(rc(rt), mid + 1, r, pos));
    }
    segment() = default;
    segment(int n) : tree((n + 5) * 50), cnt(0)
    {
        tree[0].ans = node(0, LONG_LONG_MAX);
    }
};
struct Main
{
    int n, m;
    vector<int> a, b;
    Main()
    {
        cin >> n >> m;
        a.resize(m), b.resize(m);
        for (int &i : a)
            cin >> i;
        for (int &i : b)
            cin >> i;
        vector<vector<int>> p(m), c(m);
        vector<list<int>> g(n);
        vector<map<int, int>> mp(m);
        int all = 0;
        for (int i = 0; i < m; ++i)
        {
            int q;
            cin >> q;
            all += q;
            for (int j = 1; j < 2 * q; ++j)
            {
                int x;
                cin >> x;
                if (j & 1)
                {
                    --x;
                    mp[i][x] = (int)p[i].size();
                    p[i].push_back(x);
                    g[x].push_back(i);
                }
                else
                    c[i].push_back(x);
            }
        }
        for (int i = 0; i < n; ++i)
            g[i].sort([&](int x, int y)
                      { return a[x] < a[y]; });
        priority_queue<tuple<i64, int, int>, vector<tuple<i64, int, int>>, greater<tuple<i64, int, int>>> q;
        vector<set<int>> vis(n);
        vector<i64> dis(n, LONG_LONG_MAX);
        vector<int> root(n);
        for (int i : g[0])
            q.emplace(0, 0, i);
        segment tree(all);
        while (!q.empty())
        {
            auto [d, u, o] = q.top();
            q.pop();
            if (vis[u].find(o) != vis[u].end())
                continue;
            vis[u].insert(o);
            dis[u] = min(dis[u], d);
            tree.update(root[u], 1, 1e6, node(b[o], d));
            {
                while (!g[u].empty() && vis[u].find(g[u].front()) != vis[u].end())
                    g[u].pop_front();
                if (!g[u].empty())
                {
                    int v = g[u].front();
                    q.emplace(tree.query(root[u], 1, 1e6, a[v]), u, v);
                }
            }
            
            {
                auto it = mp[o][u];
                if (it + 1 < (int)p[o].size())
                    q.emplace(d + c[o][it], p[o][it + 1], o);
            }
        }
        for (int i = 1; i < n; ++i)
            cout << dis[i] << ' ';
        cout << '\n';
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
