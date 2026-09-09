struct comb
{
    vector<i64> fac, ifac;
    comb(int n) : fac(n + 1), ifac(n + 1)
    {
        fac[0] = 1;
        for (int i = 1; i <= n; ++i)
            fac[i] = fac[i - 1] * i % mod;
        ifac[n] = quickpow(fac[n]);
        for (int i = n; i >= 1; --i)
            ifac[i - 1] = ifac[i] * i % mod;
    }
    auto C(int n, int m) -> i64
    {
        if (m < 0 || n < m)
            return 0;
        return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
    }
    auto A(int n, int m) -> i64
    {
        if (m < 0 || n < m)
            return 0;
        return fac[n] * ifac[n - m] % mod;
    }
};
