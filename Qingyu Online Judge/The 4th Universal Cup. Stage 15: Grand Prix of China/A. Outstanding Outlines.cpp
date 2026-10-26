#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>
using namespace std;
typedef int64_t i64;
typedef uint64_t u64;
typedef __int128_t i128;
typedef __uint128_t u128;
typedef __float80 f80;
typedef __float128 f128;
constexpr int mod = 1e6 + 3;
template <typename T = int>
constexpr auto quickpow(i64 a, T b = mod - 2)
{
    a %= mod;
    i64 res = 1;
    while (b)
    {
        if (b & 1)
            (res *= a) %= mod;
        (a *= a) %= mod;
        b >>= 1;
    }
    return res;
}
struct fraction
{
    i128 x, y;
    auto &adjust()
    {
        auto g = __gcd(x, y);
        x /= g, y /= g;
        if (y < 0)
            x = -x, y = -y;
        return (*this);
    }
    fraction() = default;
    fraction(i128 _x, i128 _y = 1) : x(_x), y(_y)
    {
        adjust();
    }
    auto friend operator*(fraction lhs, fraction rhs)
    {
        auto res = fraction(lhs.x * rhs.x, lhs.y * rhs.y);
        return res.adjust();
    }
    auto friend operator+(fraction lhs, fraction rhs)
    {
        auto res = fraction(lhs.x * rhs.y + lhs.y * rhs.x, lhs.y * rhs.y);
        return res.adjust();
    }
    auto friend operator-(fraction lhs, fraction rhs)
    {
        auto res = fraction(lhs.x * rhs.y - lhs.y * rhs.x, lhs.y * rhs.y);
        return res.adjust();
    }
    auto friend &operator*=(fraction &lhs, fraction rhs)
    {
        auto res = fraction(lhs.x * rhs.x, lhs.y * rhs.y);
        return lhs = res.adjust();
    }
    auto friend &operator+=(fraction &lhs, fraction rhs)
    {
        auto res = fraction(lhs.x * rhs.y + lhs.y * rhs.x, lhs.y * rhs.y);
        return lhs = res.adjust();
    }
    auto friend &operator-=(fraction &lhs, fraction rhs)
    {
        auto res = fraction(lhs.x * rhs.y - lhs.y * rhs.x, lhs.y * rhs.y);
        return lhs = res.adjust();
    }
    auto friend operator==(fraction lhs, fraction rhs)
    {
        return lhs.x * rhs.y == lhs.y * rhs.x;
    }
    auto friend operator<=>(fraction lhs, fraction rhs)
    {
        return lhs.x * rhs.y <=> lhs.y * rhs.x;
    }
    auto operator-() const
    {
        return fraction(-x, y);
    }
};
typedef complex<fraction> p2;
auto dot(p2 x, p2 y)
{
    return (conj(x) * y).real();
}
auto cross(p2 x, p2 y)
{
    return (conj(x) * y).imag();
}
struct Main
{
    p2 A, B, C, D;
    Main()
    {
        {
            int x, y;
            cin >> x >> y;
            A = p2(x, y);
        }
        {
            int x, y;
            cin >> x >> y;
            B = p2(x, y);
        }
        {
            int x, y;
            cin >> x >> y;
            C = p2(x, y);
        }
        {
            char _;
            int x1, y1, x2, y2;
            cin >> x1 >> _ >> y1 >> x2 >> _ >> y2;
            D = p2(fraction(x1, y1), fraction(x2, y2));
        }

        // l1
        {
            if (cross(D - A, B - A) == 0)
            {
                cout << "Yes\n";
                return;
            }
        }
        // l2
        {
            if (cross(D - C, B - A) == 0)
            {
                cout << "Yes\n";
                return;
            }
        }
        auto check = [&](p2 a, p2 c)
        {
            auto X = cross(D - a, c - a);
            auto Y = cross(B - A, c - a);
            return X.x * Y.y % (X.y * Y.x) == 0;
        };
        if ((cross(D - A, B - A) >= 0) != (cross(D - C, B - A) >= 0) &&
            (check(A, C) || check(B, C)))
        {
            cout << "Yes\n";
            return;
        }
        i128 d;
        {
            auto X = dot(D - A, B - A);
            auto Y = dot(B - A, B - A);
            assert(Y.y == 1);
            auto a = X.x, b = X.y * Y.x;
            d = a / b;
            if (a - b * d < 0)
                --d;
            D = D - (B - A) * fraction(d, 1);
        }
        // l3
        {
            if (dot(D - B, D - C) <= 0 && cross(D - B, D - C) == 0)
            {
                cout << "Yes\n";
                return;
            }
        }
        // l4
        {
            if (dot(D - A, D - C) <= 0 && cross(D - A, D - C) == 0)
            {
                cout << "Yes\n";
                return;
            }
        }
        auto rightA = dot(B - A, C - A) == 0;
        auto rightB = dot(A - B, C - B) == 0;
        if (d != 0 && (rightA || rightB))
        {
            C = rightA ? C + B - A : C + A - B;
            // l5
            {
                if (dot(D - B, D - C) <= 0 && cross(D - B, D - C) == 0)
                {
                    cout << "Yes\n";
                    return;
                }
            }
            // l6
            {
                if (dot(D - A, D - C) <= 0 && cross(D - A, D - C) == 0)
                {
                    cout << "Yes\n";
                    return;
                }
            }
        }
        cout << "No\n";
    }
};
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    cin >> T;
    while (T--)
        Main();
    return 0;
}
