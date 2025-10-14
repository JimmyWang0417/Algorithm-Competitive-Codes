template <typename T, int U, bool isOriginal = true>
struct linnerBasis
{
    mutable array<T, U + 1> d;
    mutable bool adjusted;
    bool zero;
    linnerBasis() : d(), adjusted(), zero() {}
    linnerBasis(const vector<T> &other) : linnerBasis()
    {
        for (auto i : other)
            insert(i);
    }
    linnerBasis(const initializer_list<T> &other) : linnerBasis()
    {
        for (auto i : other)
            insert(i);
    }

    auto &operator[](int x) { return d[x]; }
    const auto &operator[](int x) const { return d[x]; }

    auto insert(T v)
    {
        if constexpr (isOriginal)
        {
            for (int i = U; i >= 0; --i)
                if ((v >> i) & 1)
                {
                    if (!d[i])
                    {
                        d[i] = v;
                        return true;
                    }
                    else
                        v ^= d[i];
                }
            zero = true;
            return false;
        }
        else
        {
            for (int i = 0; i <= U; ++i)
                if ((v >> i) & 1)
                {
                    if (!d[i])
                    {
                        d[i] = v;
                        return true;
                    }
                    else
                        v ^= d[i];
                }
            zero = true;
            return false;
        }
    }
    auto merge(const linnerBasis &other)
    {
        for (auto i : other.d)
            insert(i);
        adjust = false;
    }
    auto max(T res = 0) const
    {
        for (int i = U; i >= 0; --i)
            if constexpr (isOriginal)
                res = ::max(res, res ^ d[i]);
            else
            {
                if (d[i])
                    res ^= (T)parity(res & d[i]) << i;
                else
                    res |= (T)1 << i;
            }
        return res;
    }
    auto min(T res) const
    {
        for (int i = U; i >= 0; --i)
            if constexpr (isOriginal)
                res = ::min(res, res ^ d[i]);
            else
            {
                if (d[i])
                    res ^= (T)parity(res & d[i]) << i;
                else
                    res &= ~((T)1 << i);
            }
        return res;
    }
    auto kth(T k) const -> T
    {
        adjust();
        T res = 0;
        if (zero)
            --k;
        if constexpr (isOriginal)
        {
            for (int i = 0; i <= U; ++i)
                if (d[i])
                {
                    if (k & 1)
                        res ^= d[i];
                    k >>= 1;
                }
            return k ? -1 : res;
        }
        else
        {
            auto tot = count(d.begin(), d.end(), 0);
            if (k >= (T)1 << tot)
                return -1;
            for (int i = U; i >= 0; --i)
                if (d[i])
                    res ^= (T)parity(res & d[i]) << i;
                else
                    res ^= (T)((k >> (--tot)) & 1) << i;
            return res;
        }
    }
    auto adjust() const
    {
        if (adjusted)
            return;
        for (int i = 0; i <= U; ++i)
            if constexpr (isOriginal)
            {
                for (int j = 0; j < i; ++j)
                    if ((d[i] >> j) & 1)
                        d[i] ^= d[j];
            }
            else
            {
                for (int j = i + 1; j <= U; ++j)
                    if ((d[i] >> j) & 1)
                        d[i] ^= d[j];
            }
        adjusted = true;
    }
    auto trans() const
    {
        adjust();
        linnerBasis<T, U, isOriginal ^ 1> e;
        e.zero = zero;
        for (int i = 0; i <= U; ++i)
            for (int j = 0; j <= U; ++j)
                if ((d[i] >> j) & 1)
                    e[j] |= (T)1 << i;
        for (int i = 0; i <= U; ++i)
            e[i] ^= (T)1 << i;
        return e;
    }
};