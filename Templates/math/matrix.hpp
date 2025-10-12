struct matrix : public vector<vector<i64>>
{
    using vector<vector<i64>>::vector;
    matrix() = default;
    matrix(size_t n) : matrix(n, n) {}
    matrix(size_t n, size_t m) : vector(n, vector<i64>(m)) {}
    matrix(const vector<vector<i64>> &_g) : vector(_g) {}
    auto rows() const { return (int)size(); }
    auto columns() const { return (int)front().size(); }
    static auto I(size_t n)
    {
        matrix _(n, vector<i64>(n));
        for (int i = 0; i < (int)n; ++i)
            _[i][i] = 1;
        return _;
    }
    auto friend operator+(const matrix &lhs, const matrix &rhs)
    {
        matrix res(lhs);
        for (int i = 0; i < res.rows(); ++i)
            for (int j = 0; j < res.columns(); ++j)
                (res[i][j] += rhs[i][j]) %= mod;
        return res;
    }
    auto friend operator-(const matrix &lhs, const matrix &rhs)
    {
        matrix res(lhs);
        for (int i = 0; i < res.rows(); ++i)
            for (int j = 0; j < res.columns(); ++j)
                (res[i][j] -= rhs[i][j]) %= mod;
        return res;
    }
    auto friend operator*(const matrix &lhs, const matrix &rhs)
    {
        matrix res(lhs.rows(), rhs.columns());
        for (int i = 0; i < res.rows(); ++i)
            for (int k = 0; k < rhs.rows(); ++k)
                for (int j = 0; j < res.columns(); ++j)
                    (res[i][j] += lhs[i][k] * rhs[k][j]) %= mod;
        return res;
    }
    template <typename T>
    auto pow(T b) const
    {
        matrix res = I(size()), a = (*this);
        while (b)
        {
            if (b & 1)
                res = res * a;
            a = a * a;
            b >>= 1;
        }
        return res;
    }
    auto friend det(matrix A) -> i64
    {
        int n = A.rows();
        i64 res = 1;
        for (int i = 0; i < n; ++i)
        {
            int where = -1;
            for (int j = i; j < n; ++j)
                if (A[j][i])
                {
                    where = j;
                    break;
                }
            if (where == -1)
                return 0;
            if (where != i)
            {
                A[i].swap(A[where]);
                res = -res;
            }
            (res *= A[i][i]) %= mod;
            auto inv = quickpow(A[i][i], mod - 2);
            for (int j = i + 1; j < n; ++j)
            {
                auto t = A[j][i] * inv % mod;
                for (int k = i; k < n; ++k)
                    (A[j][k] -= A[i][k] * t) %= mod;
            }
        }
        return (res + mod) % mod;
    }
    auto inv() const
    {
        int n = (int)this->size();
        matrix A = (*this), B = I(n);
        for (int i = 0; i < n; ++i)
        {
            int where = -1;
            for (int j = i; j < n; ++j)
                if (A[j][i])
                {
                    where = j;
                    break;
                }
            if (where == -1)
                return matrix();

            A[i].swap(A[where]), B[i].swap(B[where]);
            auto inv = quickpow(A[i][i], mod - 2);
            for (int j = i; j < n; ++j)
                (A[i][j] *= inv) %= mod;
            for (int j = 0; j < n; ++j)
                (B[i][j] *= inv) %= mod;

            for (int j = i + 1; j < n; ++j)
            {
                auto t = A[j][i];
                for (int k = i; k < n; ++k)
                    (A[j][k] -= A[i][k] * t) %= mod;
                for (int k = 0; k < n; ++k)
                    (B[j][k] -= B[i][k] * t) %= mod;
            }
        }
        for (int i = n - 1; i >= 0; --i)
        {
            for (int j = i + 1; j < n; ++j)
                for (int k = 0; k < n; ++k)
                    (B[i][k] -= A[i][j] * B[j][k]) %= mod;
        }
        return B;
    }

    auto friend &operator>>(istream &in, matrix &p)
    {
        for (auto &i : p)
            for (auto &j : i)
                in >> j;
        return in;
    }
    auto friend &operator<<(ostream &out, const matrix &p)
    {
        for (const auto &i : p)
        {
            for (auto j : i)
                out << (j + mod) % mod << ' ';
            out << '\n';
        }
        return out;
    }
};