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
auto quickpow(i64 a, T b = mod - 2)
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
vector<int> rk;
int len = 1, limit = 0;
auto init(int m)
{
    limit = 1, len = 0;
    while (limit < m)
    {
        limit <<= 1;
        ++len;
    }
    rk.resize(limit);
    for (int i = 0; i < limit; ++i)
        rk[i] = (rk[i >> 1] >> 1) | ((i & 1) << (len - 1));
}
typedef complex<double> point;
typedef vector<complex<double>> poly;

auto FFT(poly &dp)
{
    for (int i = 0; i < limit; ++i)
        if (i < rk[i])
            swap(dp[i], dp[rk[i]]);
    for (int mid = 1; mid < limit; mid <<= 1)
    {
        const auto gn = polar(1.0, M_PI / mid);
        for (int i = 0; i < limit; i += mid << 1)
        {
            point g(1, 0);
            for (int j = 0; j < mid; ++j, g *= gn)
            {
                auto x = dp[i + j], y = dp[i + j + mid] * g;
                dp[i + j] = x + y;
                dp[i + j + mid] = x - y;
            }
        }
    }
}
auto IFFT(poly &dp)
{
    for (int i = 0; i < limit; ++i)
        if (i < rk[i])
            swap(dp[i], dp[rk[i]]);
    for (int mid = 1; mid < limit; mid <<= 1)
    {
        const auto gn = polar(1.0, -M_PI / mid);
        for (int i = 0; i < limit; i += mid << 1)
        {
            point g(1, 0);
            for (int j = 0; j < mid; ++j, g *= gn)
            {
                auto x = dp[i + j], y = dp[i + j + mid] * g;
                dp[i + j] = (x + y) / 2.0;
                dp[i + j + mid] = (x - y) / 2.0;
            }
        }
    }
}
auto operator*(poly lhs, poly rhs)
{
    int up = (int)(lhs.size() + rhs.size() - 1);
    init(up);
    lhs.resize(limit), rhs.resize(limit);
    FFT(lhs), FFT(rhs);
    for (int i = 0; i < limit; ++i)
        lhs[i] *= rhs[i];
    IFFT(lhs), lhs.resize(up);
    return lhs;
}
struct Main
{
    int n;
    string a, b, c;
    auto solve(char col)
    {
        vector<int> sufa(n + 5), sufb(n + 5), sufc(n + 5);
        for (int i = n; i >= 1; --i)
        {
            sufa[i] = sufa[i + 1] + (a[i - 1] == col);
            sufb[i] = sufb[i + 1] + (b[i - 1] == col);
            sufc[i] = sufc[i + 1] + (c[i - 1] == col);
        }
        i64 res = 0;
        for (int i = 1; i <= n; ++i)
        {
            if (a[i - 1] == col)
                res += (i64)sufb[max(i, n - i)] * sufc[max(i, n - i)];
            if (b[i - 1] == col)
                res += (i64)sufa[max(i + 1, n - i)] * sufc[max(i, n - i)];
            if (c[i - 1] == col)
                res += (i64)sufa[max(i + 1, n - i)] * sufb[max(i + 1, n - i)];
        }
        poly X(n + 1), Y(n + 1);
        for (int i = 1; i <= n; ++i)
        {
            X[i] = (a[i - 1] == col);
            Y[i] = (b[i - 1] == col);
        }
        auto Z = X * Y;
        for (int i = 1; i <= n; ++i)
            if (c[i - 1] == col)
                res -= (int)round(Z[2 * n - i].real());
        return res;
    }
    Main()
    {
        cin >> n;
        cin >> a >> b >> c;
        cout << solve('0') + solve('1') << '\n';
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
