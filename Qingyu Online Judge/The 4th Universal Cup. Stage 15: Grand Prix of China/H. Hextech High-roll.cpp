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
    int m, n;
    vector<int> a, b;
    vector<f80> logfac;
    auto logC(int _n, int _m)
    {
        return logfac[_n] - logfac[_m] - logfac[_n - _m];
    }
    Main()
    {
        cin >> m >> n;

        logfac.resize(n + 5);
        logfac[0] = 0;
        for (int i = 1; i <= n; ++i)
            logfac[i] = logfac[i - 1] + log(i);

        a.resize(m);
        b.resize(n);
        for (auto &i : a)
            cin >> i;
        for (auto &i : b)
            cin >> i;
        ranges::sort(a);
        ranges::sort(b);
        vector<i64> suf(b.size() + 1);
        for (int i = (int)b.size() - 1; i >= 0; --i)
            suf[i] = suf[i + 1] + b[i];
        cout << fixed << setprecision(10);
        if (m == 1)
        {
            cout << max((f80)suf[0] / n, (f80)a.back());
            return;
        }
        f80 res = 0;
        for (int i = m - 2; i < (int)b.size(); ++i)
        {
            auto P = exp(logC(i, m - 2) - logC(n, m - 1));
            res += P * max((f80)((i64)((i + 1) - m + 1) * b[i] + suf[i + 1]) / (n - m + 1), (f80)a.back());
        }
        cout << res << '\n';
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
