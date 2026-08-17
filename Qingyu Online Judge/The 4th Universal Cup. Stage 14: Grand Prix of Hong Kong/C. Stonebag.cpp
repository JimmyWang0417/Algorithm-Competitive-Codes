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
vector<i64> fac, ifac;
auto quickpow(i64 a, int b)
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
auto init(int n)
{
    fac.resize(n + 5);
    ifac.resize(n + 5);
    fac[0] = 1;
    for (int i = 1; i <= n; ++i)
        fac[i] = fac[i - 1] * i % mod;
    ifac[n] = quickpow(fac[n], mod - 2);
    for (int i = n; i >= 1; --i)
        ifac[i - 1] = ifac[i] * i % mod;
}
auto C(int n, int m) -> i64
{
    if (n < 0 || n < m)
        return 0;
    return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}
struct Main
{
    int n;
    i64 S;
    vector<int> a;
    auto all()
    {
        // ∑bi<=S
        i64 res = ifac[n];
        for (int i = 0; i < n; ++i)
            (res *= (n + S - i) % mod) %= mod;
        return res;
    }
    auto except()
    {
        // ∑bi=S-d
        // bi<n-d
        i64 res = 0;
        for (int d = 0; d < n && d <= S; ++d)
            if ((i64)n * (n - d) >= S - d)
            {
                for (int i = 0; i <= n; ++i)
                {
                    const auto t = (int)(S - d - (i64)i * (n - d));
                    if (t >= 0)
                        (res += (i & 1 ? -1 : 1) * C(n, i) * C(n + t - 1, n - 1)) %= mod;
                }
            }
        return res;
    }
    auto irregular()
    {
        // ∑bi=S-d
        // bi<n-d
        // bi<=ai
        vector<int> dp(n + 1);
        dp[0] = 1;
        auto mul = [&](int x)
        {
            for (int i = n; i >= x; --i)
                (dp[i] -= dp[i - x]) %= mod;
        };
        auto div = [&](int x)
        {
            for (int i = x; i <= n; ++i)
                (dp[i] += dp[i - x]) %= mod;
        };
        int off = 0;
        for (int &x : a)
        {
            if (x > n)
            {
                off += x;
                if (off > n)
                    break;
                x = n;
            }
            mul(x + 1);
            div(1);
        }
        i64 res = 0;
        if (off <= n)
        {
            for (int d = 0; d < n; ++d)
            {
                for (int &x : a)
                {
                    while (x >= n - d)
                    {
                        ++off;
                        if (off > n)
                            break;
                        div(x + 1);
                        mul(x);
                        --x;
                    }
                    if (off > n)
                        break;
                }
                if (off > n)
                    break;
                if (d >= off)
                    (res += dp[d - off]) %= mod;
            }
        }
        return res;
    }
    Main() : S(0)
    {
        cin >> n;
        a.resize(n);
        for (int &i : a)
        {
            cin >> i;
            S += i;
        }
        cout << ((all() - except() + irregular()) % mod + mod) % mod << '\n';
    }
};
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    init(1e7);
    int T = 1;
    // cin >> T;
    while (T--)
        Main();
    return 0;
}

