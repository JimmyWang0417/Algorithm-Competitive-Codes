#include <bits/stdc++.h>
#include <cassert>
using namespace std;

// #define LOCAL
#ifdef LOCAL
#define dbg(...) fprintf(stderr, ##__VA_ARGS__)
#else
#define dbg(...) 42
#endif

using LL = long long;
#define all(x) (x).begin(), (x).end()
#define allr(x) (x).rbegin(), (x).rend()

template <class S>
inline bool updmn(S &x, const S y)
{
    if (y < x)
    {
        x = y;
        return 1;
    }
    return 0;
}

template <class S>
inline bool updmx(S &x, const S y)
{
    if (x < y)
    {
        x = y;
        return 1;
    }
    return 0;
}

template <class S, int K>
    requires(is_integral_v<S> && K <= sizeof(S) * 8)
struct _LB
{ // linear?basis
    array<S, K> a;
    int sz;
    _LB() { init(); }
    void init()
    {
        fill(all(a), 0);
        sz = 0;
    }
    bool insert(S x)
    {
        for (int i = K - 1; i >= 0; --i)
        {
            if (!(x >> i))
                continue;
            if (!a[i])
            {
                a[i] = x;
                ++sz;
                return 1;
            }
            x ^= a[i];
        }
        return 0;
    }
    bool find(S x)
    {
        for (int i = K - 1; i >= 0; --i)
        {
            if (!(x >> i))
                continue;
            if (!a[i])
                return 0;
            x ^= a[i];
        }
        return 1;
    }
};

constexpr int MOD = 998244353;
constexpr int N = int(2e5 + 5);

int pw2[N];
const bool __init_pw2 = []() -> bool
{
    pw2[0] = 1;
    for (int x = 1; x < N; ++x)
    {
        pw2[x] = pw2[x - 1] * 2;
        if (pw2[x] >= MOD)
            pw2[x] -= MOD;
    }
    return 1;
}();

LL fc[N], fc_inv[N];
LL ksm(LL a, LL b)
{
    a %= MOD;
    LL r = 1;
    while (b)
    {
        if (b & 1)
            r = r * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return r;
}
const bool __init_fc = []() -> bool
{
    fc[0] = fc_inv[0] = 1;
    for (int i = 1; i < N; ++i)
        fc[i] = fc[i - 1] * i % MOD;
    fc_inv[N - 1] = ksm(fc[N - 1], MOD - 2);
    for (int i = N - 2; i > 0; --i)
        fc_inv[i] = fc_inv[i + 1] * (i + 1) % MOD;
    return 1;
}();
LL C(const int x, const int y)
{
    return fc[x] * fc_inv[y] % MOD * fc_inv[x - y] % MOD;
}

vector<int> fac[N];
const bool __init_fac = []() -> bool
{
    for (int x = 1; x < N; ++x)
        for (int y = x << 1; y < N; y += x)
            fac[y].push_back(x);
    return 1;
}();

struct Main
{
    using LB = _LB<int, 18>;
    int n;
    vector<int> a, cnt;
    LL ans = 0;
    void main()
    {
        cin >> n;
        a.assign(n, 0);
        cnt.assign(n + 1, 0);
        for (auto &x : a)
        {
            cin >> x;
            ++cnt[x];
        }
        calc_0();
        for (int x = 1; x <= n; ++x)
        {
            if (!cnt[x])
                continue;
            calc_x(x);
        }
        cout << ans << "\n";
    }
    void calc_0()
    {
        LB lb;
        for (auto x : a)
            lb.insert(x);
        dbg("calc_0 = %d\n", pw2[n - lb.sz]);
        madd(ans, pw2[n - lb.sz]);
        msub(ans, 1ll);
    }
    void calc_x(const int x)
    {
        LB lb;
        int tot = 0;
        for (auto d : fac[x])
        {
            if (!cnt[d])
                continue;
            tot += cnt[d];
            lb.insert(d);
        }
        const int c = cnt[x];
        LL mul = 0;
        for (int i = 1; i <= c; i += 2)
        {
            madd(mul, C(c, i));
        }
        dbg("calc_x(%d) tot = %d add = %lld\n", x, tot, mul * pw2[tot - lb.sz] % MOD);
        madd(ans, mul * pw2[tot - lb.sz] % MOD);
    }
    static void madd(LL &x, const LL y)
    {
        if ((x += y) >= MOD)
            x -= MOD;
    }
    static void msub(LL &x, const LL y)
    {
        if ((x -= y) < 0)
            x += MOD;
    }
};

signed main()
{
#ifndef LOCAL
    cin.tie(nullptr)->sync_with_stdio(false);
#endif
    int t;
    cin >> t;
    while (t--)
        Main{}.main();
    return 0;
}
