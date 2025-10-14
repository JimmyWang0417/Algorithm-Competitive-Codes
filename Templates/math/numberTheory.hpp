template <typename T>
struct numberTheory
{
    constexpr static auto _mul = [](T a, T b, T m)
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
    };
    using functype = function<T(T, T, T)>;
    functype mul;
    numberTheory(const functype &other = _mul) : mul(other) {}
    auto exgcd(T a, T b) -> tuple<T, T, T>
    {
        if (b == 0)
            return {a, 1, 0};
        auto [d, y, x] = exgcd(b, a % b);
        return {d, x, y - (a / b) * x};
    }
    auto crt(const vector<pair<T, T>> &p)
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
    auto excrt(const vector<pair<T, T>> &p) -> T
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
    template <typename _T>
    auto pow(T a, _T b, T p)
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
    auto exlucas(T n, T m, T mod)
    {
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
    auto BSGS(T a, T n, T p) -> T
    {
        if (n == 1)
            return 0;
        unordered_map<T, T> mp;
        T res = n;
        int m = (int)::sqrt(p) + 1;
        for (int i = 0; i < m; ++i)
        {
            mp[res] = i;
            (res *= a) %= p;
        }
        T x = pow(a, m, p);
        res = 1;
        for (int i = 1; i <= m + 1; ++i)
        {
            (res *= x) %= p;
            if (mp.find(res) != mp.end())
                return i * m - mp[res];
        }
        return -1;
    }
    auto exBSGS(T a, T b, T p) -> T
    {
        a %= p, b %= p;
        if (b == 1 || p == 1)
            return 0;
        if (!b && !a)
            return 1;
        if (!a)
            return -1;
        if (!b)
        {
            T res = 0, d;
            while ((d = gcd(a, p)) != 1)
            {
                ++res;
                p /= d;
                if (p == 1)
                    return res;
            }
            return -1;
        }
        T res = 0, A = a, B = b, P = p, C = 1, d;
        while ((d = gcd(A, P)) != 1)
        {
            if (B % d)
                return -1;
            P /= d, B /= d;
            (C *= A / d) %= P;
            ++res;
            if (C == B)
                return res;
        }
        unordered_map<T, T> mp;
        T f = 1;
        int t = ::sqrt(P) + 1;
        for (int i = 0; i < t; i++)
        {
            mp[mul(f, B, P)] = i;
            (f *= A) %= P;
        }
        auto tf = f;
        (f *= C) %= P;
        for (int i = 1; i <= t; i++)
        {
            if (mp.find(f) != mp.end())
                return res + i * t - mp[f];
            (f *= tf) %= P;
        }
        return -1;
    }
    auto sqrt(T x, T p) -> pair<T, T>
    {
        if (x == 0)
            return {0, 0};
        if (pow(x, (p - 1) / 2, p) == p - 1)
            return {-1, -1};
        else
        {
            mt19937 rng(random_device{}());
            T r;
            while (1)
            {
                r = uniform_int_distribution<T>(1, p - 1)(rng);
                if (pow((r * r - x + p) % p, (p - 1) / 2, p) == p - 1)
                    break;
            }
            auto II = (r * r - x + p) % p;
            auto mulT = [&](const pair<T, T> &a, const pair<T, T> &b) -> pair<T, T>
            {
                return {
                    (a.first * b.first + a.second * b.second % p * II) % p,
                    (a.first * b.second + a.second * b.first) % p};
            };
            auto power = [&](pair<T, T> a, auto b)
            {
                pair<T, T> res(1, 0);
                while (b)
                {
                    if (b & 1)
                        res = mulT(res, a);
                    a = mulT(a, a);
                    b >>= 1;
                }
                return res;
            };
            auto root = power({r, 1}, (p + 1) / 2).first;
            root = min(root, (p - root) % p);
            return {root, (p - root) % p};
        }
    }
};