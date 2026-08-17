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
    int n;
    string s;
    auto solve()
    {
        int i = 0, j = 1, k = 0;
        while (i < n && j < n && k < n)
        {
            if (s[(i + k) % n] == s[(j + k) % n])
                ++k;
            else
            {
                if (s[(i + k) % n] > s[(j + k) % n])
                    i += k + 1;
                else
                    j += k + 1;
                if (i == j)
                    ++j;
                k = 0;
            }
        }
        return min(i, j);
    }
    Main()
    {
        cin >> n;
        cin >> s;
        auto ans = solve();
        cout << s.substr(ans) + s.substr(0, ans) << '\n';
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
