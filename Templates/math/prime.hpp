template <typename T>
struct prime
{
    constexpr static auto _mul = [](T a, T b, T m)
    {
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
    constexpr static int test_time = 10;
    using functype = function<T(T, T, T)>;
    functype mul;
    prime(const functype &other = _mul) : mul(other) {}
    template <typename _T>
    auto pow(T a, _T b, T p)
    {
        T res = 1;
        while (b)
        {
            if (b & 1)
                res = mul(res, a, p);
            a = mul(a, a, p);
            b >>= 1;
        }
        return res;
    };
    auto millerRabin(T n)
    {
        if (n < 3 || n % 2 == 0)
            return n == 2;
        if (n % 3 == 0)
            return n == 3;
        T u = n - 1;
        int t = 0;
        while (u % 2 == 0)
        {
            u /= 2;
            ++t;
        }
        for (int i = 0; i < test_time; ++i)
        {
            auto a = uniform_int_distribution<T>(2, n - 2)(rnd), v = pow(a, u, n);
            if (v == 1)
                continue;
            for (int s = 0; s < t; ++s)
            {
                if (v == n - 1)
                    break;
                v = mul(v, v, n);
            }
            if (v != n - 1)
                return false;
        }
        return true;
    }
    auto pollardRho(T x)
    {
        T s = 0, t = 0;
        T c = uniform_int_distribution<T>(1, x - 1)(rnd);
        T val = 1;
        for (int goal = 1;; goal *= 2, s = t, val = 1)
        {
            for (int step = 1; step <= goal; ++step)
            {
                t = (mul(t, t, x) + c) % x;
                val = mul(val, abs(t - s), x);
                if ((step % 127) == 0)
                {
                    T d = gcd(val, x);
                    if (d > 1)
                        return d;
                }
            }
            T d = gcd(val, x);
            if (d > 1)
                return d;
        }
    }
    auto factor(T n)
    {
        vector<T> res;
        function<void(T, int)> fac = [&](T x, int times)
        {
            if (x == 1)
                return;
            if (millerRabin(x))
            {
                for (int i = 0; i < times; ++i)
                    res.push_back(x);
                return;
            }
            T p = x;
            while (p == x)
                p = pollardRho(x);
            int cnt = 0;
            while (x % p == 0)
            {
                x /= p;
                ++cnt;
            }
            fac(x, times), fac(p, times * cnt);
        };
        fac(n, 1);
        sort(res.begin(), res.end());
        return res;
    }
};