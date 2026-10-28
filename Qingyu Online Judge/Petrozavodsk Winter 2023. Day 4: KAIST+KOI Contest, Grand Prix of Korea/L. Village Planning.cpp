#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
typedef int64_t i64;
typedef uint64_t u64;
typedef __int128_t i128;
typedef __uint128_t u128;
typedef __float80 f80;
typedef __float128 f128;
constexpr int mod = 998244353;
template <typename T = int>
constexpr auto quickpow(i64 a, T b = mod - 2) -> i64
{
    if (b < 0)
        return quickpow(quickpow(a, -b));
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
namespace polynomial
{ // NTT模数 998244353, 1004535809, 4179340454199820289
    struct poly : vector<i64>
    {
        constexpr static bool has = false;
        constexpr static int inv2 = quickpow(2);
        constexpr static int inv3 = quickpow(3);
        constexpr static int imagUnit = 86583718;
        inline static vector<int> rk;
        inline static int len, limit;
        static auto init(int n)
        {
            len = 0, limit = 1;
            while (limit < n)
            {
                ++len;
                limit <<= 1;
            }
            rk.resize(limit);
            rk[0] = 0;
            for (int i = 1; i < limit; ++i)
                rk[i] = (rk[i >> 1] >> 1) | ((i & 1) << (len - 1));
        }
        using vector<i64>::vector;
        auto friend &operator>>(istream &in, poly &p)
        {
            for (auto &i : p)
                in >> i;
            return in;
        }
        auto friend &operator<<(ostream &out, const poly &p)
        {
            for (auto i : p)
                out << (i + mod) % mod << ' ';
            return out;
        }
        auto friend operator>>(poly lhs, int rhs)
        {
            lhs.erase(lhs.begin(), lhs.begin() + rhs);
            return lhs;
        }
        auto friend operator<<(poly lhs, int rhs)
        {
            lhs.insert(lhs.begin(), rhs, 0);
            return lhs;
        }
        auto friend operator-(poly res)
        {
            for (auto &i : res)
                i = -i;
            return res;
        }
        auto friend operator+(poly lhs, i64 rhs)
        {
            if (lhs.empty())
                lhs.emplace_back();
            (lhs[0] += rhs) %= mod;
            return lhs;
        }
        auto friend operator-(poly lhs, i64 rhs)
        {
            if (lhs.empty())
                lhs.emplace_back();
            (lhs[0] -= rhs) %= mod;
            return lhs;
        }
        auto friend operator*(poly lhs, i64 rhs)
        {
            for (auto &i : lhs)
                (i *= rhs) %= mod;
            return lhs;
        }
        auto friend operator/(const poly &lhs, i64 rhs)
        {
            return lhs * quickpow(rhs);
        }
        auto friend operator+(poly lhs, poly rhs)
        {
            if (lhs.size() < rhs.size())
                lhs.resize(rhs.size());
            rhs.resize(lhs.size());
            for (int i = 0; i < (int)lhs.size(); ++i)
                (lhs[i] += rhs[i]) %= mod;
            return lhs;
        }
        auto friend operator-(poly lhs, poly rhs)
        {
            if (lhs.size() < rhs.size())
                lhs.resize(rhs.size());
            rhs.resize(lhs.size());
            for (int i = 0; i < (int)lhs.size(); ++i)
                (lhs[i] -= rhs[i]) %= mod;
            return lhs;
        }
        auto NTT()
        {
            auto &dp = (*this);
            for (int i = 0; i < limit; ++i)
                if (i < rk[i])
                    std::swap(dp[i], dp[rk[i]]);
            for (int mid = 1; mid < limit; mid <<= 1)
            {
                const auto gn = quickpow(3, (mod - 1) / (mid << 1));
                for (int i = 0; i < limit; i += mid << 1)
                {
                    i64 g = 1;
                    for (int j = 0; j < mid; ++j, (g *= gn) %= mod)
                    {
                        auto x = dp[i + j], y = dp[i + j + mid] * g % mod;
                        dp[i + j] = (x + y) % mod;
                        dp[i + j + mid] = (x - y) % mod;
                    }
                }
            }
        }
        auto INTT()
        {
            auto &dp = (*this);
            for (int i = 0; i < limit; ++i)
                if (i < rk[i])
                    std::swap(dp[i], dp[rk[i]]);
            for (int mid = 1; mid < limit; mid <<= 1)
            {
                const auto gn = quickpow(inv3, (mod - 1) / (mid << 1));
                for (int i = 0; i < limit; i += mid << 1)
                {
                    i64 g = 1;
                    for (int j = 0; j < mid; ++j, (g *= gn) %= mod)
                    {
                        auto x = dp[i + j], y = dp[i + j + mid] * g % mod;
                        dp[i + j] = (x + y) % mod;
                        dp[i + j + mid] = (x - y) % mod;
                    }
                }
            }
            auto inv = quickpow(limit);
            for (int i = 0; i < limit; ++i)
                (dp[i] *= inv) %= mod;
        }
        auto reverse() { std::reverse(begin(), end()); }
        auto fit(size_t n, i64 value = 0) const
        {
            auto res = *this;
            res.resize(n, value);
            return res;
        }
        auto friend operator*(poly lhs, poly rhs)
        {
            if (lhs.empty() || rhs.empty())
                return poly{};
            auto up = lhs.size() + rhs.size() - 1;
            constexpr static size_t LIM = 128;
            if (lhs.size() <= LIM || rhs.size() <= LIM)
            {
                poly res(up);
                for (int i = 0; i < (int)lhs.size(); ++i)
                    for (int j = 0; j < (int)rhs.size(); ++j)
                        (res[i + j] += lhs[i] * rhs[j]) %= mod;
                return res;
            }
            init((int)up);
            lhs.resize(limit), lhs.NTT();
            rhs.resize(limit), rhs.NTT();
            poly res(limit);
            for (int i = 0; i < limit; ++i)
                res[i] = lhs[i] * rhs[i] % mod;
            res.INTT(), res.resize(up);
            return res;
        }
        auto friend operator^(const poly &lhs, poly rhs)
        {
            if (lhs.empty() || rhs.empty())
                return poly{};
            rhs.reverse();
            auto res = lhs * rhs;
            res.erase(res.begin(), res.begin() + rhs.size() - 1);
            return res;
        }
        auto shift(int c) const // f(x + c)
        {
            if (empty())
                return poly{};
            vector<i64> fac(size()), ifac(size());
            fac[0] = 1;
            for (int i = 1; i < (int)size(); ++i)
                fac[i] = fac[i - 1] * i % mod;
            ifac[size() - 1] = quickpow(fac[size() - 1]);
            for (int i = (int)size() - 1; i >= 1; --i)
                ifac[i - 1] = ifac[i] * i % mod;
            poly F(size()), G(size());
            {
                i64 cc = 1;
                for (int i = 0; i < (int)size(); ++i, (cc *= c) %= mod)
                {
                    F[i] = at(i) * fac[i] % mod;
                    G[i] = ifac[i] * cc % mod;
                }
            }
            F = F ^ G;
            for (int i = 0; i < (int)size(); ++i)
                (F[i] *= ifac[i]) %= mod;
            return F;
        }
        auto inv(int n) const
        {
            if (!n)
                return poly{};
            if (n == 1)
                return poly{quickpow(at(0))};
            poly F = inv((n + 1) / 2), G(begin(), begin() + n);
            init(n * 2);
            F.resize(limit), F.NTT();
            G.resize(limit), G.NTT();
            for (int i = 0; i < limit; ++i)
                F[i] = (2 - F[i] * G[i] % mod) * F[i] % mod;
            F.INTT(), F.resize(n);
            return F;
        }
        auto inv() const { return inv((int)size()); }
        auto invBf() const
        {
            if (empty())
                return poly{};
            poly G(size());
            i64 invF0 = quickpow(at(0));
            G[0] = invF0;
            for (int i = 1; i < (int)size(); ++i)
            {
                i64 res = 0;
                for (int j = 1; j <= i; ++j)
                    (res += at(j) * G[i - j]) %= mod;
                G[i] = -res * invF0 % mod;
            }
            return G;
        }
        auto friend operator/(poly lhs, poly rhs)
        {
            if (lhs.size() < rhs.size())
                return poly{0};
            lhs.reverse(), rhs.reverse();
            auto up = lhs.size() - rhs.size() + 1;
            lhs.resize(up), rhs.resize(up);
            auto res = lhs * rhs.inv();
            res.resize(up), res.reverse();
            return res;
        }
        auto friend operator%(const poly &lhs, const poly &rhs)
        {
            if (lhs.size() < rhs.size())
                return lhs;
            auto res = lhs - lhs / rhs * rhs;
            res.resize(rhs.size() - 1);
            return res;
        }
        auto sqrt(int n) const
        {
            if (!n)
                return poly{};
            if (n == 1)
                return poly{1};
            poly F = sqrt((n + 1) / 2), G = poly(begin(), begin() + n);
            F.resize(n);
            poly invF = F.inv();
            init(n * 2);
            F.resize(limit), F.NTT();
            G.resize(limit), G.NTT();
            invF.resize(limit), invF.NTT();
            for (int i = 0; i < limit; ++i)
                F[i] = (F[i] * F[i] + G[i]) % mod * inv2 % mod * invF[i] % mod;
            F.INTT(), F.resize(n);
            return F;
        }
        auto sqrt() const { return sqrt((int)size()); }
        auto sqrtBf() const
        {
            if (empty())
                return poly{};
            poly G(size());
            G[0] = 1;
            for (int i = 1; i < (int)size(); ++i)
            {
                i64 res = 0;
                for (int j = 1; j < i; ++j)
                    (res += G[j] * G[i - j]) %= mod;
                // G[k] = (F[k] - sum(G[i]*G[k-i])) / (2 * G[0])
                G[i] = (at(i) - res) % mod * inv2 % mod;
            }
            return G;
        }
        // 积分和求导
        auto integral() const
        {
            if (empty())
                return poly{0};
            poly res(size() + 1);
            vector<i64> inv(size() + 1);
            inv[1] = 1;
            for (int i = 2; i <= (int)size(); ++i)
                inv[i] = -mod / i * inv[mod % i] % mod;
            for (int i = 1; i <= (int)size(); ++i)
                res[i] = at(i - 1) * inv[i] % mod;
            return res;
        }
        auto differ() const
        {
            if (empty())
                return poly{};
            poly res(size() - 1);
            for (int i = 1; i < (int)size(); ++i)
                res[i - 1] = at(i) * i % mod;
            return res;
        }
        // 指数函数得保证a0 = 0, 对数函数得保证a0 = 1
        auto ln() const
        {
            if (empty())
                return poly{};
            auto res = differ() * inv();
            res.resize(size() - 1);
            return res.integral();
        }
        auto lnBf() const
        {
            if (size() <= 1)
                return poly(size());
            poly G(size());
            vector<i64> inv(size());
            inv[1] = 1;
            for (int i = 2; i < (int)size(); ++i)
                inv[i] = (mod - mod / i) * inv[mod % i] % mod;
            for (int i = 1; i < (int)size(); ++i)
            {
                i64 res = 0;
                for (int j = 1; j < i; ++j)
                    (res += j * G[j] % mod * at(i - j)) %= mod;
                G[i] = (at(i) - res * inv[i]) % mod;
            }
            return G;
        }
        auto exp(int n) const
        {
            if (!n)
                return poly{};
            if (n == 1)
                return poly{1};
            poly F = exp((n + 1) / 2), G(begin(), begin() + n);
            F.resize(n);
            poly lnF = F.ln();
            init(n * 2);
            F.resize(limit), F.NTT();
            G.resize(limit), G.NTT();
            lnF.resize(limit), lnF.NTT();
            for (int i = 0; i < limit; ++i)
                F[i] = F[i] * (1 - lnF[i] + G[i]) % mod;
            F.INTT(), F.resize(n);
            return F;
        }
        auto exp() const { return exp((int)size()); }
        auto expBf() const
        {
            if (empty())
                return poly{};
            if (size() == 1)
                return poly{1};
            poly G(size());
            G[0] = 1;
            vector<i64> inv(size());
            inv[1] = 1;
            for (int i = 2; i < (int)size(); ++i)
                inv[i] = -mod / i * inv[mod % i] % mod;
            for (int i = 1; i < (int)size(); ++i)
            {
                i64 res = 0;
                for (int j = 1; j <= i; ++j)
                    (res += j * at(j) % mod * G[i - j]) %= mod;
                G[i] = res * inv[i] % mod;
            }
            return G;
        }
    };
}
using namespace polynomial;
vector<i64> fac, ifac;
auto init(int n)
{
    fac.resize(n + 1), ifac.resize(n + 1);
    fac[0] = 1;
    for (int i = 1; i <= n; ++i)
        fac[i] = fac[i - 1] * i % mod;
    ifac[n] = quickpow(fac[n]);
    for (int i = n; i >= 1; --i)
        ifac[i - 1] = ifac[i] * i % mod;
}
struct Main
{
    int n, k;
    vector<i64> A;
    auto solve0()
    {
        poly answer(n - 1);
        for (int i = 2; i <= n; ++i)
            answer[i - 2] = quickpow(A[0], (i64)i * (i - 1) / 2) % mod;
        return answer;
    }
    auto solve1()
    {
        poly a(n + 1);
        for (int i = 1; i <= n; ++i)
            a[i] = quickpow(i, i - 2) *
                   quickpow(A[1] * quickpow(A[0]) % mod, (i64)i * (i - 1) / 2) % mod *
                   ifac[i] % mod;
        a = a.exp();
        poly answer(n - 1);
        for (int i = 2; i <= n; ++i)
            answer[i - 2] = a[i] * fac[i] % mod * quickpow(A[0], (i64)i * (i - 1) / 2) % mod;
        return answer;
    }
    auto solve2()
    {
        poly a(n + 1), t(n + 1);
        const i64 r10 = A[1] * quickpow(A[0]) % mod;
        const i64 r12 = A[1] * quickpow(A[2]) % mod;
        const i64 r20 = A[2] * quickpow(A[0]) % mod;
        for (int i = 1; i <= n; ++i)
        {
            const i64 e = (i64)i * (i - 1) / 2;
            t[i] = quickpow(i, i - 2) * quickpow(r10, e) % mod * ifac[i] % mod;
            a[i] = quickpow(i, i - 1) * quickpow(r12, e) % mod * ifac[i] % mod;
        }

        constexpr static i64 inv2 = quickpow(2);
        auto b = (-(poly{1} - a).ln() - a - (a * a).fit(n + 1) * inv2) * inv2;
        for (int i = 1; i <= n; ++i)
            b[i] = b[i] * quickpow(r20, (i64)i * (i - 1) / 2) % mod;

        b = (t + b).exp();
        poly answer(n - 1);
        for (int i = 2; i <= n; ++i)
            answer[i - 2] = b[i] * fac[i] % mod *
                            quickpow(A[0], (i64)i * (i - 1) / 2) % mod;
        return answer;
    }
    Main()
    {
        cin >> n >> k;
        A.resize(k + 1);
        for (int i = 0; i <= k; ++i)
            cin >> A[i];
        if (k == 0)
            cout << solve0() << '\n';
        else if (k == 1)
            cout << solve1() << '\n';
        else
            cout << solve2() << '\n';
    }
};
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    init(1e6);
    int T = 1;
    // cin >> T;
    while (T--)
        Main();
    return 0;
}
