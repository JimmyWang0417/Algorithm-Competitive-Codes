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
constexpr int inv2 = quickpow(2);
constexpr auto lowbit = [](int x)
{ return x & (-x); };
struct Main
{
    template <typename T>
    auto FWT(int _n, vector<vector<T>> &dp)
    {
        for (int mid = 1; mid < (1 << _n); mid <<= 1)
            for (int i = 0; i < (1 << _n); i += mid << 1)
                for (int j = 0; j < mid; ++j)
                    for (int k = 0; k <= _n; ++k)
                        (dp[i + j + mid][k] += dp[i + j][k]) %= mod;
    }
    template <typename T>
    auto IFWT(int _n, vector<vector<T>> &dp)
    {
        for (int mid = 1; mid < (1 << _n); mid <<= 1)
            for (int i = 0; i < (1 << _n); i += mid << 1)
                for (int j = 0; j < mid; ++j)
                    for (int k = 0; k <= _n; ++k)
                        (dp[i + j + mid][k] -= dp[i + j][k]) %= mod;
    }
    auto comp(const vector<int> &F, const vector<int> &G) // F(G)
    {
        int n = (int)F.size() - 1;
        vector<i64> fac(n + 5);
        fac[0] = 1;
        for (int i = 1; i <= n; ++i)
            fac[i] = fac[i - 1] * i % mod;
        vector<vector<int>> f(n + 1, vector<int>(G.size()));
        for (int i = 0; i <= n; ++i)
            f[i][0] = (int)(fac[i] * F[i] % mod);
        vector<vector<int>> A(G.size(), vector<int>(n + 1));
        vector<vector<int>> B(G.size(), vector<int>(n + 1));
        for (int i = 0; i < n; ++i)
        {
            for (int j = n - i - 1; j >= 0; --j)
            {
                for (int S = 0; S < (1 << (i + 1)); ++S)
                {
                    fill(A[S].begin(), A[S].begin() + i + 2, 0);
                    fill(B[S].begin(), B[S].begin() + i + 2, 0);
                }
                for (int S = 0; S < (1 << i); ++S)
                    A[S][__builtin_popcount(S)] = f[j + 1][S];
                for (int S = 1 << i; S < (1 << (i + 1)); ++S)
                    B[S][__builtin_popcount(S)] = G[S];
                FWT(i + 1, A);
                FWT(i + 1, B);
                for (int S = 0; S < (1 << (i + 1)); ++S)
                {
                    vector<i64> C(i + 2);
                    for (int k = 0; k <= i + 1; ++k)
                        for (int l = 0; k + l <= i + 1; ++l)
                            (C[k + l] += (i64)A[S][k] * B[S][l]) %= mod;
                    for (int k = 0; k <= i + 1; ++k)
                        A[S][k] = (int)C[k];
                }
                IFWT(i + 1, A);
                for (int S = 1 << i; S < (1 << (i + 1)); ++S)
                    (f[j][S] += A[S][__builtin_popcount(S)]) %= mod;
            }
        }
        return f[0];
    }
    Main()
    {
        int n;
        cin >> n;
        vector<int> G(1 << n), F(n + 1);
        for (auto &i : G)
            cin >> i;
        for (auto &i : F)
            cin >> i;
        auto H = comp(F, G);
        for (auto &i : H)
            cout << (i + mod) % mod << ' ';
        cout << '\n';
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