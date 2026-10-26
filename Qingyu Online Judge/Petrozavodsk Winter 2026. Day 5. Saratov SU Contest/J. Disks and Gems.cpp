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
constexpr int MOD = 998244353;
constexpr int phi_MOD = MOD - 1; // 119 * (1 << 23)

// === Garner Template by DeepSeek Start ===
// ????????? g = gcd(a,b)???? x,y ?? a*x + b*y = g
LL egcd(LL a, LL b, LL &x, LL &y)
{
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    LL x1, y1;
    LL g = egcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

// ? a ?? mod ??????? gcd(a, mod) = 1
LL mod_inv(LL a, LL mod)
{
    LL x, y;
    LL g = egcd(a, mod, x, y);
    // g ?? 1
    x %= mod;
    if (x < 0)
        x += mod;
    return x;
}

// Garner ?????????? x ? a[i] (mod m[i])
// ?? m[i] ????????????
LL garner(const vector<LL> &a, const vector<LL> &m)
{
    const int n = int(a.size());
    LL ans = 0; // ????????
    LL M = 1;   // ??????????
    for (int i = 0; i < n; ++i)
    {
        // ?? M ?? m[i] ????
        LL Mi = M % m[i];
        LL inv = mod_inv(Mi, m[i]);

        // ???????? x_i = (a[i] - ans) * inv mod m[i]
        LL diff = (a[i] - ans) % m[i];
        if (diff < 0)
            diff += m[i];
        LL xi = (diff * inv) % m[i];

        // ??????????
        ans = ans + xi * M;
        M = M * m[i];
    }
    return ans; // ?????
}
// === Garner Template By DeepSeek End ===

LL pow3(LL b)
{
    LL res = 1, a = 3;
    while (b)
    {
        if (b & 1)
            res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

LL bf(int n, int k)
{
    LL ans = 1;
    for (int i = 0; i < k; ++i)
    {
        ans = ans * n % phi_MOD;
        n -= 2;
    }
    ans = pow3(ans);
    return ans;
}

namespace Init_2_23
{
    constexpr int N = 1 << 23;
    LL pre[N] = {}, pre_inv[N] = {};
    LL suf[N] = {}, suf_inv[N] = {};
    const bool __init = []() -> bool
    {
        pre[1] = 1;
        for (int x = 3; x < N; x += 2)
            pre[x] = pre[x - 2] * x % N;
        pre_inv[N - 1] = mod_inv(pre[N - 1], N);
        for (int x = N - 3; x > 0; x -= 2)
            pre_inv[x] = pre_inv[x + 2] * (x + 2) % N;
        suf[N - 1] = N - 1;
        for (int x = N - 3; x > 0; x -= 2)
            suf[x] = suf[x + 2] * x % N;
        suf_inv[1] = mod_inv(suf[1], N);
        for (int x = 3; x < N; x += 2)
            suf_inv[x] = suf_inv[x - 2] * (x - 2) % N;
#ifdef LOCAL
        assert(pre[N - 1] == 1);
        for (int x = 1; x < N; x += 2)
        {
            assert(pre[x] * pre_inv[x] % N == 1);
            assert(pre[x] * pre_inv[x] % N == 1);
        }
        dbg("Init_2_23 OK.\n");
#endif
        return 1;
    }();
    LL calc(const int n, const int k)
    {
#ifdef LOCAL
        LL _res = 1, _n = n;
        for (int i = 0; i < k; ++i)
        {
            _res = _res * _n % N;
            _n -= 2;
        }
#endif
        LL res = 1;
        int l = n - (k - 1) * 2, r = n;
        const int m = l / N;
        l -= m * N, r -= m * N;
        dbg("l = %d r = %d\n", l, r);
        if (r > N)
        {
            res = suf[l];
            const int mm = r / N;
            r -= mm * N;
            res = res * pre[r] % N;
            if (mm != 0)
                dbg("tested");
        }
        else
        {
            res = suf[l];
            if (r + 2 < N)
                res = res * suf_inv[r + 2] % N;
        }
#ifdef LOCAL
        dbg("n = %d k = %d _res = %lld res = %lld\n", n, k, _res, res);
        assert(_res == res);
#endif
        return res;
    }
}

struct Main
{
    int n, k;
    vector<LL> _a, _m{119, 1 << 23};
    Main()
    {
        _a.assign(2, 0ll);
    }
    void main()
    {
        cin >> n >> k;
        if (n == k << 1)
            --k;
        if (k >= 150)
        {
            if (n % 2 == 0)
            {
                cout << "1\n";
#ifdef LOCAL
                assert(bf(n, k) == 1);
#endif
            }
            else
            { // n is odd
#ifdef LOCAL
                {
                    LL _res = 1, _n = n;
                    for (int i = 0; i < k; ++i)
                    {
                        _res = (_res * _n) % 119;
                        _n -= 2;
                    }
                    assert(_res == 0);
                }
#endif
                _a[1] = Init_2_23::calc(n, k);
                const LL res = garner(_a, _m);
                const LL ans = pow3(res);
                cout << ans << "\n";
#ifdef LOCAL
                assert(bf(n, k) == ans);
#endif
            }
            return;
        }
        cout << bf(n, k) << "\n";
    }
};

int main()
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
