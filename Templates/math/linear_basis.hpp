#pragma once
#include <algorithm>
#include <array>

template <typename T, int U>
struct LinearBasis : std::array<T, U + 1>
{
    using std::array<T, U + 1>::array;
    using std::array<T, U + 1>::begin;
    using std::array<T, U + 1>::end;
    using std::array<T, U + 1>::at;

    LinearBasis() : std::array<T, U + 1>{} {}
    auto insert(T v)
    {
        for (int i = U; i >= 0; --i)
            if ((v >> i) & 1)
            {
                if (!at(i))
                {
                    at(i) = v;
                    return true;
                }
                v ^= at(i);
            }
        return false;
    }
    auto contain(T v) const
    {
        for (int i = U; i >= 0; --i)
            if ((v >> i) & 1)
            {
                if (!at(i))
                    return false;
                v ^= at(i);
            }
        return true;
    }
    auto rank() const
    {
        return (int)std::count_if(begin(), end(), [](T x)
                                  { return x != 0; });
    }
    auto &merge(const LinearBasis &other)
    {
        for (auto i : other)
            if (i)
                insert(i);
        return *this;
    }
    auto &intersect(const LinearBasis &other)
    {
        LinearBasis d = *this, tag{};
        auto push = [&](T v, T t)
        {
            for (int i = U; i >= 0; --i)
                if ((v >> i) & 1)
                {
                    if (!d[i])
                    {
                        d[i] = v;
                        tag[i] = t;
                        return T{};
                    }
                    v ^= d[i];
                    t ^= tag[i];
                }
            return t;
        };

        LinearBasis res;
        for (auto i : other)
            if (i)
            {
                auto v = push(i, i);
                if (v)
                    res.insert(v);
            }
        return *this = res;
    }
    auto max(T res = 0) const
    {
        for (int i = U; i >= 0; --i)
            res = std::max(res, res ^ at(i));
        return res;
    }
    auto min(T res = 0) const
    {
        for (int i = U; i >= 0; --i)
            res = std::min(res, res ^ at(i));
        return res;
    }
    auto &adjust()
    {
        for (int i = 0; i <= U; ++i)
            if (at(i))
                for (int j = i - 1; j >= 0; --j)
                    if ((at(i) >> j) & 1)
                        at(i) ^= at(j);
        return *this;
    }
    auto &adjust() const
    {
        return const_cast<LinearBasis &>(*this).adjust();
    }
    auto &reduced()
    {
        return adjust();
    }
    const auto &reduced() const
    {
        return adjust();
    }
    auto kth(T k) const -> T
    {
        const auto &basis = reduced();
        T res = 0;
        for (int i = 0; i <= U; ++i)
            if (basis[i])
            {
                if (k & 1)
                    res ^= basis[i];
                k >>= 1;
            }
        return k ? (T)-1 : res;
    }
    static auto orthogonal(const LinearBasis &basis)
    {
        basis.adjust();
        LinearBasis res;
        for (int j = 0; j <= U; ++j)
            if (!basis[j])
            {
                T v = (T)1 << j;
                for (int i = j + 1; i <= U; ++i)
                    if (basis[i] && ((basis[i] >> j) & 1))
                        v |= (T)1 << i;
                res.insert(v);
            }
        return res;
    }
};
