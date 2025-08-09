#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr int N = 4e5 + 5;
constexpr int mod = 998244353;
constexpr auto quickpow(ll a, int b = mod - 2)
{
    ll res = 1;
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
{ // NTT模数 998244353, 1004535809
    constexpr int inv2 = quickpow(2);
    constexpr int inv3 = quickpow(3);
    constexpr int imagUnit = 86583718;
    int limit, len;
    vector<int> rk;
    auto init(int n)
    {
        len = 0, limit = 1;
        while (limit < n)
        {
            limit <<= 1;
            ++len;
        }
        rk.resize(limit);
        for (int i = 0; i < limit; ++i)
            rk[i] = (rk[i >> 1] >> 1) | ((i & 1) << (len - 1));
    }
    struct poly
    {
        vector<ll> dp;
        poly() = default;
        poly(int _n) { dp.resize(_n); }
        poly(vector<ll> _dp) { dp = _dp; }

        auto size() const { return (int)dp.size(); }
        auto resize(int _n) { dp.resize(_n); }

        auto operator[](const int &x) const { return dp[x]; }
        auto &operator[](const int &x) { return dp[x]; }

        auto friend &operator>>(istream &in, poly &p)
        {
            for (auto &i : p.dp)
                in >> i;
            return in;
        }
        auto friend &operator<<(ostream &out, const poly &p)
        {
            for (auto i : p.dp)
                out << (i + mod) % mod << ' ';
            return out;
        }

        auto friend operator+(poly lhs, poly rhs)
        {
            poly res(max(lhs.size(), rhs.size()));
            lhs.resize(res.size()), rhs.resize(res.size());
            for (int i = 0; i < res.size(); ++i)
                res[i] = (lhs[i] + rhs[i]) % mod;
            return res;
        }
        auto friend operator-(poly lhs, poly rhs)
        {
            poly res(max(lhs.size(), rhs.size()));
            lhs.resize(res.size()), rhs.resize(res.size());
            for (int i = 0; i < res.size(); ++i)
                res[i] = (lhs[i] - rhs[i]) % mod;
            return res;
        }
        auto friend operator*(poly res, ll rhs)
        {
            for (auto &i : res.dp)
                (i *= rhs) %= mod;
            return res;
        }
        auto friend operator/(poly res, ll rhs)
        {
            return res * quickpow(rhs);
        }

        auto NTT()
        {
            for (int i = 0; i < limit; ++i)
                if (i < rk[i])
                    swap(dp[i], dp[rk[i]]);
            for (int mid = 1; mid < limit; mid <<= 1)
            {
                ll gn = quickpow(3, (mod - 1) / (mid << 1));
                for (int i = 0; i < limit; i += mid << 1)
                {
                    ll g = 1;
                    for (int j = 0; j < mid; ++j, (g *= gn) %= mod)
                    {
                        ll x = dp[i + j], y = dp[i + j + mid] * g % mod;
                        dp[i + j] = (x + y) % mod;
                        dp[i + j + mid] = (x - y) % mod;
                    }
                }
            }
        }
        auto INTT()
        {
            for (int i = 0; i < limit; ++i)
                if (i < rk[i])
                    swap(dp[i], dp[rk[i]]);
            for (int mid = 1; mid < limit; mid <<= 1)
            {
                ll gn = quickpow(inv3, (mod - 1) / (mid << 1));
                for (int i = 0; i < limit; i += mid << 1)
                {
                    ll g = 1;
                    for (int j = 0; j < mid; ++j, (g *= gn) %= mod)
                    {
                        ll x = dp[i + j], y = dp[i + j + mid] * g % mod;
                        dp[i + j] = (x + y) % mod;
                        dp[i + j + mid] = (x - y) % mod;
                    }
                }
            }
            ll inv = quickpow(limit);
            for (int i = 0; i < limit; ++i)
                (dp[i] *= inv) %= mod;
        }

        // 多项式乘法
        auto friend operator*(poly lhs, poly rhs)
        {
            int up = lhs.size() + rhs.size() - 1;
            init(up);
            lhs.resize(limit), rhs.resize(limit);
            lhs.NTT(), rhs.NTT();
            poly res(limit);
            for (int i = 0; i < limit; ++i)
                res[i] = lhs[i] * rhs[i] % mod;
            res.INTT();
            res.resize(up);
            return res;
        }

        // 多项式求逆和多项式除法
        auto inv(int n) const
        {
            poly F = poly(vector<ll>{quickpow(dp[0])}), G;
            for (int l = 2; (l >> 1) < n; l <<= 1)
            {
                G.resize(l);
                for (int i = 0; i < l; ++i)
                    G[i] = i < n ? dp[i] : 0;
                init(l * 2);
                F.resize(limit), G.resize(limit);
                F.NTT(), G.NTT();
                for (int i = 0; i < limit; ++i)
                    F[i] = (2 - F[i] * G[i] % mod) * F[i] % mod;
                F.INTT();
                F.resize(l);
            }
            F.resize(n);
            return F;
        }
        auto inv() const { return inv(size()); }
        auto reverse() { std::reverse(dp.begin(), dp.end()); }
        auto friend operator/(poly lhs, poly rhs)
        {
            lhs.reverse(), rhs.reverse();
            int up = lhs.size() - rhs.size() + 1;
            lhs.resize(up), rhs.resize(up);
            auto res = lhs * rhs.inv();
            res.resize(up);
            res.reverse();
            return res;
        }
        auto friend operator%(poly lhs, poly rhs)
        {
            auto res = lhs - lhs / rhs * rhs;
            res.resize(rhs.size() - 1);
            return res;
        }

        // 多项式开根
        auto sqrt(int n) const
        {
            if (n == 1) // 其实要用二次剩余，但是洛谷模板保证a0=1
                return poly(vector<ll>{1});
            poly F = sqrt((n + 1) / 2), G = poly(vector<ll>(dp.begin(), dp.begin() + n));
            F.resize(n);
            poly invF = F.inv();
            init(n * 2);
            F.resize(limit), G.resize(limit), invF.resize(limit);
            F.NTT(), G.NTT(), invF.NTT();
            for (int i = 0; i < limit; ++i)
                F[i] = (F[i] * F[i] + G[i]) % mod * inv2 % mod * invF[i] % mod;
            F.INTT();
            F.resize(n);
            return F;
        }
        auto sqrt() const { return sqrt(size()); }

        // 积分和求导
        auto integral() const
        {
            vector<ll> inv(size() + 1);
            poly res(size() + 1);
            inv[1] = 1;
            for (int i = 2; i <= size(); ++i)
                inv[i] = (mod - mod / i) * inv[mod % i] % mod;
            for (int i = 1; i <= size(); ++i)
                res[i] = dp[i - 1] * inv[i] % mod;
            return res;
        }
        auto differ() const
        {
            poly res(size() - 1);
            for (int i = 1; i < size(); ++i)
                res[i - 1] = dp[i] * i % mod;
            return res;
        }

        // 指数函数和对数函数，得保证a0 = 0
        auto ln() const
        {
            auto res = differ() * inv();
            res.resize(size() - 1);
            return res.integral();
        }
        auto exp(int n) const
        {
            if (n == 1)
                return poly(vector<ll>{1});
            poly F = exp((n + 1) / 2), G(vector<ll>(dp.begin(), dp.begin() + n));
            F.resize(n);
            poly lnF = F.ln();
            init(n * 2);
            F.resize(limit), G.resize(limit), lnF.resize(limit);
            F.NTT(), G.NTT(), lnF.NTT();
            for (int i = 0; i < limit; ++i)
                F[i] = F[i] * (1 - lnF[i] + G[i]) % mod;
            F.INTT();
            F.resize(n);
            return F;
        }
        auto exp() const { return exp(size()); }

        // 三角函数（得保证a0 = 0）
        auto cos() const
        {
            return ((*this * imagUnit).exp() + (*this * (-imagUnit)).exp()) * inv2;
        }
        auto sin() const
        {
            return ((*this * imagUnit).exp() - (*this * (-imagUnit)).exp()) * (-(ll)inv2 * imagUnit % mod);
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
            for (int i = 1; i < size(); ++i)
                res[i] = -res[i];
            res = differ() * res.sqrt().inv();
            res.resize(size() - 1);
            return res.integral();
        }
        auto acos() const
        {
            auto res = asin();
            for (int i = 0; i < size(); ++i)
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
    };

    // 多项式多点求值 | 快速差值
    struct lagrange
    {
#define lc (rt << 1)
#define rc (rt << 1 | 1)
        vector<int> treearray;
        vector<poly> tree, pol;
        auto build(int rt, int l, int r)
        {
            if (l == r)
            {
                tree[rt] = poly({-treearray[l], 1});
                return;
            }
            int mid = (l + r) >> 1;
            build(lc, l, mid);
            build(rc, mid + 1, r);
            tree[rt] = tree[lc] * tree[rc];
        };
        auto solve(int rt, int l, int r, vector<int> &p)
        {
            if ((int)pol[rt].size() - 1 <= 1024)
            {
                for (int i = l; i <= r; ++i)
                {
                    auto x = treearray[i], all = (int)pol[rt].size() - 1;
                    const auto &q = pol[rt];
                    vector<ll> pw(17, 1);
                    for (int j = 1; j <= 16; ++j)
                        pw[j] = pw[j - 1] * x % mod;
                    ll res = q[all];
                    ll c1, c2, c3, c4;
                    for (int j = all - 1; j >= 15; j -= 16)
                    {
                        c1 = res * pw[16] + q[j] * pw[15] + q[j - 1] * pw[14] + q[j - 2] * pw[13], c1 %= mod;
                        c2 = q[j - 3] * pw[12] + q[j - 4] * pw[11] + q[j - 5] * pw[10] + q[j - 6] * pw[9], c2 %= mod;
                        c3 = q[j - 7] * pw[8] + q[j - 8] * pw[7] + q[j - 9] * pw[6] + q[j - 10] * pw[5], c3 %= mod;
                        c4 = q[j - 11] * pw[4] + q[j - 12] * pw[3] + q[j - 13] * pw[2] + q[j - 14] * pw[1], c4 %= mod;
                        res = (c1 + c2 + c3 + c4 + q[j - 15]) % mod;
                    }
                    for (int j = all % 16 - 1; j >= 0; --j)
                        res = (res * x + q[j]) % mod;
                    p[i] = (int)res;
                }
                return;
            }
            int mid = (l + r) >> 1;
            pol[lc] = pol[rt] % tree[lc];
            pol[rc] = pol[rt] % tree[rc];
            solve(lc, l, mid, p);
            solve(rc, mid + 1, r, p);
        };
        auto multipointEval(const poly &p, const vector<int> &q)
        {
            int n = (int)q.size();
            vector<int> r(n);
            tree.resize(n * 4), pol.resize(n * 4);
            treearray = q;
            build(1, 0, n - 1);
            pol[1] = p;
            solve(1, 0, n - 1, r);
            return r;
        }
        auto interpolation(const vector<int> &X, vector<int> Y)
        {
            int n = (int)X.size();
            vector<ll> p(n, 1);
            vector<int> q(n);
            tree.resize(n * 4), pol.resize(n * 4);
            treearray = X;
            build(1, 0, n - 1);
            function<void(int, int, int)> dfs = [&](int rt, int l, int r)
            {
                if (l == r)
                    return;
                int mid = (l + r) >> 1;
                pol[lc] = tree[rc], pol[rc] = tree[lc];
                solve(lc, l, mid, q);
                solve(rc, mid + 1, r, q);
                for (int i = l; i <= r; ++i)
                    (p[i] *= q[i]) %= mod;
                dfs(lc, l, mid);
                dfs(rc, mid + 1, r);
            };
            dfs(1, 0, n - 1);
            for (int i = 0; i < n; ++i)
                Y[i] = (int)((Y[i] * quickpow(p[i])) % mod);
            function<poly(int, int, int)> calc = [&](int rt, int l, int r)
            {
                if (l == r)
                    return poly(vector<ll>{Y[l]});
                int mid = (l + r) >> 1;
                return calc(lc, l, mid) * tree[rc] + tree[lc] * calc(rc, mid + 1, r);
            };
            return calc(1, 0, n - 1);
        }
#undef lc
#undef rc
    };
}
using namespace polynomial;
auto _main()
{
    int n, m;
    cin >> n >> m;
    poly p(n + 1);
    vector<int> q(m);
    cin >> p;
    for (int &i : q)
        cin >> i;
    for (int i : lagrange().multipointEval(p, q))
        cout << (i + mod) % mod << '\n';
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    // cin >> T;
    for (int cas = 1; cas <= T; ++cas)
        _main();
    return 0;
}