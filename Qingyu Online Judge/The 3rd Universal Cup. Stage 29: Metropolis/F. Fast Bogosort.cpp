#include <bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
constexpr int N = 4e5 + 5;
constexpr int mod = 998244353;
constexpr inline ll quickpow(ll a, int b = mod - 2)
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
constexpr int inv3 = quickpow(3);
int len, limit, rk[N];
inline void init(int n)
{
    len = 0, limit = 1;
    while (limit <= n)
    {
        ++len;
        limit <<= 1;
    }
    for (int i = 0; i < limit; ++i)
        rk[i] = (rk[i >> 1] >> 1) | ((i & 1) << (len - 1));
}
struct polygon
{
    vector<ll> dp;
    inline int size() const
    {
        return (int)dp.size();
    }
    inline auto &operator[](int x)
    {
        return dp[x];
    }
    inline auto operator[](int x) const
    {
        return dp[x];
    }
    inline void resize(int n)
    {
        dp.resize(n);
    }
    inline void NTT()
    {
        for (int i = 0; i < limit; ++i)
            if (i < rk[i])
                swap(dp[i], dp[rk[i]]);
        for (int mid = 1; mid < limit; mid <<= 1)
        {
            const auto gn = quickpow(3, (mod - 1) / (mid << 1));
            for (int i = 0; i < limit; i += mid << 1)
            {
                ll g = 1;
                for (int j = 0; j < mid; ++j, (g *= gn) %= mod)
                {
                    auto x = dp[i + j], y = dp[i + j + mid] * g % mod;
                    dp[i + j] = (x + y) % mod;
                    dp[i + j + mid] = (x - y) % mod;
                }
            }
        }
    }
    inline void INTT()
    {
        for (int i = 0; i < limit; ++i)
            if (i < rk[i])
                swap(dp[i], dp[rk[i]]);
        for (int mid = 1; mid < limit; mid <<= 1)
        {
            const auto gn = quickpow(inv3, (mod - 1) / (mid << 1));
            for (int i = 0; i < limit; i += mid << 1)
            {
                ll g = 1;
                for (int j = 0; j < mid; ++j, (g *= gn) %= mod)
                {
                    auto x = dp[i + j], y = dp[i + j + mid] * g % mod;
                    dp[i + j] = (x + y) % mod;
                    dp[i + j + mid] = (x - y) % mod;
                }
            }
        }
        const auto invlimit = quickpow(limit);
        for (int i = 0; i < limit; ++i)
            (dp[i] *= invlimit) %= mod;
    }
    inline auto operator+(const polygon &rhs) const
    {
        assert(size() != rhs.size());
        polygon res(size());
        for (int i = 0; i < size(); ++i)
            res.dp[i] = (dp[i] + rhs[i]) % mod;
        return res;
    }
    inline auto operator-(const polygon &rhs) const
    {
        assert(size() != rhs.size());
        polygon res(size());
        for (int i = 0; i < size(); ++i)
            res.dp[i] = (dp[i] - rhs[i]) % mod;
        return res;
    }
    inline friend polygon operator*(polygon lhs, polygon rhs)
    {
        int L = lhs.size(), R = rhs.size();
        polygon res;
        init(L + R - 1);
        lhs.resize(limit), rhs.resize(limit), res.resize(limit);
        lhs.NTT(), rhs.NTT();
        for (int i = 0; i < limit; ++i)
            res[i] = lhs[i] * rhs[i] % mod;
        res.INTT();
        res.resize(L + R - 1);
        return res;
    }
    polygon(int _n = 0) { dp.resize(_n); }
};
int n;
ll fac[N], ifac[N];
ll P[N], F[N];
inline void solveP(int l, int r)
{
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    solveP(l, mid);
    polygon A(mid - l + 1), B(r - l + 1), C;
    for (int i = 0; i < A.size(); ++i)
        A[i] = P[i + l];
    for (int i = 0; i < B.size(); ++i)
        B[i] = fac[i];
    C = A * B;
    for (int i = mid + 1; i <= r; ++i)
        (P[i] -= C[i - l]) %= mod;
    solveP(mid + 1, r);
}
inline void solveQ(int l, int r)
{
    if (l == r)
    {
        (F[l] *= quickpow(fac[l] - P[l])) %= mod;
        return;
    }
    int mid = (l + r) >> 1;
    solveQ(l, mid);
    polygon A(mid - l + 1), B(r - l + 1), C;
    for (int i = 0; i < A.size(); ++i)
        A[i] = (i + l > 1 ? F[i + l] - 1 : 0) * fac[i + l] % mod;
    for (int i = 0; i < B.size(); ++i)
        B[i] = P[i];
    C = A * B;
    for (int i = mid + 1; i <= r; ++i)
        (F[i] += C[i - l]) %= mod;

    for (int i = 0; i < A.size(); ++i)
        A[i] = F[i + l] * P[i + l] % mod;
    for (int i = 0; i < B.size(); ++i)
        B[i] = fac[i];
    C = A * B;
    for (int i = mid + 1; i <= r; ++i)
        (F[i] += C[i - l]) %= mod;
    solveQ(mid + 1, r);
}
int a[N], b[N];
inline void _main()
{
    cin >> n;
    fac[0] = 1;
    for (int i = 1; i <= n; ++i)
        fac[i] = fac[i - 1] * i % mod;
    ifac[n] = quickpow(fac[n]);
    for (int i = n; i >= 1; --i)
        ifac[i - 1] = ifac[i] * i % mod;
    for (int i = 0; i <= n; ++i)
        P[i] = F[i] = fac[i];
    solveP(1, n);
    solveQ(1, n);
    for (int i = 1; i <= n; ++i)
    {
        cin >> a[i];
        b[a[i]] = i;
    }
    ll ans = 0;
    for (int i = 1, j = 1, k = 1; i <= n; i = j + 1)
    {
        j = i;
        while (k <= j)
        {
            j = max({j, a[k], b[k]});
            ++k;
        }
        ans += F[j - i + 1];
    }
    cout << (ans % mod + mod) % mod << '\n';
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--)
        _main();
    return 0;
}