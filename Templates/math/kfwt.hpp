template <int q>
struct cyclotomic : array<i64, q - 1> // q is prime
{
    cyclotomic(i64 x = 0)
    {
        this->fill(0), this->front() = x % mod;
    }
    auto &operator+=(const cyclotomic &rhs)
    {
        for (int i = 0; i < q - 1; ++i)
            ((*this)[i] += rhs[i]) %= mod;
        return *this;
    }
    auto operator*(const cyclotomic &rhs) const
    {
        array<i64, q> f{};
        for (int i = 0; i < q - 1; ++i)
            for (int j = 0; j < q - 1; ++j)
                (f[(i + j) % q] += (*this)[i] * rhs[j]) %= mod;
        cyclotomic res;
        for (int i = 0; i < q - 1; ++i)
            res[i] = (f[i] - f[q - 1]) % mod;
        return res;
    }
    auto &operator*=(const cyclotomic &rhs)
    {
        return *this = *this * rhs;
    }
    auto &operator%=(i64)
    {
        for (auto &x : *this)
            x %= mod;
        return *this;
    }
    static auto root(bool inv = false)
    {
        cyclotomic res;
        if (inv)
            res.fill(-1);
        else if constexpr (q == 2)
            res[0] = -1;
        else
            res[1] = 1;
        return res;
    }
};
template <int q, typename T = i64>
struct kfwt
{
    using row = array<T, q>;
    using matrix = array<row, q>;
    template <typename F>
    static auto FWT(vector<T> &dp, F calc)
    {
        row f;
        for (int mid = 1; mid < (int)dp.size(); mid *= q)
            for (int i = 0; i < (int)dp.size(); i += mid * q)
                for (int j = 0; j < mid; ++j)
                {
                    for (int k = 0; k < q; ++k)
                        f[k] = dp[i + j + k * mid];
                    calc(f);
                    for (int k = 0; k < q; ++k)
                        dp[i + j + k * mid] = f[k];
                }
    }
    static auto FWT(vector<T> &dp, const matrix &mat)
    {
        return FWT(dp, [&](auto &f)
                   {
            row g{};
            for (int i = 0; i < q; ++i)
                for (int j = 0; j < q; ++j)
                    (g[j] += f[i] * mat[i][j]) %= mod;
            f = g; });
    }
    static auto xorMatrix(T w, T coef = 1)
    {
        matrix mat{};
        T wi = 1;
        for (int i = 0; i < q; ++i, (wi *= w) %= mod)
        {
            T x = coef;
            for (int j = 0; j < q; ++j, (x *= wi) %= mod)
                mat[i][j] = x;
        }
        return mat;
    }
};
