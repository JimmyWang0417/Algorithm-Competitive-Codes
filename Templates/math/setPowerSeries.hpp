#pragma once
#include <vector>

template <int mod = 998244353>
struct setPowerSeries
{
    using i64 = long long;

    static auto norm(i64 x)
    {
        x %= mod;
        if (x < 0)
            x += mod;
        return (int)x;
    }

    static auto popcount(int x)
    {
        return __builtin_popcount((unsigned)x);
    }

    static auto fwt(int n, std::vector<std::vector<int>> &a)
    {
        for (int mid = 1; mid < (1 << n); mid <<= 1)
            for (int i = 0; i < (1 << n); i += mid << 1)
                for (int j = 0; j < mid; ++j)
                    for (int k = 0; k <= n; ++k)
                        a[i + j + mid][k] = norm(a[i + j + mid][k] + a[i + j][k]);
    }

    static auto ifwt(int n, std::vector<std::vector<int>> &a)
    {
        for (int mid = 1; mid < (1 << n); mid <<= 1)
            for (int i = 0; i < (1 << n); i += mid << 1)
                for (int j = 0; j < mid; ++j)
                    for (int k = 0; k <= n; ++k)
                        a[i + j + mid][k] = norm(a[i + j + mid][k] - a[i + j][k]);
    }

    static auto subsetConv(int n, const std::vector<int> &a, const std::vector<int> &b)
    {
        int lim = 1 << n;
        std::vector<std::vector<int>> A(lim, std::vector<int>(n + 1));
        std::vector<std::vector<int>> B(lim, std::vector<int>(n + 1));
        std::vector<std::vector<int>> C(lim, std::vector<int>(n + 1));
        for (int S = 0; S < lim; ++S)
        {
            A[S][popcount(S)] = norm(a[S]);
            B[S][popcount(S)] = norm(b[S]);
        }
        fwt(n, A), fwt(n, B);
        for (int S = 0; S < lim; ++S)
            for (int i = 0; i <= n; ++i)
                for (int j = 0; i + j <= n; ++j)
                    C[S][i + j] = (C[S][i + j] + (i64)A[S][i] * B[S][j]) % mod;
        ifwt(n, C);
        std::vector<int> res(lim);
        for (int S = 0; S < lim; ++S)
            res[S] = C[S][popcount(S)];
        return res;
    }

    static auto comp(const std::vector<int> &F, const std::vector<int> &G)
    {
        int n = (int)F.size() - 1, lim = 1 << n;
        std::vector<int> fac(n + 1, 1);
        for (int i = 1; i <= n; ++i)
            fac[i] = (i64)fac[i - 1] * i % mod;

        std::vector<std::vector<int>> f(n + 1, std::vector<int>(lim));
        for (int i = 0; i <= n; ++i)
            f[i][0] = (i64)fac[i] * norm(F[i]) % mod;

        for (int i = 0; i < n; ++i)
        {
            int m = 1 << (i + 1), half = 1 << i;
            for (int j = n - i - 1; j >= 0; --j)
            {
                std::vector<std::vector<int>> A(m, std::vector<int>(i + 2));
                std::vector<std::vector<int>> B(m, std::vector<int>(i + 2));
                for (int S = 0; S < half; ++S)
                    A[S][popcount(S)] = f[j + 1][S];
                for (int S = half; S < m; ++S)
                    B[S][popcount(S)] = norm(G[S]);
                fwt(i + 1, A), fwt(i + 1, B);
                for (int S = 0; S < m; ++S)
                {
                    std::vector<int> C(i + 2);
                    for (int k = 0; k <= i + 1; ++k)
                        for (int l = 0; k + l <= i + 1; ++l)
                            C[k + l] = (C[k + l] + (i64)A[S][k] * B[S][l]) % mod;
                    A[S] = C;
                }
                ifwt(i + 1, A);
                for (int S = half; S < m; ++S)
                    f[j][S] = norm(f[j][S] + A[S][popcount(S)]);
            }
        }
        return f[0];
    }
};
