#include <bits/stdc++.h>
#include <cassert>
using namespace std;
typedef int64_t i64;
typedef uint64_t u64;
typedef __int128_t i128;
typedef __uint128_t u128;
typedef __float80 f80;
typedef __float128 f128;
constexpr int mod = 998244353;
constexpr int g = 3;
constexpr int l2 = 640079066;
constexpr int l3 = 1;
template <typename T>
constexpr auto quickpow(i64 a, T b)
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
template <int _mod>
struct matrix
{
    i64 g[3][3];
    constexpr auto operator*(const matrix &rhs) const
    {
        matrix res{};
        for (int i = 0; i < 3; ++i)
            for (int k = 0; k < 3; ++k)
                for (int j = 0; j < 3; ++j)
                    (res.g[i][j] += g[i][k] * rhs.g[k][j]) %= _mod;
        return res;
    }
    constexpr static auto I()
    {
        matrix f{};
        f.g[0][0] = f.g[1][1] = f.g[2][2] = 1;
        return f;
    }
    template <typename T>
    constexpr auto pow(T rhs) const
    {
        matrix res(I()), a(*this);
        while (rhs)
        {
            if (rhs & 1)
                res = res * a;
            a = a * a;
            rhs >>= 1;
        }
        return res;
    }
};
struct Main
{
    i64 n;
    Main()
    {
        cin >> n;
        matrix<mod - 1> a;
        a.g[0][0] = 0, a.g[0][1] = 1, a.g[0][2] = 1;
        a.g[1][0] = 1, a.g[1][1] = 1, a.g[1][2] = 0;
        a.g[2][0] = 0, a.g[2][1] = 0, a.g[2][2] = 1; 
        auto b = a.pow(n);
        auto c = (l2 * b.g[0][2] + l3 * b.g[1][2]) % (mod - 1);
        cout << quickpow(g, c) << '\n';
    }
};
signed main()
{
    // freopen("project.in", "r", stdin);
    // freopen("project.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--)
        Main();
    return 0;
}