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
constexpr int mod1 = 1e9 + 7;
constexpr int mod2 = 1e9 + 9;
template <int mod>
struct Hash : vector<i64>
{
    using vector<i64>::vector;
    static inline vector<i64> power = {1};
    static constexpr auto base = 97;
    static auto ensure(int n)
    {
        while ((int)power.size() <= n)
            power.emplace_back(power.back() * base % mod);
    }
    Hash(const string &s) : vector(s.size())
    {
        for (int i = 0; i < (int)s.size(); ++i)
            at(i) = ((i ? at(i - 1) : 0) * base + (s[i] - 'a' + 1)) % mod;
    }
    auto query(int l, int r)
    {
        ensure(r - l + 1);
        return ((at(r) - (l ? at(l - 1) : 0) * power[r - l + 1]) % mod + mod) % mod;
    }
};
struct UnionSet : vector<int>
{
    using vector<int>::vector;
    UnionSet() = default;
    UnionSet(size_t n) : vector(n) { iota(begin(), end(), 0); }
    auto find(int x) -> int
    {
        return at(x) == x ? x : at(x) = find(at(x));
    }
    auto merge(int x, int y)
    {
        x = find(x), y = find(y);
        if (x == y)
            return;
        at(x) = y;
    }
    auto check(int x, int y)
    {
        return find(x) == find(y);
    }
};
struct Main
{
    int n, m;
    vector<string> a, b;
    vector<Hash<mod1>> A1, B1;
    vector<Hash<mod2>> A2, B2;
    vector<vector<int>> G;
    vector<bool> vis;
    stack<int> st;
    auto dfs(int u) -> void
    {
        while (!G[u].empty())
        {
            int v = G[u].back();
            G[u].pop_back();
            dfs(v);
        }
        st.push(u);
    }
    Main()
    {
        cin >> n >> m;
        a.resize(n), b.resize(n);
        A1.resize(n), B1.resize(n);
        A2.resize(n), B2.resize(n);
        for (int i = 0; i < n; ++i)
        {
            cin >> a[i];
            A1[i] = Hash<mod1>(a[i]);
            A2[i] = Hash<mod2>(a[i]);
        }
        for (int i = 0; i < n; ++i)
        {
            cin >> b[i];
            B1[i] = Hash<mod1>(b[i]);
            B2[i] = Hash<mod2>(b[i]);
        }
        auto queryA = [&](int id, int l, int r)
        {
            return pair{A1[id].query(l, r), A2[id].query(l, r)};
        };
        auto queryB = [&](int id, int l, int r)
        {
            return pair{B1[id].query(l, r), B2[id].query(l, r)};
        };
        {
            map<pair<int, int>, vector<int>> mp;
            for (int i = 0; i < n; ++i)
                mp[queryA(i, 0, m - 1)].emplace_back(i);
            vector<int> p;
            bool flag = true;
            for (int i = 0; i < n; ++i)
                if (!mp[queryB(i, 0, m - 1)].empty())
                {
                    p.emplace_back(mp[queryB(i, 0, m - 1)].back());
                    mp[queryB(i, 0, m - 1)].pop_back();
                }
                else
                {
                    flag = false;
                    break;
                }
            if (flag)
            {
                for (auto i : p)
                    cout << i + 1 << ' ';
                cout << '\n';
                for (int i = 1; i <= n; ++i)
                    cout << i << ' ';
                cout << '\n';
                return;
            }
        }
        for (int basis = 1; basis < m; ++basis)
        {
            int tot = 2 * n;
            map<pair<i64, i64>, int> mpA, mpB;
            for (int i = 0; i < n; ++i)
            {
                if (!mpA[queryA(i, 0, basis - 1)])
                    mpA[queryA(i, 0, basis - 1)] = tot++;
                if (!mpB[queryA(i, basis, m - 1)])
                    mpB[queryA(i, basis, m - 1)] = tot++;
            }
            for (int i = 0; i < n; ++i)
            {
                if (!mpB[queryB(i, 0, m - basis - 1)])
                    mpB[queryB(i, 0, m - basis - 1)] = tot++;
                if (!mpA[queryB(i, m - basis, m - 1)])
                    mpA[queryB(i, m - basis, m - 1)] = tot++;
            }
            G.assign(tot, vector<int>());
            vector<int> in(tot), out(tot);
            UnionSet us(tot);
            for (int i = 0; i < n; ++i)
            {
                int u, v;

                u = i, v = mpB[queryA(i, basis, m - 1)];
                G[u].emplace_back(v);
                ++out[u], ++in[v];
                us.merge(u, v);

                u = mpA[queryA(i, 0, basis - 1)], v = i;
                G[u].emplace_back(v);
                ++out[u], ++in[v];
                us.merge(u, v);

                u = mpB[queryB(i, 0, m - basis - 1)], v = i + n;
                G[u].emplace_back(v);
                ++out[u], ++in[v];
                us.merge(u, v);

                u = i + n, v = mpA[queryB(i, m - basis, m - 1)];
                G[u].emplace_back(v);
                ++out[u], ++in[v];
                us.merge(u, v);
            }
            bool flag = true;
            for (int i = 0; i < tot; ++i)
                flag = flag & (in[i] == out[i]) & (us.check(0, i));
            // if (basis == 1)
            // {
            //     for (int u = 0; u < tot; ++u)
            //     {
            //         for (auto v : G[u])
            //             cout << u << ' ' << v << '\n';
            //     }
            //     cout << '\n';
            // }
            if (flag)
            {
                dfs(0);
                vector<int> p, q;
                while (!st.empty())
                {
                    int u = st.top();
                    st.pop();
                    if (u < n)
                        p.emplace_back(u + 1);
                    else if (u < 2 * n)
                        q.emplace_back(u - n + 1);
                }
                p.pop_back();
                for (auto i : p)
                    cout << i << ' ';
                cout << '\n';
                for (auto i : q)
                    cout << i << ' ';
                cout << '\n';
                return;
            }
        }
        cout << "-1\n";
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
