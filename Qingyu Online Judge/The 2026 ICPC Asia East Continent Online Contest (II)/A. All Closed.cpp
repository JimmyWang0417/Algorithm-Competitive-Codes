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
int n, m;
struct LinnerBasis : array<int, 20>
{
    LinnerBasis() : array<int, 20>{} {}
    auto insert(int v)
    {
        for (int i = m - 1; i >= 0; --i)
            if ((v >> i) & 1)
            {
                if (!at(i))
                {
                    at(i) = v;
                    return true;
                }
                v ^= at(i);
            }
        return false;
    }
    auto contain(int v) const
    {
        for (int i = m - 1; i >= 0; --i)
            if ((v >> i) & 1)
            {
                if (!at(i))
                    return false;
                v ^= at(i);
            }
        return true;
    }
    auto count()
    {
        int res = 1;
        for (int i = m - 1; i >= 0; --i)
            if (at(i))
                res *= 2;
        return res;
    }
    auto all()
    {
        vector<int> p = {0};
        for (int i = m - 1; i >= 0; --i)
            if (at(i))
            {
                int tot = (int)p.size();
                for (int k = 0; k < tot; ++k)
                    p.emplace_back(p[k] ^ at(i));
            }
        return p;
    }
};
struct Main
{
    vector<vector<int>> a;
    vector<LinnerBasis> sp;
    LinnerBasis U;
    vector<int> cnt;
    Main()
    {
        cin >> n >> m;
        a.resize(n);
        sp.resize(n);
        cnt.resize(1 << m);
        vector<bool> exist(1 << m);
        for (int i = 0; i < n; ++i)
        {
            int c;
            cin >> c;
            a[i].resize(c);
            for (auto &j : a[i])
            {
                cin >> j;
                sp[i].insert(j);
                cnt[j]++;
            }
            if (sp[i].count() <= (int)a[i].size() * 2)
            {
                for (auto j : a[i])
                    exist[j] = true;
                auto p = sp[i].all();
                for (auto j : p)
                {
                    if (exist[j])
                        continue;
                    U.insert(j);
                }
                for (auto j : a[i])
                    exist[j] = false;
            }
            else
            {
                for (auto j : sp[i])
                    if (j)
                        U.insert(j);
            }
        }
        vector<int> q;
        for (auto i : U)
            if (i)
                q.emplace_back(i);
        vector<bool> fixed(n);
        for (auto k = 0; k < (int)q.size(); ++k)
            for (auto i = 0; i < n; ++i)
            {
                if (fixed[i] || sp[i].contain(q[k]))
                    continue;
                fixed[i] = true;
                for (auto j : sp[i])
                    if (j && U.insert(j))
                        q.emplace_back(j);
            }
        auto V = U.all();
        vector<int> T;
        for (auto i : V)
        {
            if (cnt[i] == n)
                continue;
            T.emplace_back(i);
        }
        cout << T.size() << '\n';
        for (auto i : T)
            cout << i << ' ';
        cout << '\n';
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
