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
struct comb
{
    static inline vector<i64> fac, ifac, inv;
    static auto init(int n)
    {
        fac.resize(n + 1), ifac.resize(n + 1);
        inv.resize(n + 1);
        inv[1] = 1;
        for (int i = 2; i <= n; ++i)
            inv[i] = (-mod / i) * inv[mod % i] % mod;
        fac[0] = 1;
        for (int i = 1; i <= n; ++i)
            fac[i] = fac[i - 1] * i % mod;
        ifac[n] = quickpow(fac[n]);
        for (int i = n; i >= 1; --i)
            ifac[i - 1] = ifac[i] * i % mod;
    }
    static auto C(int n, int m)
    {
        return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
    }
    static auto invC(int n, int m)
    {
        return ifac[n] * fac[m] % mod * fac[n - m] % mod;
    }
    static auto A(int n, int m)
    {
        return fac[n] * ifac[n - m] % mod;
    }
    static auto invA(int n, int m)
    {
        return ifac[n] * fac[n - m] % mod;
    }
};
struct Main
{
    int n, m;
    Main()
    {
        cin >> n >> m;
        i64 res = 0;
        for (int i = 0; i <= n - m; ++i)
            (res += ((i & 1) ? -1 : 1) * comb::C(n - m, i) * quickpow(n - i - 1, n - 1)) %= mod;
        (res *= n - 1) %= mod;
        (res *= comb::C(n, m)) %= mod;
        cout << (res + mod) % mod << '\n';
    }
};
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    comb::init(5e6);
    cin >> T;
    while (T--)
        Main();
    return 0;
}
