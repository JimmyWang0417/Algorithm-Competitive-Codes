#pragma once
template<class T>
constexpr auto mul(T a, T b, T m) -> T
{
    if constexpr (sizeof(T) <= sizeof(int))
    {
        i64 r = (i64)a * b % m;
        ((r %= m) += m) %= m;
        return (T)r;
    }
    else if constexpr (sizeof(T) <= sizeof(i64))
    {
        i128 r = (i128)a * b % m;
        ((r %= m) += m) %= m;
        return (T)r;
    }
    else
    {
        ((a %= m) += m) %= m;
        ((b %= m) += m) %= m;
        T r = 0;
        while (b)
        {
            if (b & 1)
                r = r >= m - a ? r - (m - a) : r + a;
            a = a >= m - a ? a - (m - a) : a + a;
            b >>= 1;
        }
        return r;
    }
}
template<class T>
struct mul_op
{
    constexpr auto operator()(T a, T b, T m) const -> T
    {
        return ::mul(a, b, m);
    }
};
template<class T, class Mul = mul_op<T>>
requires signed_integral<T>
struct prime
{
    [[no_unique_address]] Mul mul{};
    prime() = default;
    explicit prime(Mul f) : mul(move(f)) {}
    constexpr static int test_time = 10;
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
        mt19937 rnd(random_device{}());
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
        mt19937 rnd(random_device{}());
        T c = uniform_int_distribution<T>(1, x - 1)(rnd);
        T val = 1;
        for (unsigned long long goal = 1;; goal *= 2, s = t, val = 1)
        {
            for (unsigned long long step = 1; step <= goal; ++step)
            {
                t = mul(t, t, x);
                t = (t >= x - c ? t - (x - c) : t + c) % x;
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
            if (x <= 1)
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
