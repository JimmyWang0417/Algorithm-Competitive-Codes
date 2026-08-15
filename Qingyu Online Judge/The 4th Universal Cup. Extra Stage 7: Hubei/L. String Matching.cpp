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
constexpr int mod1 = 998244353;
constexpr int mod2 = 1e9 + 7;
constexpr int base = 31;
struct Main
{
    int n;
    vector<string> a;
    vector<vector<int>> p;
    vector<int> f;
    struct node : array<int, 26>
    {
        using array<int, 26>::array;
        int fail;
    };
    vector<node> tree;
    auto insert(const string &s)
    {
        auto newnode = [&]()
        {
            tree.emplace_back();
            return (int)tree.size() - 1;
        };
        int u = 0;
        vector<int> _;
        for (auto _c : s)
        {
            int c = _c - 'a';
            if (!tree[u][c])
                tree[u][c] = newnode();
            u = tree[u][c];
            _.push_back(u);
        }
        return _;
    }
    auto build()
    {
        queue<int> q;
        for (int i = 0; i < 26; ++i)
            if (tree[0][i])
                q.push(tree[0][i]);
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            for (int i = 0; i < 26; ++i)
                if (!tree[u][i])
                    tree[u][i] = tree[tree[u].fail][i];
                else
                {
                    tree[tree[u][i]].fail = tree[tree[u].fail][i];
                    q.push(tree[u][i]);
                }
        }
    }
    template <int mod>
    struct Hash : vector<i64>
    {
        using vector<i64>::vector;
        static inline std::vector<int> power{1};
        static void ensure(int n)
        {
            while ((int)power.size() <= n)
                power.push_back((int)((i64)power.back() * base % mod));
        }
        Hash(const string &s)
        {
            resize(s.size());
            for (int i = 0; i < (int)s.size(); ++i)
                at(i) = ((i ? at(i - 1) : 0) * base + s[i] - 'a' + 1) % mod;
        }
        auto calc(int l, int r)
        {
            ensure(r - l + 1);
            return (at(r) - (l > 0 ? at(l - 1) * power[r - l + 1] % mod : 0) + mod) % mod;
        }
    };
    using h1 = Hash<mod1>;
    using h2 = Hash<mod2>;
    vector<vector<int>> G;
    auto dfs(int u) -> void
    {
        for (int v : G[u])
        {
            f[v] += f[u];
            dfs(v);
        }
    }
    Main() : tree(1)
    {
        cin >> n;
        a.resize(n);
        p.resize(n);
        for (auto &&[s, u] : views::zip(a, p))
        {
            cin >> s;
            u = insert(s);
        }
        build();
        f.resize(tree.size());
        for (int i = 0; i < n; ++i)
            f[p[i].back()]++;
        G.resize(tree.size());
        for (int i = 1; i < (int)tree.size(); ++i)
            G[tree[i].fail].push_back(i);
        dfs(0);
        vector<h1> A(n);
        vector<h2> B(n);
        vector<vector<int>> C(n);
        for (int _ = 0; _ < n; ++_)
        {
            const auto &s = a[_];
            A[_] = h1(s);
            B[_] = h2(s);
            vector<int> P(s.size());
            for (int i = 1, j = 0; i < (int)s.size(); ++i)
            {
                while (j && s[i] != s[j])
                    j = P[j - 1];
                if (s[i] == s[j])
                    ++j;
                P[i] = j;
            }
            for (int j = P.back(); j; j = P[j - 1])
                C[_].push_back(j);
        }
        i64 ans = 0;
        {
            i64 ans1 = 0;
            map<pair<i64, i64>, int> mp;
            for (int i = 0; i < n; ++i)
            {
                for (int j = 0; j < (int)a[i].size(); ++j)
                    ans1 += mp[{A[i].calc((int)a[i].size() - j - 1, (int)a[i].size() - 1),
                                B[i].calc((int)a[i].size() - j - 1, (int)a[i].size() - 1)}];
                for (int j = 0; j < (int)a[i].size(); ++j)
                    mp[{A[i].calc(0, j), B[i].calc(0, j)}]++;
            }
            ans += ans1;
        }
        {
            i64 ans2 = 0;
            for (int i = 0; i < n; ++i)
            {
                for (int j : C[i])
                    ans2 += f[p[i][a[i].size() - j - 1]];
            }
            ans += ans2;
        }
        {
            i64 ans3 = 0;
            map<pair<i64, i64>, int> mp;
            for (int i = 0; i < n; ++i)
            {
                for (int j : C[i])
                    ans3 += mp[{A[i].calc(0, (int)a[i].size() - j - 1),
                                B[i].calc(0, (int)a[i].size() - j - 1)}];
                for (int j : C[i])
                    mp[{A[i].calc(j, (int)a[i].size() - 1),
                        B[i].calc(j, (int)a[i].size() - 1)}]++;
            }
            ans += ans3;
        }
        cout << ans + (i64)n * (n - 1) / 2 << '\n';
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
