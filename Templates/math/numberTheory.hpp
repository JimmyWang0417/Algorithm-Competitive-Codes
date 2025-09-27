template <typename T>
struct numberTheory
{
    static auto _mul(T a, T b, T m)
    {
        a = (a % m + m) % m, b = (b % m + m) % m;
        T res = 0;
        while (b)
        {
            if (b & 1)
                (res += a) %= m;
            (a += a) %= m;
            b >>= 1;
        }
        return res;
    }
    auto exgcd(T a, T b) -> tuple<T, T, T>
    {
        if (b == 0)
            return {a, 1, 0};
        auto [d, y, x] = exgcd(b, a % b);
        return {d, x, y - (a / b) * x};
    }
    auto crt(const vector<pair<T, T>> &p, const function<T(T, T, T)> &mul = _mul)
    {
        T res = 0, m = 1;
        for (auto [a, b] : p)
            m *= a;
        for (auto [a, b] : p)
        {
            auto mi = m / a;
            auto [d, x, y] = exgcd(mi, a);
            (res += mul(mul(x, mi, m), b, m)) %= m;
        }
        return (res + m) % m;
    }
    auto excrt(const vector<pair<T, T>> &p, const function<T(T, T, T)> &mul = _mul) -> T
    {
        auto [c, d] = p.front();
        for (int i = 1; i < (int)p.size(); ++i)
        {
            auto [a, b] = p[i];
            auto [g, x, y] = exgcd(a, c);
            c = c / g * a;
            if ((d - b) % g)
                return -1;
            d = (mul(mul(a, x, c), (d - b) / g, c) + b) % c;
        }
        return (d + c) % c;
    }
    auto lucas(T n, T m, T p) // (p - 1) * (p - 1) <= TMAX
    {
        vector<T> fac(p), ifac(p);
        fac[0] = 1;
        for (int i = 1; i < p; ++i)
            fac[i] = fac[i - 1] * i % p;
        ifac[p - 1] = get<1>(exgcd(fac[p - 1], p));
        for (int i = (int)p - 1; i >= 1; --i)
            ifac[i - 1] = ifac[i] * i % p;
        function<T(T, T)> C = [&](T x, T y) -> T
        {
            if (x < y)
                return 0;
            if (y == 0)
                return 1;
            if (x < p)
                return fac[x] * ifac[y] % p * ifac[x - y] % p;
            return C(x / p, y / p) * C(x % p, y % p) % p;
        };
        return (C(n, m) + p) % p;
    }
    auto exlucas(T n, T m, T mod)
    {
        auto pow = [](T a, T b, T p)
        {
            T res = 1;
            while (b)
            {
                if (b & 1)
                    (res *= a) %= p;
                (a *= a) %= p;
                b >>= 1;
            }
            return res;
        };
        auto g = [&](T x, T p)
        {
            T res = 0;
            while (x >= p)
                res += (x /= p);
            return res;
        };
        function<T(T, T, T)> fac = [&](T x, T p, T pk) -> T
        {
            if (x == 0)
                return 1;
            T res = 1;
            for (int i = 2; i <= pk; ++i)
                if (i % p)
                    (res *= i) %= pk;
            res = pow(res, x / pk, pk);
            for (int i = 2; i <= x % pk; ++i)
                if (i % p)
                    (res *= i) %= pk;
            return res * fac(x / p, p, pk) % pk;
        };
        vector<pair<T, T>> que;
        for (int p = 2; p * p <= mod; ++p)
            if (mod % p == 0)
            {
                T pk = 1;
                do
                {
                    pk *= p;
                    mod /= p;
                } while (mod % p == 0);
                auto res = fac(n, p, pk);
                (res *= get<1>(exgcd(fac(m, p, pk), pk))) %= pk;
                (res *= get<1>(exgcd(fac(n - m, p, pk), pk))) %= pk;
                (res *= pow(p, g(n, p) - g(m, p) - g(n - m, p), pk) % pk) %= pk;
                que.emplace_back(pk, res);
            }
        if (mod > 1)
        {
            auto p = mod, pk = mod;
            auto res = fac(n, p, pk);
            (res *= get<1>(exgcd(fac(m, p, pk), pk))) %= pk;
            (res *= get<1>(exgcd(fac(n - m, p, pk), pk))) %= pk;
            (res *= pow(p, g(n, p) - g(m, p) - g(n - m, p), pk) % pk) %= pk;
            que.emplace_back(pk, res);
        }
        return crt(que, [](T a, T b, T p)
                   { return a * b % p; });
    }
};