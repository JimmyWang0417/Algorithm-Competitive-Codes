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
constexpr int mod = 167772161;
template <typename T = int>
constexpr auto quickpow(i64 a, T b = mod - 2)
{
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
{
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
            for (int i = 0; i < limit; ++i)
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
            lhs.insert(lhs.begin(), rhs);
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
            (lhs[0] += rhs) %= mod;
            return lhs;
        }
        auto friend operator-(poly lhs, i64 rhs)
        {
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
            poly res(max(lhs.size(), rhs.size()));
            lhs.resize(res.size()), rhs.resize(res.size());
            for (int i = 0; i < (int)res.size(); ++i)
                res[i] = (lhs[i] + rhs[i]) % mod;
            return res;
        }
        auto friend operator-(poly lhs, poly rhs)
        {
            poly res(max(lhs.size(), rhs.size()));
            lhs.resize(res.size()), rhs.resize(res.size());
            for (int i = 0; i < (int)res.size(); ++i)
                res[i] = (lhs[i] - rhs[i]) % mod;
            return res;
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
            poly inv(size() + 1), res(size() + 1);
            inv[1] = 1;
            for (int i = 2; i <= (int)size(); ++i)
                inv[i] = -mod / i * inv[mod % i] % mod;
            for (int i = 1; i <= (int)size(); ++i)
                res[i] = at(i - 1) * inv[i] % mod;
            return res;
        }
        auto differ() const
        {
            poly res(size() - 1);
            for (int i = 1; i < (int)size(); ++i)
                res[i - 1] = at(i) * i % mod;
            return res;
        }

        // 指数函数得保证a0 = 0, 对数函数得保证a0 = 1
        auto ln() const
        {
            auto res = differ() * inv();
            res.resize(size() - 1);
            return res.integral();
        }
        auto lnBf() const
        {
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

        // 三角函数（得保证a0 = 0）
        auto cos() const
        {
            return ((*this * imagUnit).exp() + (*this * (-imagUnit)).exp()) * inv2;
        }
        auto sin() const
        {
            return ((*this * imagUnit).exp() - (*this * (-imagUnit)).exp()) * (-(i64)inv2 * imagUnit % mod);
        }
        auto tan() const
        {
            auto res = sin() * cos().inv();
            res.resize(size());
            return res;
        }

        // 反三角函数（得保证 a0 = 0）
        auto asin() const
        {
            auto res = (*this) * (*this);
            res.resize(size());
            res[0] = (1 - res[0]) % mod;
            for (int i = 1; i < (int)size(); ++i)
                res[i] = -res[i];
            res = differ() * res.sqrt().inv();
            res.resize(size() - 1);
            return res.integral();
        }
        auto acos() const
        {
            auto res = asin();
            for (int i = 0; i < (int)size(); ++i)
                res[i] = -res[i];
            return res;
        }
        auto atan() const
        {
            auto res = (*this) * (*this);
            res.resize(size());
            res[0] = (1 + res[0]) % mod;
            res = differ() * res.inv();
            res.resize(size() - 1);
            return res.integral();
        }

        // 多项式快速幂
        auto pow(int n, poly q) const
        {
            poly res{1}, p = (*this);
            while (n)
            {
                if (n & 1)
                    res = res * p % q;
                p = p * p % q;
                n >>= 1;
            }
            return res;
        }
        // n是指 mod 998244353 的结果，m是指 mod 998244352 的结果, r是指位移乘数
        auto pow(int n) const { return (ln() * n).exp(); }
        auto pow(int n, int m, int r) const
        {
            int fir = (int)size();
            for (int i = 0; i < (int)size(); ++i)
                if (at(i))
                {
                    fir = i;
                    break;
                }
            if ((i64)fir * r >= (int)size()) // 说明是原poly是全0
                return poly(size());
            int right = fir * r;
            poly res(size());
            auto inv = quickpow(at(fir)), times = quickpow(at(fir), m);
            for (int i = fir; i < (int)size(); ++i)
                res[i - fir] = at(i) * inv % mod;
            res = res.pow(n) * times;
            poly ans(size());
            for (int i = right; i < (int)size(); ++i)
                ans[i] = res[i - right];
            return ans;
        }

        static auto bostanMori(int n, poly F, poly G)
        {
            if (!n)
                return F[0] * quickpow(G[0]) % mod;
            if (n + 1 < (int)F.size())
                F.resize(n + 1);
            if (n + 1 < (int)G.size())
                G.resize(n + 1);
            auto H = G;
            for (int i = 1; i < (int)H.size(); i += 2)
                H[i] = -H[i];
            F = F * H, G = G * H;
            poly A, B;
            for (int i = n & 1; i < (int)F.size(); i += 2)
                A.emplace_back(F[i]);
            for (int i = 0; i < (int)G.size(); i += 2)
                B.emplace_back(G[i]);
            return bostanMori(n / 2, A, B);
        }

        typedef vector<poly> vpoly;
        auto friend operator*(const vpoly &a, const vpoly &b)
        {
            if (a.empty() || b.empty())
                return vpoly{};
            int n = (int)a.size(), m = (int)b.size();

            auto p = 0, q = 0;
            for (const auto &i : a)
                p = max(p, (int)i.size());
            for (const auto &i : b)
                q = max(q, (int)i.size());
            if (p == 0 || q == 0)
                return vpoly{};

            auto pad = p + q - 1;
            poly F(n * pad), G(m * pad);
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < (int)a[i].size(); ++j)
                    F[i * pad + j] = a[i][j];
            for (int i = 0; i < m; ++i)
                for (int j = 0; j < (int)b[i].size(); ++j)
                    G[i * pad + j] = b[i][j];
            F = F * G;
            vpoly c(n + m - 1, poly(pad));
            for (int i = 0; i < n + m - 1; ++i)
                for (int j = 0; j < pad; ++j)
                    c[i][j] = F[i * pad + j];
            return c;
        }
        static auto bostanMori(int n, vpoly F, vpoly G)
        {
            if (!n)
                return F.front() * G.front().inv();
            if (n + 1 < (int)F.size())
                F.resize(n + 1);
            if (n + 1 < (int)G.size())
                G.resize(n + 1);
            vpoly H = G;
            for (int i = 1; i < (int)H.size(); i += 2)
                for (auto &j : H[i])
                    j = -j;
            F = F * H, G = G * H;
            vpoly A, B;
            for (int i = n & 1; i < (int)F.size(); i += 2)
                A.emplace_back(F[i]);
            for (int i = 0; i < (int)G.size(); i += 2)
                B.emplace_back(G[i]);
            return bostanMori(n / 2, A, B);
        }

        auto compInv() const
        {
            auto dp = (*this);
            int n = (int)size();
            auto v = quickpow(dp[1]);
            for (int i = 0; i < n; i++)
                (dp[i] *= v) %= mod;
            vpoly P, Q;
            for (int i = 0; i < n; i++)
            {
                P.push_back({!i});
                Q.push_back({(i64)!i, -dp[i]});
            }
            poly F = bostanMori(n - 1, P, Q), G(n);
            F.resize(n);

            poly inv(n);
            inv[1] = 1;
            for (int i = 2; i < n; ++i)
                inv[i] = -mod / i * inv[mod % i] % mod;

            for (int i = 0; i < n; i++)
                G[n - 1 - i] = F[i] * (n - 1) % mod * inv[i] % mod;
            i64 w = 1;
            for (int i = 0; i < n; i++, (w *= v) %= mod)
                (G[i] *= w) %= mod;

            G = G.pow((int)-inv[n - 1]);
            G.insert(G.begin(), 0), G.resize(n);
            for (int i = 0; i < n; i++)
                (G[i] *= v) %= mod;
            return G;
        }

        auto friend mulT(const poly &lhs, poly rhs)
        {
            if (rhs.empty() || lhs.size() < rhs.size())
                return poly{};
            rhs.reverse();
            auto res = lhs * rhs;
            res.erase(res.begin(), res.begin() + rhs.size() - 1);
            res.resize(lhs.size() - rhs.size() + 1);
            return res;
        }
        auto friend mulT(const vpoly &a, const vpoly &b)
        {
            if (b.empty() || a.size() < b.size())
                return vpoly{};
            int n = (int)a.size(), m = (int)b.size();

            auto p = 0, q = 0;
            for (const auto &i : a)
                p = max(p, (int)i.size());
            for (const auto &i : b)
                q = max(q, (int)i.size());
            if (q == 0 || p < q)
                return vpoly{};

            poly F(n * p), G(m * p);
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < (int)a[i].size(); ++j)
                    F[i * p + j] = a[i][j];
            for (int i = 0; i < m; ++i)
                for (int j = 0; j < (int)b[i].size() && j < p; ++j)
                    G[(m - 1 - i) * p + (q - 1 - j)] = b[i][j];
            F = F * G;
            vpoly c(n - m + 1, poly(p - q + 1));
            for (int i = 0; i < n - m + 1; ++i)
                for (int j = 0; j < p - q + 1; ++j)
                    c[i][j] = F[(i + m - 1) * p + (j + q - 1)];
            return c;
        }
        auto friend bostanMoriT(int n, poly P, vpoly G)
        {
            if (!n)
            {
                P.resize(G.front().size() * 2 - 1);
                return vpoly{mulT(P, G.front().inv())};
            }
            if (n + 1 < (int)G.size())
                G.resize(n + 1);
            auto H = G;
            for (int i = 1; i < (int)H.size(); i += 2)
                for (auto &j : H[i])
                    j = -j;
            G = G * H;
            vpoly A, B;
            for (int i = 0; i < (int)G.size(); i += 2)
                B.emplace_back(G[i]);
            vpoly F = bostanMoriT(n / 2, P, B);
            for (int i = n & 1; i < (int)F.size(); i += 2)
                A.emplace_back(F[i]);
            A.resize(H.size() * 2);
            for (int i = 0, j = 0; i < (int)A.size(); i++)
            {
                if ((i & 1) == (n & 1) && j < (int)F.size())
                    A[i] = F[j++];
                else
                    A[i] = poly{};
            }
            return mulT(A, H);
        }
        static auto comp(poly F, poly G)
        {
            int n = (int)F.size();
            G.resize(n);
            vpoly Q;
            for (int i = 0; i < n; i++)
                Q.push_back({!i, -G[i]});
            vpoly P = bostanMoriT(n - 1, F, Q);
            poly H(n);
            for (int i = 0; i < n; i++)
                H[n - 1 - i] = P[i].front();
            return H;
        }

        auto compInvBf() const
        {
            int n = (int)size();
            auto F = poly{1} * poly(begin() + 1, end()).inv();
            F.resize(n);
            int block = (int)std::sqrt(n - 1);
            vector<poly> A{poly{1}}, B{poly{1}};
            for (int i = 1; i < block; ++i)
            {
                B.push_back(B.back() * F);
                B.back().resize(n);
            }
            auto C = B.back() * F;
            C.resize(n);
            for (int i = block; i < n; i += block)
            {
                A.push_back(A.back() * C);
                A.back().resize(n);
            }

            vector<i64> inv(n);
            inv[1] = 1;
            for (int i = 2; i < n; ++i)
                inv[i] = -mod / i * inv[mod % i] % mod;

            poly G(n);
            for (int i = 1; i < n; ++i)
            {
                for (int j = 0; j < i; ++j)
                    if (j < (int)A[i / block].size() && i - 1 - j < (int)B[i % block].size())
                        (G[i] += A[i / block][j] * B[i % block][i - 1 - j]) %= mod;
                (G[i] *= inv[i]) %= mod;
            }
            return G;
        }
        static auto compBf(poly F, poly G)
        {
            int n = (int)F.size();
            int block = (int)std::sqrt(n - 1);
            vector<poly> A{poly{1}}, B{poly{1}};
            for (int i = 1; i < block; ++i)
            {
                B.push_back(B.back() * G);
                B.back().resize(n);
            }
            auto C = B.back() * F;
            C.resize(n);
            for (int i = block; i < n; i += block)
            {
                A.push_back(A.back() * C);
                A.back().resize(n);
            }

            poly H(n);
            for (int i = 0; i < (int)A.size(); ++i)
            {
                auto res = poly{};
                for (int j = 0; j < block && i * block + j < n; ++j)
                    res = res + B[j] * F[i * block + j];
                res = res * A[i];
                res.resize(n);
                H = H + res;
            }
            return H;
        }
    };
    struct lagrange
    {
    private:
#define lc (rt << 1)
#define rc (rt << 1 | 1)
        vector<poly> tree;
        auto build(int rt, int l, int r, const vector<int> &a)
        {
            if (l == r)
            {
                tree[rt] = poly{1, -a[l]};
                return;
            }
            int mid = (l + r) >> 1;
            build(lc, l, mid, a);
            build(rc, mid + 1, r, a);
            tree[rt] = tree[lc] * tree[rc];
        }
        auto buildI(int rt, int l, int r, const vector<int> &a)
        {
            if (l == r)
            {
                tree[rt] = poly{-a[l], 1};
                return;
            }
            int mid = (l + r) >> 1;
            buildI(lc, l, mid, a);
            buildI(rc, mid + 1, r, a);
            tree[rt] = tree[lc] * tree[rc];
        }
        auto solve(int rt, int l, int r, vector<int> &ans, const poly &p)
        {
            if (l == r)
            {
                ans[l] = (int)((p.empty() ? 0 : p[0] + mod) % mod);
                return;
            }
            int mid = (l + r) >> 1;
            solve(lc, l, mid, ans, mulT(p, tree[rc]));
            solve(rc, mid + 1, r, ans, mulT(p, tree[lc]));
        }
        auto calc(int rt, int l, int r, const vector<int> &a)
        {
            if (l == r)
                return poly{a[l]};
            int mid = (l + r) >> 1;
            return calc(lc, l, mid, a) * tree[rc] + tree[lc] * calc(rc, mid + 1, r, a);
        }
#undef lc
#undef rc
    public:
        auto eval(const poly &F, const vector<int> &X)
        {
            int n = (int)F.size(), m = (int)X.size();
            vector<int> ans(m);
            if (!n || !m)
                return ans;
            tree.resize(m * 4, poly{});
            build(1, 0, m - 1, X);
            auto G = tree[1];
            G.resize(n);
            auto H = F ^ G.inv();
            H.resize(m);
            solve(1, 0, m - 1, ans, H);
            return ans;
        }
        auto interpolation(const vector<int> &X, vector<int> Y)
        {
            if (X.empty())
                return poly{};
            int n = (int)X.size();
            tree.resize(n * 4, poly{});
            buildI(1, 0, n - 1, X);

            vector<poly> _tree;
            swap(_tree, tree);
            auto W = eval(_tree[1].differ(), X);
            swap(_tree, tree);

            for (int i = 0; i < n; ++i)
                Y[i] = (int)((i64)Y[i] * quickpow(W[i]) % mod);

            auto ans = calc(1, 0, n - 1, Y);
            for (auto &i : ans)
                i = (int)((i + mod) % mod);
            return ans;
        }
    };
}
using namespace polynomial;
struct stirling
{
    static auto s1row(int n)
    {
        if (n == 0)
            return poly{1};
        if (n == 1)
            return poly{0, 1};
        auto F = s1row(n / 2);
        F = F * F.shift(n / 2);
        if (n & 1)
        {
            F.emplace_back();
            for (int i = n; i >= 1; --i)
                F[i] = (F[i - 1] + (n - 1) * F[i]) % mod;
        }
        return F;
    }
    static auto s2row(int n)
    {
        vector<i64> fac(n + 1), ifac(n + 1);
        fac[0] = 1;
        for (int i = 1; i <= n; ++i)
            fac[i] = fac[i - 1] * i % mod;
        ifac[n] = quickpow(fac[n]);
        for (int i = n; i >= 1; --i)
            ifac[i - 1] = ifac[i] * i % mod;

        poly F(n + 1), G(n + 1);
        for (int i = 0; i <= n; ++i)
        {
            F[i] = (i & 1 ? -1 : 1) * ifac[i];
            G[i] = quickpow(i, n) * ifac[i] % mod;
        }
        F = F * G;
        F.resize(n + 1);
        return F;
    }
    static auto s2col(int n, int m)
    {
        vector<i64> fac(n + 1), ifac(n + 1);
        fac[0] = 1;
        for (int i = 1; i <= n; ++i)
            fac[i] = fac[i - 1] * i % mod;
        ifac[n] = quickpow(fac[n]);
        for (int i = n; i >= 1; --i)
            ifac[i - 1] = ifac[i] * i % mod;

        poly F(n + 1);
        for (int i = 1; i <= n; ++i)
            F[i] = ifac[i];
        F = F.pow(m, m, m);
        for (int i = 0; i <= n; ++i)
            (F[i] *= fac[i] * ifac[m] % mod) %= mod;
        return F;
    }
};
struct Main
{
    int n, m;
    Main()
    {
        cin >> n >> m;
        cout << stirling::s2col(n, m) << '\n';
    }
};
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--)
        Main();
    return 0;
}
