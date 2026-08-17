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
    vector<int> a;
    Main()
    {
        cin >> n;
        a.resize(n + 5);
        for (int i = 1; i <= n; ++i)
            cin >> a[i];
        if (is_sorted(a.begin() + 1, a.begin() + 1 + n))
        {
            cout << "0\n";
            return;
        }
        const auto invn = quickpow(n), invn1 = quickpow(n - 1);
        i64 res = 0;
        for (int i = 1; i <= n; ++i)
        {
            vector<int> b(n + 5);
            for (int j = i + 1; j <= n; ++j)
                b[a[j]] = true;
            vector<i64> A(n + 5), B(n + 5);
            vector<vector<i64>> dp(n + 5, vector<i64>(n + 5));
            for (int len = 2; len <= n; ++len)
                for (int l = 1, r; (r = l + len - 1) <= n; ++l)
                    if (b[l] == 1 && b[r] == 0)
                    {
                        dp[l][r] = (A[l] + B[r] + n) * invn1 % mod;
                        (A[l] += dp[l][r]) %= mod;
                        (B[r] += dp[l][r]) %= mod;
                    }
            int L = n + 1, R = 0;
            for (int j = 1; j <= n; ++j)
                if (b[j] == 1)
                {
                    L = j;
                    break;
                }
            for (int j = n; j >= 1; --j)
                if (b[j] == 0)
                {
                    R = j;
                    break;
                }
            (res += dp[L][R] * invn) %= mod;
        }
        cout << ((res + 1) % mod + mod) % mod  << '\n';
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

