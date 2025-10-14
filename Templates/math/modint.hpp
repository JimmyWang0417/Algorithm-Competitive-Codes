template <const int _mod>
struct modint
{
    constexpr modint(int _x = 0) : x(_x) {}
    constexpr auto operator+() const
    {
        return *this;
    }
    constexpr auto operator-() const
    {
        return !x ? 0 : _mod - x;
    }
    constexpr auto &operator++()
    {
        ++x;
        if (x >= _mod)
            x -= _mod;
        return *this;
    }
    constexpr auto &operator--()
    {
        --x;
        if (x < 0)
            x += _mod;
        return *this;
    }
    constexpr auto operator++(int) -> modint
    {
        int res = x;
        if (x >= _mod)
            x -= _mod;
        return res;
    }
    constexpr auto operator--(int) -> modint
    {
        int res = x;
        if (x < 0)
            x += _mod;
        return res;
    }
    constexpr auto operator+(const modint &rhs) const -> modint
    {
        int res = x;
        res += rhs.x;
        if (res >= _mod)
            res -= _mod;
        return res;
    }
    constexpr auto operator-(const modint &rhs) const -> modint
    {
        int res = x;
        res -= rhs.x;
        if (res < 0)
            res += _mod;
        return res;
    }
    constexpr auto operator*(const modint &rhs) const -> modint
    {
        return (int)((ll)x * rhs.x % _mod);
    }
    constexpr auto &operator+=(const modint &rhs)
    {
        x += rhs.x;
        if (x >= _mod)
            x -= _mod;
        return *this;
    }
    constexpr auto &operator-=(const modint &rhs)
    {
        x -= rhs.x;
        if (x < 0)
            x += _mod;
        return *this;
    }
    constexpr auto &operator*=(const modint &rhs)
    {
        x = (int)((ll)x * rhs.x % _mod);
        return *this;
    }
    template <typename _G>
    constexpr auto pow(_G rhs) const
    {
        modint a = x, res = 1;
        while (rhs)
        {
            if (rhs & 1)
                res *= a;
            a *= a;
            rhs >>= 1;
        }
        return res;
    }
    constexpr auto inv() const { return this->pow(_mod - 2); }
    constexpr auto operator/(const modint &rhs) const { return (*this) * rhs.inv(); }
    constexpr auto &operator/=(const modint &rhs) { return (*this) *= rhs.inv(); }
    constexpr auto operator==(const modint &rhs) const { return x == rhs.x; }
    constexpr auto operator!=(const modint &rhs) const { return x != rhs.x; }
    constexpr auto &data() { return x; }
    constexpr auto friend &operator>>(istream &in, modint &x) { return in >> x.x; }
    constexpr auto friend &operator<<(ostream &out, const modint &x) { return out << x.x; }

private:
    int x;
};