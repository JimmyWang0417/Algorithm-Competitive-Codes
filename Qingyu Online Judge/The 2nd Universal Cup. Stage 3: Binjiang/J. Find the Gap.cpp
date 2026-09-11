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
struct p3
{
    f80 x, y, z;
    p3() = default;
    p3(f80 _x, f80 _y, f80 _z) : x(_x), y(_y), z(_z) {}
    auto operator<(const p3 &rhs) const
    {
        return tie(x, y, z) < tie(rhs.x, rhs.y, rhs.z);
    }
    auto operator+(p3 p) const
    {
        return p3(x + p.x, y + p.y, z + p.z);
    }
    auto operator-(p3 p) const
    {
        return p3(x - p.x, y - p.y, z - p.z);
    }
    auto operator*(double p) const
    {
        return p3(x * p, y * p, z * p);
    }
    auto operator/(double p) const
    {
        return p3(x / p, y / p, z / p);
    }

    auto friend dot(p3 a, p3 b)
    {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }
    auto friend cross(p3 a, p3 b)
    {
        return p3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
    }
    auto friend mixed(p3 a, p3 b, p3 c)
    {
        return dot(cross(a, b), c);
    }
    auto friend norm(p3 a)
    {
        return dot(a, a);
    }
    auto friend abs(p3 a)
    {
        return sqrt(norm(a));
    }
};
struct plane
{
    p3 n;
    f80 d;
    plane() = default;
    plane(p3 _n, f80 _d) : n(_n), d(_d) {}
    plane(p3 _n, p3 _p) : n(_n), d(dot(_n, _p)) {}
    plane(p3 p, p3 q, p3 r) : plane(cross(q - p, r - p), p) {}

    auto side(p3 p) const
    {
        return dot(n, p) - d;
    }
    auto dist(p3 p) const
    {
        return side(p) / abs(n);
    }
};
constexpr double eps = 1e-12;
struct Main
{
    int n;
    vector<p3> a;
    Main()
    {
        cin >> n;
        a.resize(n);
        for (auto &[x, y, z] : a)
            cin >> x >> y >> z;
        f80 ans = 1e18;
        for (int i = 0; i < n; ++i)
            for (int j = i + 1; j < n; ++j)
                for (int k = j + 1; k < n; ++k)
                {
                    if (abs(norm(cross(a[i] - a[j], a[k] - a[j]))) < eps)
                        continue;
                    plane p(a[i], a[j], a[k]);
                    f80 minn = 1e18, maxx = -1e18;
                    for (int l = 0; l < n; ++l)
                    {
                        minn = min(minn, p.side(a[l]));
                        maxx = max(maxx, p.side(a[l]));
                    }
                    ans = min(ans, abs(maxx - minn) / abs(p.n));
                    // cout << ' ' << p.n.x << ' ' << p.n.y << ' ' << p.n.z << ' ' << p.d << '\n';
                    // cout << i << ' ' << j << ' ' << k << ' ' << minn << ' ' << maxx << '\n';
                }

        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
            {
                if (i == j)
                    continue;
                for (int k = 0; k < n; ++k)
                {
                    if (i == k || j == k)
                        continue;
                    for (int l = 0; l < n; ++l)
                    {
                        if (i == l || j == l || k == l)
                            continue;
                        p3 X = a[l] - a[k], Y = a[j] - a[i];
                        if (abs(norm(cross(X, Y))) < eps)
                            continue;
                        plane p(cross(X, Y), a[i]);
                        f80 minn = 1e18, maxx = -1e18;
                        for (int r = 0; r < n; ++r)
                        {
                            minn = min(minn, p.side(a[r]));
                            maxx = max(maxx, p.side(a[r]));
                        }
                        ans = min(ans, abs(maxx - minn) / abs(p.n));
                    }
                }
            }
        cout << fixed << setprecision(16) << (abs(ans - 1e18) < eps ? 0 : ans) << '\n';
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
