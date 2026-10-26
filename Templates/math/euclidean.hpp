struct euclidean
{
    struct node
    {
        matrix x, y, xy;
        node() = default;
        node(const matrix &_x, const matrix &_y, const matrix &_xy) : x(_x), y(_y), xy(_xy) {}
        static auto I(size_t n)
        {
            return node(matrix::I(n), matrix::I(n), matrix(n));
        }
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
            node res = I(x.size()), a = (*this);
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
    static node euclid(i64 a, i64 b, i64 c, i64 n, node U, node R)
    {
        if (b >= c)
            return (U.pow(b / c)) * euclid(a, b % c, c, n, U, R);
        if (a >= c)
            return euclid(a % c, b, c, n, U, (U.pow(a / c)) * R);
        i64 m = (i64)(((i128)a * n + b) / c);
        if (!m)
            return R.pow(n);
        return (R.pow((c - b - 1) / a)) * U * euclid(c, (c - b - 1) % a, a, m - 1, R, U) *
               (R.pow(n - (i64)(((i128)c * m - b - 1) / a)));
    }
    static auto euclid(i64 a, i64 b, i64 c, i64 n, const matrix &U, const matrix &R)
    {
        auto size = U.size();
        return euclid(a, b, c, n,
                      node(matrix::I(size), U, matrix(size)),
                      node(R, matrix::I(size), R))
            .xy;
    }
};
