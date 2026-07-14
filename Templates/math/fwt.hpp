#pragma once
#include <algorithm>
#include <vector>

template <int mod = 998244353>
struct fwt
{
    using i64 = long long;

    static auto norm(i64 x)
    {
        x %= mod;
        if (x < 0)
            x += mod;
        return (int)x;
    }

    static auto power(i64 a, i64 b = mod - 2)
    {
        i64 res = 1;
        for (a = norm(a); b; b >>= 1, a = a * a % mod)
            if (b & 1)
                res = res * a % mod;
        return (int)res;
    }

    static auto fit(std::vector<int> &a, int n)
    {
        if ((int)a.size() < n)
            a.resize(n);
        for (auto &x : a)
            x = norm(x);
    }

    static auto orTrans(std::vector<int> &a, bool inv = false)
    {
        int n = (int)a.size();
        for (int mid = 1; mid < n; mid <<= 1)
            for (int i = 0; i < n; i += mid << 1)
                for (int j = 0; j < mid; ++j)
                    a[i + j + mid] = norm(a[i + j + mid] + (inv ? -a[i + j] : a[i + j]));
    }

    static auto andTrans(std::vector<int> &a, bool inv = false)
    {
        int n = (int)a.size();
        for (int mid = 1; mid < n; mid <<= 1)
            for (int i = 0; i < n; i += mid << 1)
                for (int j = 0; j < mid; ++j)
                    a[i + j] = norm(a[i + j] + (inv ? -a[i + j + mid] : a[i + j + mid]));
    }

    static auto xorTrans(std::vector<int> &a, bool inv = false)
    {
        int n = (int)a.size();
        for (int mid = 1; mid < n; mid <<= 1)
            for (int i = 0; i < n; i += mid << 1)
                for (int j = 0; j < mid; ++j)
                {
                    int x = a[i + j], y = a[i + j + mid];
                    a[i + j] = norm(x + y);
                    a[i + j + mid] = norm(x - y);
                }
        if (inv)
        {
            int iv = power(n);
            for (auto &x : a)
                x = (i64)x * iv % mod;
        }
    }

    template <typename Trans>
    static auto conv(std::vector<int> a, std::vector<int> b, Trans trans)
    {
        int n = 1;
        while (n < (int)std::max(a.size(), b.size()))
            n <<= 1;
        fit(a, n), fit(b, n);
        trans(a, false), trans(b, false);
        for (int i = 0; i < n; ++i)
            a[i] = (i64)a[i] * b[i] % mod;
        trans(a, true);
        return a;
    }

    static auto orConv(std::vector<int> a, std::vector<int> b)
    {
        return conv(a, b, orTrans);
    }

    static auto andConv(std::vector<int> a, std::vector<int> b)
    {
        return conv(a, b, andTrans);
    }

    static auto xorConv(std::vector<int> a, std::vector<int> b)
    {
        return conv(a, b, xorTrans);
    }
};
