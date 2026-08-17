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
auto f(i128 a, i128 b, i128 c, i128 n) -> i128
{
    auto ac = a / c, bc = b / c;
    auto n2 = n * (n + 1) / 2;
    if (a >= c || b >= c)
        return n2 * ac + (n + 1) * bc + f(a % c, b % c, c, n);
    else
    {
        auto m = (a * n + b) / c;
        if (m == 0)
            return 0;
        return n * m - f(c, c - b - 1, a, m - 1);
    }
}
struct Main
{
    int n;
    i64 m;
    vector<i64> a;
    auto check(i64 mid) -> bool
    {
        auto t = mid / m;
        for (int i = n - 1; i >= 0; --i)
            if (f(m, mid - t * m, 1 << i, t - 1) < a[i])
                return false;
        return true;
    }
    Main()
    {
        cin >> n >> m;
        a.resize(n);
        for (auto &i : a)
            cin >> i;
        for (int i = n - 1; i >= 1; --i)
            a[i - 1] += a[i] * 2;
        i64 l = m, r = a[0] + m;
        while (l <= r)
        {
            auto mid = (l + r) / 2;
            if (check(mid))
                r = mid - 1;
            else
                l = mid + 1;
        }
        cout << l << '\n';
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

