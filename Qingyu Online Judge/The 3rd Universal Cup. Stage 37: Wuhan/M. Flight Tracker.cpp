#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr int N = 5e5 + 5;
constexpr int mod = 998244353;
struct p3
{
    double x, y, z;
    p3(double _x = 0, double _y = 0, double _z = 0) : x(_x), y(_y), z(_z) {}
    p3 operator*(double v) const
    {
        return p3(x * v, y * v, z * v);
    }
    p3 operator/(double v) const
    {
        return p3(x / v, y / v, z / v);
    }
    p3 operator+(p3 rhs) const
    {
        return p3(x + rhs.x, y + rhs.y, z + rhs.z);
    }
} bg, ed, hom;
double sqabs(p3 x)
{
    return x.x * x.x + x.y * x.y + x.z * x.z;
}
double abs(p3 x)
{
    return sqrt(sqabs(x));
}
p3 cross(p3 a, p3 b)
{
    return p3(
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x);
}
double dot(p3 x, p3 y)
{
    return x.x * y.x + x.y * y.y + x.z * y.z;
}
int m;
inline void _main()
{
    cin >> m;
    {
        int x, y, z;
        cin >> x >> y >> z;
        double r = sqrt(x * x + y * y + z * z);
        hom = p3(x / r, y / r, z / r);
    }
    {
        int x, y, z;
        cin >> x >> y >> z;
        double r = sqrt(x * x + y * y + z * z);
        bg = p3(x / r, y / r, z / r);
    }
    {
        int x, y, z;
        cin >> x >> y >> z;
        double r = sqrt(x * x + y * y + z * z);
        ed = p3(x / r, y / r, z / r);
    }
    p3 n = cross(bg, ed);
    n = n / abs(n);
    p3 radius = hom + n * (-dot(hom, n));
    auto distance = [&](auto lhs, auto rhs)
    {
        return acos(clamp(dot(lhs, rhs), -1.0, 1.0));
    };
    if (dot(cross(bg, radius), n) > 0 && dot(cross(radius, ed), n) > 0)
        cout << fixed << setprecision(9) << asin(clamp(abs(dot(n, hom)), -1.0, 1.0)) * m << '\n';
    else
        cout << fixed << setprecision(9) << min(distance(bg, hom), distance(hom, ed)) * m << '\n';
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    cin >> T;
    while (T--)
        _main();
    return 0;
}