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
struct Main
{
    int D;
    int n, m;
    vector<int> cf;
    vector<pair<int, int>> p;
    auto solve(int deep = 0)
    {
        if (deep == (int)cf.size())
            return;
        int y = cf[deep];
        m += y;
        solve(deep + 1);
        for (int i = 0; i < y; i++)
        {
            if (deep & 1)
                p.emplace_back(1, n);
            else
            {
                ++n;
                p.emplace_back(n - 1, n);
            }
        }
        
    }
    Main()
    {
        cin >> D;
        int a0 = 0;
        for (int i = 1; i * i <= D; ++i)
        {
            a0 = i;
            if (i * i == D)
            {
                cout << i + 1 << ' ' << i << '\n';
                for (int j = 1; j <= i; ++j)
                    cout << j << ' ' << j + 1 << '\n';
                return;
            }
        }
        int x = 0, y = 1, a = a0;
        vector<int> prefix;
        int sum = 0, even_sum = 0;
        const long double target = sqrtl((long double)D);
        while (cf.empty())
        {
            if (prefix.size() % 2 == 0)
            {
                for (int last = 1; sum + last <= 300 && even_sum + last <= 299; ++last)
                {
                    vector<int> candidate = prefix;
                    candidate.emplace_back(last);
                    long double value = candidate.back();
                    for (int i = (int)candidate.size() - 2; i >= 0; --i)
                        value = candidate[i] + 1 / value;
                    if (fabsl(value - target) <= 1e-6L)
                    {
                        cf = move(candidate);
                        break;
                    }
                }
                if (!cf.empty())
                    break;
            }

            if (sum + a > 300 || even_sum + (prefix.size() % 2 == 0 ? a : 0) > 299)
                break;
            prefix.emplace_back(a);
            sum += a;
            if (prefix.size() & 1)
                even_sum += a;
            x = y * a - x;
            y = (D - x * x) / y;
            a = (a0 + x) / y;
        }
        assert(!cf.empty());
        n = 1, m = 0;
        solve();
        cout << n << ' ' << p.size() << '\n';
        for (auto [x, y] : p)
            cout << x << ' ' << y << '\n';
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
