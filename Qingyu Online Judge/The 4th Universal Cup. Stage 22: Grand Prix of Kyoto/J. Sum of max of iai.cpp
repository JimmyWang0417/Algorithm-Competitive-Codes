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
// constexpr int mod = 998244353;
template <typename T>
constexpr auto quickpow(i64 a, T b, int mod)
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
    int n, p;
    Main()
    {
        cin >> n >> p;
        vector<int> cnt(n * n + 1e4 + 5), ub(n + 5), pv(n * n / 2 + 1e4 + 5);
        vector<int> inv(n + 5);
        for (int i = 1; i <= n; i++)
        {
            ub[i] = i;
            for (int j = n; j > n - i; j--)
                cnt[i * j]++;
        }
        for (int i = 1; i <= n * n + 1; i++)
            cnt[i] += cnt[i - 1];
        for (int i = 1; i <= n; i++)
            for (int j = n; j > n - i; j--)
                pv[cnt[i * j]--] = i;
        int fac = 1;
        inv[0] = inv[1] = 1;
        for (int i = 2; i <= n; i++)
            inv[i] = 1ll * (p - p / i) * inv[p % i] % p, fac = 1ll * fac * i % p;
        int ans = 1ll * (n * n + 1) * fac % p, res = fac;
        for (int i = n * n, j = cnt[n * n + 1]; res; i--)
        {
            (ans += p - res) >= p && (ans -= p);
            while (--cnt[i + 1] >= cnt[i])
            {
                int &x = ub[pv[j--]];
                res = 1ll * res * inv[x] % p;
                res = 1ll * res * --x % p;
            }
        }
        cout << ans << '\n';
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
