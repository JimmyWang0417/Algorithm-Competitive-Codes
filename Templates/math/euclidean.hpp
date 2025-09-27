struct euclidean
{
    struct matrix
    {
        vector<vector<int>> g;
        matrix() = default;
        matrix(int n) : g(n, vector<int>(n)) {}
        auto size() const { return (int)g.size(); }
        const auto &operator[](int x) const { return g[x]; }
        auto &operator[](int x) { return g[x]; }
        static auto I(int n)
        {
            matrix res(n);
            for (int i = 0; i < n; ++i)
                res[i][i] = 1;
            return res;
        }
        auto friend operator+(const matrix &lhs, const matrix &rhs)
        {
            matrix res(lhs.size());
            for (int i = 0; i < res.size(); ++i)
                for (int j = 0; j < res.size(); ++j)
                    res[i][j] = (lhs[i][j] + rhs[i][j]) % mod;
            return res;
        }
        auto friend operator*(const matrix &lhs, const matrix &rhs)
        {
            matrix res(lhs.size());
            for (int i = 0; i < res.size(); ++i)
                for (int k = 0; k < res.size(); ++k)
                    for (int j = 0; j < res.size(); ++j)
                        res[i][j] = (int)((res[i][j] + (i64)lhs[i][k] * rhs[k][j]) % mod);
            return res;
        }
        auto friend &operator>>(istream &in, matrix &p)
        {
            for (auto &i : p.g)
                for (auto &j : i)
                    in >> j;
            return in;
        }
        auto friend &operator<<(ostream &out, const matrix &p)
        {
            for (const auto &i : p.g)
            {
                for (auto j : i)
                    out << j << ' ';
                out << '\n';
            }
            return out;
        }
    };
    struct node
    {
        matrix x, y, xy;
        node() = default;
        node(int n) : x(matrix::I(n)), y(matrix::I(n)), xy(n) {}
        auto operator*(const node &rhs) const
        {
            node res;
            res.x = x * rhs.x;
            res.y = y * rhs.y;
            res.xy = xy + x * rhs.xy * y;
            return res;
        }
        auto pow(i64 b) const
        {
            node res(x.size()), a = (*this);
            while (b)
            {
                if (b & 1)
                    res = res * a;
                a = a * a;
                b >>= 1;
            }
            return res;
        }
    };
    auto euclid(i64 p, i64 q, i64 r, i64 l, node U, node R)
    {
        if (!l)
            return node(U.x.size());
        if (r >= q)
            return (U.pow(p / q)) * euclid(p, q, l, r % q, U, R);
        if (p >= q)
            return euclid(p % q, q, r, l, U, (U.pow(p / q)) * R);
        i64 m = ((i128)p * l + r) / q;
        if (!m)
            return R.pow(l);
        return (R.pow((q - r - 1) / p)) * U * euclid(q, p, (q - r - 1) % p, m - 1, R, U) *
               (R.pow(l - ((i128)q * m - r - 1) / p));
    }
};