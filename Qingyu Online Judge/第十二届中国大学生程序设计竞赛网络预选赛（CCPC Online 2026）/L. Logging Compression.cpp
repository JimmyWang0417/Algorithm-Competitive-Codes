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

ostream &operator<<(ostream &out, i128 x)
{
    if (x == 0)
        return out << '0';
    if (x < 0)
    {
        out << '-';
        x = -x;
    }
    string s;
    while (x)
    {
        s.push_back(char('0' + x % 10));
        x /= 10;
    }
    reverse(s.begin(), s.end());
    return out << s;
}

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
struct Main
{
    i64 n;
    int m;
    map<i64, vector<pair<i64, i64>>> mp;
    Main()
    {
        cin >> n >> m;
        for (int i = 0; i < m; ++i)
        {
            i64 l, r;
            cin >> l >> r;
            mp[l].emplace_back(1, 1), mp[r + 1].emplace_back(1, -1);
        }
        if (n == 1)
        {
            cout << m << '\n';
            return;
        }
        for (i64 l = 1, r; l <= n; l = r + 1)
        {
            r = min(n, n / (n / l));
            mp[l].emplace_back(2, n / l);
        }
        map<i64, i64> vec;
        {
            i64 A = 0, B = 0;
            i64 las = 1;
            for (const auto &[p, v] : mp)
            {
                if (las < p)
                    vec[A * B] += p - las;
                for (auto [o, w] : v)
                    if (o == 1)
                        A += w;
                    else
                        B = w;
                las = p;
            }
            if (las < n + 1)
                vec[A * B] += n + 1 - las;
        }
        i128 answer = 0;
        {
            queue<pair<i128, i64>> p, q;
            for (auto [x, y] : vec)
                p.emplace(x, y);
            auto empty = [&]()
            {
                return p.empty() && q.empty();
            };
            auto front = [&]() -> pair<i128, i64> &
            {
                if (p.empty())
                    return q.front();
                else if (q.empty())
                    return p.front();
                else if (p.front() < q.front())
                    return p.front();
                else
                    return q.front();
            };
            auto pop = [&]()
            {
                auto f = front();
                if (!p.empty() && p.front() == f)
                    p.pop();
                else
                    q.pop();
            };
            auto emplace = [&](auto x, auto y)
            {
                q.emplace(x, y);
            };
            while (!empty())
            {
                auto [u, w1] = front();
                if (w1 >= 2)
                {
                    auto c = w1 / 2;
                    w1 -= 2 * c;
                    answer += (i128)c * (u + u);
                    if (!w1)
                        pop();
                    else
                        front().second = w1;
                    emplace(u + u, c);
                }
                else
                {
                    pop();
                    if (empty())
                        break;
                    auto [v, w2] = front();
                    auto c = min(w1, w2);
                    w1 -= c, w2 -= c;
                    answer += (i128)c * (u + v);
                    if (!w2)
                        pop();
                    else
                        front().second = w2;
                    emplace(u + v, c);
                }
            }
        }
        cout << answer << '\n';
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
