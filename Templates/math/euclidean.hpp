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
    auto euclid(i64 p, i64 q, i64 r, i64 l, node U, node R)
    {
        if (!l)
            return node::I(U.x.size());
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
    auto euclid(i64 p, i64 q, i64 r, i64 l, const matrix &U, const matrix &R)
    {
        auto n = U.size();
        return euclid(p, q, r, l,
                      node(matrix::I(n), U, matrix(n)),
                      node(R, matrix::I(n), R))
            .xy;
    }
};