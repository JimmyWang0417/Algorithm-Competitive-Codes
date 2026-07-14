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
constexpr int mod = 998244353;

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
        constexpr static int inv2 = quickpow(2);
        constexpr static int inv3 = quickpow(3);
        constexpr static int imagUnit = 86583718;

        // O(1) 多维缓存
        inline static vector<int> rk[30];
        inline static vector<i64> rt{0, 1};
        inline static int len, limit;
        static auto init(int n)
        {
            len = 0, limit = 1;
            while (limit < n)
            {
                ++len;
                limit <<= 1;
            }
            if (rk[len].empty())
            {
                rk[len].resize(limit);
                for (int i = 0; i < limit; ++i)
                    rk[len][i] = (rk[len][i >> 1] >> 1) | ((i & 1) << (len - 1));
            }
            if ((int)rt.size() < limit)
            {
                int k = rt.size();
                rt.resize(limit);
                for (; k < limit; k <<= 1)
                {
                    i64 e = quickpow(3, (mod - 1) / (k << 1));
                    rt[k] = 1;
                    for (int i = 1; i < k; ++i)
                        rt[k + i] = rt[k + i - 1] * e % mod;
                }
            }
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

        // 修复：严谨的正数化，防止负数污染 NTT
        auto friend operator-(poly res)
        {
            for (auto &i : res)
            {
                i %= mod;
                if (i < 0)
                    i += mod;
                i = i ? mod - i : 0;
            }
            return res;
        }

        auto friend operator+(const poly &lhs, const poly &rhs)
        {
            poly res(max(lhs.size(), rhs.size()));
            for (int i = 0; i < (int)res.size(); ++i)
            {
                i64 v1 = i < (int)lhs.size() ? lhs[i] : 0;
                i64 v2 = i < (int)rhs.size() ? rhs[i] : 0;
                res[i] = (v1 + v2) % mod;
            }
            return res;
        }

        auto friend operator-(const poly &lhs, const poly &rhs)
        {
            poly res(max(lhs.size(), rhs.size()));
            for (int i = 0; i < (int)res.size(); ++i)
            {
                i64 v1 = i < (int)lhs.size() ? lhs[i] : 0;
                i64 v2 = i < (int)rhs.size() ? rhs[i] : 0;
                res[i] = (v1 - v2) % mod;
                if (res[i] < 0)
                    res[i] += mod; // 防负数
            }
            return res;
        }

        auto friend operator*(poly lhs, i64 rhs)
        {
            rhs %= mod;
            if (rhs < 0)
                rhs += mod;
            for (auto &i : lhs)
                i = i * rhs % mod;
            return lhs;
        }

        auto friend operator/(const poly &lhs, i64 rhs)
        {
            return lhs * quickpow(rhs);
        }

        auto NTT()
        {
            auto &dp = (*this);
            i64 *__restrict A = dp.data();
            const int *__restrict R = rk[len].data();
            for (int i = 0; i < limit; ++i)
                if (i < R[i])
                    std::swap(A[i], A[R[i]]);

            const i64 *__restrict RT = rt.data();
            for (int mid = 1; mid < limit; mid <<= 1)
            {
                const i64 *__restrict R_row = RT + mid;
                for (int i = 0; i < limit; i += mid << 1)
                {
                    i64 *__restrict A_row = A + i;
                    for (int j = 0; j < mid; ++j)
                    {
                        i64 x = A_row[j], y = A_row[j + mid] * R_row[j] % mod;
                        A_row[j] = x + y >= mod ? x + y - mod : x + y;
                        A_row[j + mid] = x - y < 0 ? x - y + mod : x - y;
                    }
                }
            }
        }
        auto INTT()
        {
            NTT();
            std::reverse(begin() + 1, begin() + limit);
            i64 inv = quickpow(limit);
            i64 *__restrict A = data();
            for (int i = 0; i < limit; ++i)
                A[i] = A[i] * inv % mod;
        }
        auto reverse() { std::reverse(begin(), end()); }

        auto friend operator*(poly lhs, poly rhs)
        {
            if (lhs.empty() || rhs.empty())
                return poly{};
            auto up = lhs.size() + rhs.size() - 1;
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

        auto inv(int n) const
        {
            if (n == 1)
                return poly{quickpow(at(0))};
            poly F = inv((n + 1) / 2), G(begin(), begin() + n);
            init(n * 2);
            F.resize(limit), F.NTT();
            G.resize(limit), G.NTT();
            for (int i = 0; i < limit; ++i)
                F[i] = (2 - F[i] * G[i] % mod + mod) % mod * F[i] % mod;
            F.INTT(), F.resize(n);
            return F;
        }
        auto inv() const { return inv((int)size()); }

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

        auto integral() const
        {
            poly inv(size() + 1), res(size() + 1);
            inv[1] = 1;
            for (int i = 2; i <= (int)size(); ++i)
                inv[i] = (mod - mod / i) * inv[mod % i] % mod;
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

        auto ln() const
        {
            auto res = differ() * inv();
            res.resize(size() - 1);
            return res.integral();
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
                F[i] = F[i] * (1 - lnF[i] + G[i] + mod) % mod;
            F.INTT(), F.resize(n);
            return F;
        }
        auto exp() const { return exp((int)size()); }
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

        auto asin() const
        {
            auto res = (*this) * (*this);
            res.resize(size());
            res[0] = (1 - res[0] + mod) % mod;
            for (int i = 1; i < (int)size(); ++i)
                res[i] = res[i] ? mod - res[i] : 0;
            res = differ() * res.sqrt().inv();
            res.resize(size() - 1);
            return res.integral();
        }
        auto acos() const
        {
            auto res = asin();
            for (int i = 0; i < (int)size(); ++i)
                res[i] = res[i] ? mod - res[i] : 0;
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
            if ((i64)fir * r >= (int)size())
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

        // 修复 1D BostanMori: 不能暴力 -G，因为 G(-x) 只需要对奇数项取反！
        static auto bostanMori(int n, poly F, poly G)
        {
            if (!n)
                return F[0] * quickpow(G[0]) % mod;
            if (n + 1 < (int)F.size())
                F.resize(n + 1);
            if (n + 1 < (int)G.size())
                G.resize(n + 1);

            poly H = G;
            for (int i = 1; i < (int)H.size(); i += 2)
            {
                H[i] %= mod;
                if (H[i] < 0)
                    H[i] += mod;
                H[i] = H[i] ? mod - H[i] : 0;
            }

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
            i64 *__restrict F_ptr = F.data();
            i64 *__restrict G_ptr = G.data();

            for (int i = 0; i < n; ++i)
            {
                const i64 *__restrict a_row = a[i].data();
                int sz = (int)a[i].size();
                for (int j = 0; j < sz; ++j)
                    F_ptr[i * pad + j] = a_row[j];
            }
            for (int i = 0; i < m; ++i)
            {
                const i64 *__restrict b_row = b[i].data();
                int sz = (int)b[i].size();
                for (int j = 0; j < sz; ++j)
                    G_ptr[i * pad + j] = b_row[j];
            }
            F = F * G;

            const i64 *__restrict res_ptr = F.data();
            vpoly c(n + m - 1, poly(pad));
            for (int i = 0; i < n + m - 1; ++i)
            {
                i64 *__restrict c_row = c[i].data();
                for (int j = 0; j < pad; ++j)
                    c_row[j] = res_ptr[i * pad + j];
            }
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
                {
                    j %= mod;
                    if (j < 0)
                        j += mod;
                    j = j ? mod - j : 0;
                }
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
                i64 val = dp[i] % mod;
                if (val < 0)
                    val += mod;
                Q.push_back({(i64)!i, val ? mod - val : 0}); // 修复负数取模
            }
            poly F = bostanMori(n - 1, P, Q), G(n);
            F.resize(n);

            poly inv(n);
            inv[1] = 1;
            for (int i = 2; i < n; ++i)
                inv[i] = (mod - mod / i) * inv[mod % i] % mod;

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
            i64 *__restrict F_ptr = F.data();
            i64 *__restrict G_ptr = G.data();

            for (int i = 0; i < n; ++i)
            {
                const i64 *__restrict a_row = a[i].data();
                int sz = (int)a[i].size();
                for (int j = 0; j < sz; ++j)
                    F_ptr[i * p + j] = a_row[j];
            }
            for (int i = 0; i < m; ++i)
            {
                const i64 *__restrict b_row = b[i].data();
                int sz = (int)b[i].size();
                for (int j = 0; j < sz && j < q; ++j)
                    G_ptr[(m - 1 - i) * p + (q - 1 - j)] = b_row[j]; // 这里依然保留关键修改
            }
            F = F * G;

            const i64 *__restrict res_ptr = F.data();
            vpoly c(n - m + 1, poly(p - q + 1));
            for (int i = 0; i < n - m + 1; ++i)
            {
                i64 *__restrict c_row = c[i].data();
                for (int j = 0; j < p - q + 1; ++j)
                    c_row[j] = res_ptr[(i + m - 1) * p + (j + q - 1)];
            }
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
                {
                    j %= mod;
                    if (j < 0)
                        j += mod;
                    j = j ? mod - j : 0;
                }
            G = G * H;
            vpoly A, B;
            for (int i = 0; i < (int)G.size(); i += 2)
                B.emplace_back(G[i]);
            vpoly F = bostanMoriT(n / 2, P, B);
            for (int i = n & 1; i < (int)F.size(); i += 2)
                A.emplace_back(F[i]);
            int p = (int)H.size(), q = (int)F[0].size();
            A.resize(p * 2);
            for (int i = 0, j = 0; i < p * 2; i++)
            {
                if ((i & 1) == (n & 1) && j < (int)F.size())
                    A[i] = F[j++];
                else
                    A[i] = poly(q, 0);
            }
            return mulT(A, H);
        }

        // 彻底还原了你原本绝妙的 `Q` 生成逻辑与翻转提取，这是最漂亮且自洽的做法
        static auto comp(poly F, poly G)
        {
            int n = (int)F.size();
            G.resize(n);
            vpoly Q;
            for (int i = 0; i < n; i++)
            {
                i64 val = G[i] % mod;
                if (val < 0)
                    val += mod;
                Q.push_back({(i64)!i, val ? mod - val : 0}); // 防止负数
            }
            vpoly P = bostanMoriT(n - 1, F, Q);
            poly H(n);
            for (int i = 0; i < n; i++)
            {
                i64 val = 0;
                if (i < (int)P.size() && !P[i].empty())
                    val = P[i].front();
                H[n - 1 - i] = val; // 完美转置提取，无需多此一举地反转 F
            }
            return H;
        }
    };
}
using namespace polynomial;

struct Main
{
    int n, m;
    Main()
    {
        cin >> n >> m;
        poly F(n + 1), G(m + 1);
        cin >> F >> G;
        cout << poly::comp(F, G) << '\n';
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