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
constexpr int mod = 1e9 + 7;
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
    int n, m;
    vector<int> a;
    Main()
    {
        cin >> n >> m;
        a.resize(n);
        for (auto &i : a)
            cin >> i;
        ranges::sort(a);
        int x = 0, y = 1, t = 0;
        i64 res = m;
        for (int i = 0; i < n; ++i)
        {
            int c = (a[i] - x + y - 1) / y;
            if (t + c <= m)
            {
                x += y * c;
                x -= a[i], y++;
                t += c;
                res = max(res, x + (i64)(m - t) * y);
            }
        }
        cout << res << '\n';
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
