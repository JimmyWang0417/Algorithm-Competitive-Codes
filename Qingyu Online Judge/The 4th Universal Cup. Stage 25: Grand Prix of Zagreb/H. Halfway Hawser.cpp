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
    string s;
    auto calc(int x)
    {
        return s.substr(0, x) + s.substr(x + 1);
    }
    Main()
    {
        cin >> s;
        int n = (int)s.length(), k = (n + 1) / 2;
        for (int i = 0, j = 0; i + 1 < n; ++i)
            if (s[i] != s[i + 1])
            {
                if (s[i] < s[i + 1])
                {
                    if (n - 1 - i < k)
                    {
                        cout << calc(i) << '\n';
                        return;
                    }
                }
                else
                {
                    if (i - j + 1 >= k)
                    {
                        cout << calc(i) << '\n';
                        return;
                    }
                    k -= (i - j + 1);
                }
                j = i + 1;
            }
        cout << calc(n - 1) << '\n';
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
