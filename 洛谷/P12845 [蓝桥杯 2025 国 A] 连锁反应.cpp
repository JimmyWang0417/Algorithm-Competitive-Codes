#include <bits/stdc++.h>
#include <cassert>
using namespace std;
typedef int64_t i64;
typedef uint64_t u64;
typedef __int128_t i128;
typedef __uint128_t u128;
typedef __float80 f80;
typedef __float128 f128;
constexpr int mod = 998244353;
struct Main
{
    int n, cnt;
    vector<tuple<int, int, int>> a;
    vector<vector<int>> g, h;
    vector<int> tree;
#define lc (rt << 1)
#define rc (rt << 1 | 1)
    auto build(int rt, int l, int r) -> void
    {
        tree[rt] = (int)g.size();
        g.push_back({});
        if (l == r)
        {
            tree[rt] = l;
            return;
        }
        int mid = (l + r) / 2;
        build(lc, l, mid);
        build(rc, mid + 1, r);
        g[tree[rt]].push_back(tree[lc]);
        g[tree[rt]].push_back(tree[rc]);
    }
    auto update(int rt, int l, int r, int x, int y, int v)
    {
        if (r < x || l > y)
            return;
        if (x <= l && r <= y)
            return g[v].push_back(tree[rt]);
        int mid = (l + r) >> 1;
        update(lc, l, mid, x, y, v);
        update(rc, mid + 1, r, x, y, v);
    }
    vector<int> dfn, low;
    vector<int> belong, have;
    stack<int> st;
    int dfstime, color;
    auto tarjan(int u) -> void
    {
        dfn[u] = low[u] = ++dfstime;
        st.push(u);
        for (int v : g[u])
        {
            if (!dfn[v])
            {
                tarjan(v);
                low[u] = min(low[u], low[v]);
            }
            else if (!belong[v])
                low[u] = min(low[u], dfn[v]);
        }
        if (dfn[u] == low[u])
        {
            have[belong[u] = ++color] += (u < n);
            while (st.top() != u)
            {
                have[belong[st.top()] = color] += (st.top() < n);
                st.pop();
            }
            st.pop();
        }
    }
    Main() : dfstime(0), color(0)
    {
        cin >> n;
        a.resize(n);
        for (auto &[p, l, r] : a)
        {
            cin >> p >> l >> r;
            l = p - l, r = p + r;
        }
        sort(a.begin(), a.end());
        {
            tree.resize(4 * n + 5);
            g.resize(n);
            build(1, 0, n - 1);
            for (int i = 0; i < n; ++i)
            {
                auto [p, l, r] = a[i];
                int x = (int)(lower_bound(a.begin(), a.end(), make_tuple(l, INT_MIN, INT_MIN)) - a.begin());
                int y = (int)(upper_bound(a.begin(), a.end(), make_tuple(r, INT_MAX, INT_MAX)) - a.begin() - 1);
                update(1, 0, n - 1, x, y, i);
                // cout << i << ' ' << x << ' ' << y << '\n';
            }
        }
        // for (int u = 0; u < (int)g.size(); ++u)
        // {
        //     cerr << u << ":";
        //     for (int v : g[u])
        //         cerr << ' ' << v;
        //     cerr << '\n';
        // }
        {
            dfn.resize(g.size());
            low.resize(g.size());
            belong.resize(g.size());
            have.resize(g.size());
            for (int i = 0; i < (int)g.size(); ++i)
                if (!dfn[i])
                    tarjan(i);
        }
        vector<int> in(color + 5);
        {
            h.resize(color + 5);
            for (int u = 0; u < (int)g.size(); ++u)
            {
                for (int v : g[u])
                {
                    if (belong[u] == belong[v])
                        continue;
                    h[belong[u]].push_back(belong[v]);
                    ++in[belong[v]];
                }
            }
        }
        {
            queue<int> q;
            for (int i = 1; i <= color; ++i)
                if (!in[i])
                    q.push(i);
            int res = 0;
            while (!q.empty())
            {
                int u = q.front();
                q.pop();
                if (have[u])
                {
                    ++res;
                    continue;
                }
                for (int v : h[u])
                    if (!--in[v])
                        q.push(v);
            }
            cout << res << '\n';
        }
    }
};
signed main()
{
    // freopen("project.in", "r", stdin);
    // freopen("project.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--)
        Main();
    return 0;
}