#pragma once
#include "sieve.hpp"
#include <cmath>
#include <functional>
#include <unordered_map>
#include <vector>

template <typename T = long long>
struct DuSieve
{
    using i64 = long long;

    int lim = 0;
    std::vector<T> pre;
    std::unordered_map<i64, T> mp;
    std::function<T(i64)> prefixC;
    std::function<T(i64, i64)> prefixB;

    DuSieve() = default;

    template <typename PrefixC, typename PrefixB>
    DuSieve(const std::vector<T> &_pre, PrefixC _prefixC, PrefixB _prefixB)
        : lim((int)_pre.size() - 1), pre(_pre), prefixC(_prefixC), prefixB(_prefixB)
    {
    }

    template <typename PrefixC, typename PrefixB>
    auto init(const std::vector<T> &_pre, PrefixC _prefixC, PrefixB _prefixB)
    {
        pre = _pre;
        lim = (int)pre.size() - 1;
        prefixC = _prefixC;
        prefixB = _prefixB;
    }

    auto clear()
    {
        mp.clear();
    }

    auto calc(i64 n) -> T
    {
        if (n <= 0)
            return T(0);
        if (n <= lim)
            return pre[n];
        if (auto it = mp.find(n); it != mp.end())
            return it->second;
        T res = prefixC(n);
        for (i64 l = 2, r; l <= n; l = r + 1)
        {
            r = n / (n / l);
            res -= prefixB(l, r) * calc(n / l);
        }
        return mp[n] = res;
    }
};

template <typename T = long long>
struct DuSieveMuPhi
{
    using i64 = long long;

    sieve<T> s;
    DuSieve<T> mu, phi;

    DuSieveMuPhi() = default;
    DuSieveMuPhi(int n) : s(n),
                          mu(s.preMu,
                             [](i64) -> T
                             { return T(1); },
                             [](i64 l, i64 r) -> T
                             { return T(r - l + 1); }),
                          phi(s.prePhi,
                              [](i64 n) -> T
                              { return T(n) * T(n + 1) / T(2); },
                              [](i64 l, i64 r) -> T
                              { return T(r - l + 1); })
    {
    }

    auto init(int n)
    {
        s.init(n);
        mu.init(
            s.preMu,
            [](i64) -> T
            { return T(1); },
            [](i64 l, i64 r) -> T
            { return T(r - l + 1); });
        phi.init(
            s.prePhi,
            [](i64 n) -> T
            { return T(n) * T(n + 1) / T(2); },
            [](i64 l, i64 r) -> T
            { return T(r - l + 1); });
    }

    auto sumMu(i64 n) -> T
    {
        return mu.calc(n);
    }

    auto sumPhi(i64 n) -> T
    {
        return phi.calc(n);
    }

    static auto isqrt(i64 n)
    {
        if (n <= 0)
            return i64(0);
        i64 r = std::sqrt((long double)n);
        while (r + 1 <= n / (r + 1))
            ++r;
        while (r > n / r)
            --r;
        return r;
    }

    auto sumMu2(i64 n) -> T
    {
        T res = 0;
        for (i64 l = 1, r; l <= n / l; l = r + 1)
        {
            i64 t = n / (l * l);
            r = isqrt(n / t);
            res += (sumMu(r) - sumMu(l - 1)) * T(t);
        }
        return res;
    }
};
