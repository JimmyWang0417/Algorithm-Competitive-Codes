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
template <typename T = int>
constexpr auto quickpow(i64 a, T b, int mod)
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
struct Main
{
    int n;
    typedef complex<f80> p2;
    auto dot(p2 x, p2 y)
    {
        return (conj(x) * y).real();
    }
    auto cross(p2 x, p2 y)
    {
        return (conj(x) * y).imag();
    }
    vector<p2> a;
    Main()
    {
        cin >> n;
        a.resize(n);
        for (int i = 0; i < n; ++i)
        {
            i64 s = 0, t = 0;
            int c;
            cin >> c;
            for (int j = 0; j < c; ++j)
            {
                int x;
                cin >> x;
                s += x, t += (i64)x * x;
            }
            a[i] = {(f80)s / c, (f80)t / c};
        }
        sort(a.begin(), a.end(), [](auto x, auto y)
             { return make_pair(x.real(), x.imag()) < make_pair(y.real(), y.imag()); });
        vector<int> st(n + 1);
        int top = 0;
        for (int i = 0; i < n; ++i)
        {
            while (top >= 2 && cross(a[st[top - 1]] - a[st[top]], a[i] - a[st[top]]) <= 0)
                --top;
            st[++top] = i;
        }
        f80 minn = 1e40, maxx = -1e40;
        for (int i = 0; i < n; ++i)
            minn = min(minn, a[i].imag() - a[i].real() * a[i].real());
        for (int i = 1; i <= top; ++i)
            maxx = max(maxx, a[st[i]].imag() - a[st[i]].real() * a[st[i]].real());
        for (int i = 2; i <= top; i++)
        {
            auto t1 = a[st[i - 1]], t2 = a[st[i]];
            auto k = (t2.imag() - t1.imag()) / (t2.real() - t1.real());
            auto x = k / 2;
            if (t1.real() <= x && x <= t2.real())
                maxx = max(maxx, t1.imag() + k * (x - t1.real()) - x * x);
        }
        cout << fixed << setprecision(14) << minn << ' ' << maxx << '\n';
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
