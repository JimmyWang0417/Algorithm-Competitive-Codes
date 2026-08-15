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
constexpr int mod = 1e6 + 3;
template <typename T = int>
constexpr auto quickpow(i64 a, T b = mod - 2)
{
    a %= mod;
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

    Main()
    {
        string _;
        cin >> _;
        if (_ == "first")
        {
            int n, k;
            cin >> n >> k;
            vector<i64> f(k + 1);
            f[0] = 1;
            for (int i = 0; i < n + k; ++i)
            {
                int v;
                cin >> v;
                for (int j = k - 1; j >= 0; --j)
                    (f[j + 1] -= f[j] * v) %= mod;
            }
            for (int i = 1; i <= k; ++i)
                cout << (f[i] + mod) % mod << ' ';
            cout << '\n';
        }
        else
        {
            int n, k;
            cin >> n >> k;
            vector<i64> f(k + 1);
            f[0] = 1;
            for (int i = 1; i <= k; ++i)
                cin >> f[i];
            auto check = [&](int c)
            {
                i64 res = 0;
                for (int i = 0; i <= k; ++i)
                    res = (res * c + f[i]) % mod;
                return res == 0;
            };
            auto solve = [&](int c)
            {
                for (int j = 0; j < k; ++j)
                    (f[j + 1] += f[j] * c) %= mod;
            };
            for (int i = 0; i < n; ++i)
            {
                int v;
                cin >> v;
                solve(v);
            }
            for (int i = 1; i <= 1e6; ++i)
                while (check(i))
                {
                    solve(i);
                    cout << i << ' ';
                }
            cout << '\n';
        }
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

