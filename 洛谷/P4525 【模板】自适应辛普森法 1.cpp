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
template <typename T>
struct Simpson
{
    using functype = function<T(T)>;
    functype f;
    Simpson(const functype &other) : f(other) {}
    auto simpson(T l, T r)
    {
        T mid = (l + r) / 2;
        return (r - l) * (f(l) + 4 * f(mid) + f(r)) / 6;
    }
    auto solve(T l, T r, T eps, T ans) -> T
    {
        T mid = (l + r) / 2;
        double fl = simpson(l, mid), fr = simpson(mid, r);
        if (abs(fl + fr - ans) <= 15 * eps)
            return fl + fr + (fl + fr - ans) / 15;
        return solve(l, mid, eps / 2, fl) + solve(mid, r, eps / 2, fr);
    }
    auto integral(T l, T r, T eps)
    {
        return solve(l, r, eps, simpson(l, r));
    }
};
struct Main
{
    Main()
    {
        double a, b, c, d, L, R;
        cin >> a >> b >> c >> d >> L >> R;
        auto func = [&](double x)
        {
            return (c * x + d) / (a * x + b);
        };
        cout << fixed << setprecision(6) << Simpson<double>(func).integral(L, R, 1e-7) << '\n';
    }
};
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--)
        Main();
    return 0;
}