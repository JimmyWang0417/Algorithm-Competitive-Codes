#pragma once
#include "polynomial.hpp"
using namespace polynomial;
struct stirling
{
    static auto s1row(int n)
    {
        if (n == 0)
            return poly{1};
        if (n == 1)
            return poly{0, 1};
        auto F = s1row(n / 2);
        F = F * F.shift(n / 2);
        if (n & 1)
        {
            F.emplace_back();
            for (int i = n; i >= 1; --i)
                F[i] = (F[i - 1] + (n - 1) * F[i]) % mod;
        }
        return F;
    }
    static auto s1col(int n, int m)
    {
        vector<i64> fac(n + 1), ifac(n + 1);
        fac[0] = 1;
        for (int i = 1; i <= n; ++i)
            fac[i] = fac[i - 1] * i % mod;
        ifac[n] = quickpow(fac[n]);
        for (int i = n; i >= 1; --i)
            ifac[i - 1] = ifac[i] * i % mod;
        poly F(n + 1);
        for (int i = 1; i <= n; ++i)
            F[i] = fac[i - 1] * ifac[i] % mod;
        F = F.pow(m, m, m);
        for (int i = 0; i <= n; ++i)
            (F[i] *= fac[i] * ifac[m] % mod) %= mod;
        return F;
    }
    static auto s2row(int n)
    {
        vector<i64> fac(n + 1), ifac(n + 1);
        fac[0] = 1;
        for (int i = 1; i <= n; ++i)
            fac[i] = fac[i - 1] * i % mod;
        ifac[n] = quickpow(fac[n]);
        for (int i = n; i >= 1; --i)
            ifac[i - 1] = ifac[i] * i % mod;

        poly F(n + 1), G(n + 1);
        for (int i = 0; i <= n; ++i)
        {
            F[i] = (i & 1 ? -1 : 1) * ifac[i];
            G[i] = quickpow(i, n) * ifac[i] % mod;
        }
        F = F * G;
        F.resize(n + 1);
        return F;
    }
    static auto s2col(int n, int m)
    {
        vector<i64> fac(n + 1), ifac(n + 1);
        fac[0] = 1;
        for (int i = 1; i <= n; ++i)
            fac[i] = fac[i - 1] * i % mod;
        ifac[n] = quickpow(fac[n]);
        for (int i = n; i >= 1; --i)
            ifac[i - 1] = ifac[i] * i % mod;

        poly F(n + 1);
        for (int i = 1; i <= n; ++i)
            F[i] = ifac[i];
        F = F.pow(m, m, m);
        for (int i = 0; i <= n; ++i)
            (F[i] *= fac[i] * ifac[m] % mod) %= mod;
        return F;
    }
};
