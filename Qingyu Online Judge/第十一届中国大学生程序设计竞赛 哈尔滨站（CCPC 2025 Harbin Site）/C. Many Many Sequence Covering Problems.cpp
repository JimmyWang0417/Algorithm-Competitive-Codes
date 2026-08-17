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
constexpr int V = 5000;
struct Main
{
    int n;
    vector<int> a, b, c, d, e;
    template <typename T>
    auto calc(const T &p, int l, int r)
    {
        auto res = p[r];
        if (l > 0)
            (res -= p[l - 1]) %= mod;
        return res;
    }
    Main()
    {
        cin >> n;
        a.resize(n + 5);
        b.resize(n + 5);
        c.resize(n + 5);
        d.resize(n + 5);
        e.resize(n + 5);

        i64 tot = 1;

        a[0] = a[n + 1] = 0;
        for (int i = 1; i <= n; ++i)
        {
            cin >> a[i];
            (tot *= (a[i] < 0 ? -a[i] + 1 : 1)) %= mod;
        }

        for (int i = 1; i <= n; ++i)
        {
            cin >> b[i];
            (tot *= (b[i] < 0 ? -b[i] + 1 : 1)) %= mod;
        }
        for (int i = 1; i <= n; ++i)
        {
            cin >> c[i];
            (tot *= (c[i] < 0 ? -c[i] + 1 : 1)) %= mod;
        }

        for (int i = 1; i <= n; ++i)
        {
            cin >> d[i];
            (tot *= (d[i] < 0 ? -d[i] + 1 : 1)) %= mod;
        }
        for (int i = 1; i <= n; ++i)
        {
            cin >> e[i];
            (tot *= (e[i] < 0 ? -e[i] + 1 : 1)) %= mod;
        }

        array<i64, V + 1> f({}), g({});
        array<i64, V + 1> cnt0({}), cnt1({}), cnt2({});
        array<i64, V + 1> sum0({}), sum1({});

        for (int i = 0; i <= V; ++i)
            cnt0[i] = 1;
        for (int i = 1; i <= n + 1; ++i)
        {
            auto cntb = (b[i] < 0 ? -b[i] + 1 : 1);
            auto cntc = (c[i - 1] < 0 ? -c[i - 1] + 1 : 1);
            auto cntd = (d[i] < 0 ? -d[i] + 1 : 1);
            auto cnte = (e[i - 1] < 0 ? -e[i - 1] + 1 : 1);

            auto sumb = (b[i] < 0 ? -b[i] * (-b[i] + 1) / 2 : b[i]) % mod;
            auto sumc = (c[i - 1] < 0 ? -c[i - 1] * (-c[i - 1] + 1) / 2 : c[i - 1]) % mod;

            for (int j = 0; j <= V; ++j)
            {
                if ((a[i] >= 0 && j != a[i]) || (a[i] < 0 && j > -a[i]))
                    continue;
                if (d[i] >= 0)
                {
                    int td = d[i];
                    int l = max(0, j - td), r = j;
                    if (l <= r)
                    {
                        auto f1 = (i64)cntb * cntc * cnte % mod;
                        (f1 *= calc(cnt0, l, r)) %= mod;
                        (f[j] += f1) %= mod;

                        auto g1 = (i64)cntb * cntc * cnte % mod;
                        (g1 *= calc(sum0, l, r)) %= mod;
                        auto g2 = (i64)sumb * cntc * cnte % mod;
                        (g2 *= calc(cnt0, l, r) * j - calc(cnt1, l, r)) %= mod;
                        (g[j] += g1 + g2) %= mod;
                    }
                }
                else
                {
                    int td = -d[i];
                    int l = max(0, j - td), r = j;
                    if (l <= r)
                    {
                        auto f1 = (i64)cntb * cntc * cnte % mod;
                        (f1 *= (calc(cnt0, l, r) * (td - j + 1) + calc(cnt1, l, r)) % mod) %= mod;
                        (f[j] += f1) %= mod;

                        auto g1 = (i64)cntb * cntc * cnte % mod;
                        (g1 *= (calc(sum0, l, r) * (td - j + 1) + calc(sum1, l, r)) % mod) %= mod;
                        auto g2 = (i64)sumb * cntc * cnte % mod;
                        auto g3 = (i64)(td - j + 1) * j % mod * calc(cnt0, l, r) % mod;
                        (g3 += (i64)(j * 2 - td - 1) * calc(cnt1, l, r)) %= mod;
                        (g3 -= calc(cnt2, l, r)) %= mod;
                        (g[j] += g1 + g2 * g3) %= mod;
                    }
                }

                if (e[i - 1] >= 0)
                {
                    int te = e[i - 1];
                    int l = j + 1, r = min(V, j + te);
                    if (l <= r)
                    {
                        auto f1 = (i64)cntb * cntc * cntd % mod;
                        (f1 *= calc(cnt0, l, r)) %= mod;
                        (f[j] += f1) %= mod;

                        auto g1 = (i64)cntb * cntc * cntd % mod;
                        (g1 *= calc(sum0, l, r)) %= mod;
                        auto g2 = (i64)cntb * sumc * cntd % mod;
                        (g2 *= -calc(cnt0, l, r) * j + calc(cnt1, l, r)) %= mod;
                        (g[j] += g1 + g2) %= mod;
                    }
                }
                else
                {
                    int te = -e[i - 1];
                    int l = j + 1, r = min(V, j + te);
                    if (l <= r)
                    {
                        auto f1 = (i64)cntb * cntc * cntd % mod;
                        (f1 *= (calc(cnt0, l, r) * (te + j + 1) - calc(cnt1, l, r)) % mod) %= mod;
                        (f[j] += f1) %= mod;

                        auto g1 = (i64)cntb * cntc * cntd % mod;
                        (g1 *= (calc(sum0, l, r) * (te + j + 1) - calc(sum1, l, r)) % mod) %= mod;
                        auto g2 = (i64)cntb * sumc * cntd % mod;
                        auto g3 = -(j + te + 1) * j % mod * calc(cnt0, l, r) % mod;
                        (g3 += (j * 2 + te + 1) * calc(cnt1, l, r)) %= mod;
                        (g3 -= calc(cnt2, l, r)) %= mod;

                        (g[j] += g1 + g2 * g3) %= mod;
                    }
                }
            }
            for (int j = 0; j <= V; ++j)
            {
                if (j > 0)
                {
                    cnt0[j] = cnt0[j - 1];
                    cnt1[j] = cnt1[j - 1];
                    cnt2[j] = cnt2[j - 1];
                    sum0[j] = sum0[j - 1];
                    sum1[j] = sum1[j - 1];
                }
                else
                {
                    cnt0[j] = 0;
                    cnt1[j] = 0;
                    cnt2[j] = 0;
                    sum0[j] = 0;
                    sum1[j] = 0;
                }

                (cnt0[j] += f[j]) %= mod;
                (cnt1[j] += f[j] * j) %= mod;
                (cnt2[j] += f[j] * j * j) %= mod;

                (sum0[j] += g[j]) %= mod;
                (sum1[j] += g[j] * j) %= mod;

                f[j] = g[j] = 0;
            }
        }
        cout << (calc(sum0, 0, 0) + mod) % mod << ' '
             << ((tot - calc(cnt0, 0, 0)) % mod + mod) % mod << '\n';
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
