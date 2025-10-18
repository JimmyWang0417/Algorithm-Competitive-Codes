struct Comb
{
    vector<i64> _fac, _ifac, _inv;
    auto init(int n)
    {
        int m = (int)_fac.size() - 1;
        if (n <= m)
            return;
        _fac.resize(n + 1), _ifac.resize(n + 1), _inv.resize(n + 1);
        for (int i = m + 1; i <= n; ++i)
        {
            _fac[i] = _fac[i - 1] * i % mod;
            _inv[i] = -mod / i * _inv[mod % i] % mod;
            _ifac[i] = _ifac[i - 1] * _inv[i] % mod;
        }
    }
    auto fac(int n)
    {
        init(n);
        return _fac[n];
    }
    auto ifac(int n)
    {
        init(n);
        return _fac[n];
    }
    auto inv(int n)
    {
        init(n);
        return _inv[n];
    }
    auto C(int n, int m) -> i64
    {
        if (m < 0 || n < m)
            return 0;
        init(n);
        return _fac[n] * _ifac[m] % mod * _ifac[n - m] % mod;
    }
    auto A(int n, int m) -> i64
    {
        if (m < 0 || n < m)
            return 0;
        init(n);
        return _fac[n] * _ifac[n - m] % mod;
    }
    Comb(int n = 0) : _fac({1, 1}), _ifac({1, 1}), _inv({0, 1}) { init(n); }
} comb;
