#include <bits/stdc++.h>
using namespace std;

// #define LOCAL
#ifdef LOCAL
#define dbg(...) fprintf(stderr, ##__VA_ARGS__)
#else
#define dbg(...) 42
#endif

using LL = long long;

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

constexpr int MOD = 998244353;
constexpr LL ksm(LL a, LL b)
{
    if (b < 0)
        b += MOD - 1;
    a %= MOD;
    LL res = 1;
    while (b)
    {
        if (b & 1)
            res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}
constexpr LL inv2 = ksm(2, MOD - 2);

constexpr int N = int(1e6) + 5;
LL fc[N], fc_inv[N];
const bool __init = []() -> bool
{
    fc[1] = 1;
    for (int i = 2; i < N; ++i)
        fc[i] = fc[i - 1] * i % MOD;
    fc_inv[N - 1] = ksm(fc[N - 1], MOD - 2);
    for (int i = N - 2; i > 0; --i)
        fc_inv[i] = fc_inv[i + 1] * (i + 1) % MOD;
    return 1;
}();

struct Main
{
    int n;
    LL ans;
    void main()
    {
        cin >> n;
        const int k = n / 2;
        if (n % 2 == 0)
        {
            const LL _1 = ksm(k, k - 2);
            const LL _2 = _1 * _1 % MOD;
            const LL _3 = fc[n] * fc_inv[k] % MOD;
            ans = _2 * _3 % MOD;
        }
        else
        {
            const LL _1 = ksm(k, k - 2) * 4 % MOD;
            const LL _2 = ksm(k + 1, k - 2);
            const LL _3 = fc[n] * fc_inv[k + 1] % MOD;
            const LL _4 = inv2 * k % MOD * (k + 1) % MOD;
            ans = _1 * _2 % MOD * _3 % MOD * _4 % MOD;
        }
        cout << ans << "\n";
    }
};

int main()
{
#ifndef LOCAL
    cin.tie(nullptr)->sync_with_stdio(false);
#endif
    Main{}.main();
    return 0;
}
