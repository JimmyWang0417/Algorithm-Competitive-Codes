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
template <typename T1, typename T2>
auto operator+(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
{
    return make_pair(lhs.first + rhs.first, lhs.second + rhs.second);
}
struct Main
{
    int n, m, k;
    vector<int> a;
    struct fraction
    {
        int x, y;
        fraction() = default;
        fraction(int _x, int _y) : x(_x), y(_y) {}
        auto &adjust()
        {
            auto g = __gcd(x, y);
            x /= g, y /= g;
            return (*this);
        }
        auto operator==(const fraction &rhs) const
        {
            return (i64)x * rhs.y == (i64)rhs.x * y;
        }
        auto operator<=>(const fraction &rhs) const
        {
            return (i64)x * rhs.y <=> (i64)rhs.x * y;
        }
        auto friend &operator<<(ostream &out, const fraction &rhs)
        {
            out << rhs.x << ' ' << rhs.y;
            return out;
        }
    };
    vector<fraction> p;
    vector<vector<pair<fraction, int>>> q;
    auto MAX()
    {
        if (k < m)
            return fraction(1, 1);
        int l = 1, r = (int)p.size() - 1;
        while (l <= r)
        {
            auto calc = [&](fraction mid)
            {
                int cnt = 0;
                for (int i = 0, j = 0; i < n; i = j)
                {
                    int x = INT_MAX, y = 0;
                    while (j < n && fraction(x & a[j], y | a[j]) >= mid)
                    {
                        x &= a[j], y |= a[j];
                        ++j;
                    }
                    ++cnt;
                }
                return cnt;
            };
            int mid = (l + r) >> 1;
            if (calc(p[mid]) <= m)
                l = mid + 1;
            else
                r = mid - 1;
        }
        return p[r];
    }
    auto MIN() -> fraction
    {
        auto calc = [&](fraction lim)
        {
            vector<int> L(n + 1, -1);
            for (int i = 1; i <= n; ++i)
            {
                for (auto [u, v] : q[i - 1])
                    if (u <= lim)
                        L[i] = v;
            }
            auto compare = [](auto x, auto y)
            {
                return x.first == y.first ? x.second > y.second : x.first < y.first;
            };
            auto get = [&](i64 ad)
            {
                vector<pair<i64, int>> dp(n + 1);
                for (int i = 1; i <= n; ++i)
                {
                    dp[i] = dp[i - 1];
                    if (L[i] != -1)
                        dp[i] = min(dp[i], dp[L[i]] + make_pair((i - L[i]) + ad, 1), compare);
                }
                return dp[n];
            };
            i64 l = -1e13, r = 1e13;
            while (l <= r)
            {
                auto mid = (l + r) >> 1;
                if (get(mid).second >= m + 1 - k)
                    l = mid + 1;
                else
                    r = mid - 1;
            }
            auto [x, y] = get(r);
            return n - (x - r * (m + 1 - k));
        };
        // for (int i = 0; i < (int)p.size(); ++i)
        //     cout << calc(p[i]) << '\n';
        int l = 0, r = (int)p.size() - 2;
        while (l <= r)
        {
            auto mid = (l + r) >> 1;
            if (calc(p[mid]) >= k - 1)
                r = mid - 1;
            else
                l = mid + 1;
        }
        return p[l];
    }
    Main()
    {
        cin >> n >> m >> k;
        a.resize(n);
        for (auto &i : a)
            cin >> i;
        vector<tuple<int, int, int>> b;
        q.resize(n);
        for (int i = 0; i < n; ++i)
        {
            {
                vector<tuple<int, int, int>> c;
                b.emplace_back(a[i], a[i], i);
                for (auto v : b)
                {
                    get<0>(v) &= a[i];
                    get<1>(v) |= a[i];
                    if (!c.empty() &&
                        get<0>(c.back()) == get<0>(v) &&
                        get<1>(c.back()) == get<1>(v))
                        c.pop_back();
                    c.emplace_back(v);
                }
                b.swap(c);
            }
            for (auto [v, w, _] : b)
            {
                auto u = fraction(v, w).adjust();
                p.emplace_back(u);
                q[i].emplace_back(u, _);
            }
        }
        sort(p.begin(), p.end());
        p.erase(unique(p.begin(), p.end()), p.end());
        cout << MAX() << '\n';
        cout << MIN() << '\n';
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

