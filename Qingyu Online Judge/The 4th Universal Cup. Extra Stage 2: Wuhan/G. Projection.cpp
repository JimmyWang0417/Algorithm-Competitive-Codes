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
template <typename T>
auto &operator<<(ostream &in, const vector<T> &rhs)
{
    for (auto i : rhs)
        in << i << ' ';
    return in;
}
struct Main
{
    int n, r2;
    vector<f80> X, L;
    Main()
    {
        cin >> n >> r2;
        X.resize(n), L.resize(n);
        for (auto &i : X)
            cin >> i;
        for (auto &i : L)
            cin >> i;
        auto point = [&](auto lambda)
        {
            auto times = 1 / (1 + lambda);
            vector<f80> res(n);
            for (int i = 0; i < n; ++i)
                res[i] = clamp(X[i] * times, -L[i], L[i]);
            return res;
        };
        auto phi = [&](auto lambda)
        {
            auto times = 1 / (1 + lambda);
            f80 res = 0;
            for (int i = 0; i < n; ++i)
            {
                auto Y = clamp(X[i] * times, -L[i], L[i]);
                res += Y * Y;
            }
            return res;
        };
        if (phi(0) <= r2)
        {
            cout << point(0) << '\n';
            return;
        }
        f80 l = 0, r = 1;
        while (phi(r) > r2)
            r *= 2;
        for (int _ = 0; _ < 80; ++_)
        {
            auto mid = (l + r) / 2;
            if (phi(mid) > r2)
                l = mid;
            else
                r = mid;
        }
        cout << point(l) << '\n';
    }
};
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cout << fixed << setprecision(9);
    int T = 1;
    cin >> T;
    while (T--)
        Main();
    return 0;
}
