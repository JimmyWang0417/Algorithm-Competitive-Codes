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
namespace comb
{
    vector<i64> fac, ifac;
    auto init(int n)
    {
        fac.resize(n + 5);
        ifac.resize(n + 5);
        fac[0] = 1;
        for (int i = 1; i <= n; ++i)
            fac[i] = fac[i - 1] * i % mod;
        ifac[n] = quickpow(fac[n]);
        for (int i = n; i >= 1; --i)
            ifac[i - 1] = ifac[i] * i % mod;
    }
    auto C(int n, int m)
    {
        return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
    }
    auto invC(int n, int m)
    {
        return ifac[n] * fac[m] % mod * ifac[n - m] % mod;
    }
}
using namespace comb;
struct Main
{
    int n, A, B;
    string s, t;
    vector<int> a;
    Main()
    {
        cin >> n >> A >> B;
        cin >> s >> t;
        int ls = (int)ranges::count(s, '0');
        int lt = (int)ranges::count(t, '0');
        double res = n;
        for (int i = 0; i < n; ++i)
            if (s[i] == '0' && t[i] == '0')
                res -= (double)(ls - A) / ls * (lt - B) / lt; 
        cout << fixed << setprecision(9) << res << '\n';
    }
};
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    init(5e6);
    int T = 1;
    // cin >> T;
    while (T--)
        Main();
    return 0;
}
