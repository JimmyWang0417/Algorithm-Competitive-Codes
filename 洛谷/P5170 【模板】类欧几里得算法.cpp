#include <bits/stdc++.h>
#include <bits/extc++.h>
#define ll long long
#define ull unsigned ll
#define lowbit(x) (x & (-x))
template <typename T>
inline void read(T &x)
{
    x = 0;
    char s = (char)getchar();
    bool f = false;
    while (!(s >= '0' && s <= '9'))
    {
        if (s == '-')
            f = true;
        s = (char)getchar();
    }
    while (s >= '0' && s <= '9')
    {
        x = (x << 1) + (x << 3) + s - '0';
        s = (char)getchar();
    }
    if (f)
        x = (~x) + 1;
}
template <typename T, typename... T1>
inline void read(T &x, T1 &...x1)
{
    read(x);
    read(x1...);
}
template <typename T>
inline void ckmin(T &x, T y)
{
    if (x > y)
        x = y;
}
template <typename T>
inline void ckmax(T &x, T y)
{
    if (x < y)
        x = y;
}
using namespace std;
constexpr int mod = 998244353;
constexpr int inv2 = (mod + 1) / 2, inv6 = (mod + 1) / 6;
struct node
{
    ll f, g, h;
};
inline node calc(ll a, ll b, ll c, ll n)
{
    const ll ac = a / c, bc = b / c, n1 = n + 1, n21 = n * 2 + 1, m = (a * n + b) / c;
    node res;
    if (a == 0)
    {
        res.f = bc * n1 % mod;
        res.g = bc * n % mod * n1 % mod * inv2 % mod;
        res.h = bc * bc % mod * n1 % mod;
        return res;
    }
    else if (a >= c || b >= c)
    {
        node now = calc(a % c, b % c, c, n);
        res.f = (n * n1 % mod * inv2 % mod * ac % mod + n1 * bc % mod + now.f) % mod;
        res.g = (ac * n % mod * n1 % mod * n21 % mod * inv6 % mod + bc * n % mod * n1 % mod * inv2 % mod + now.g) % mod;
        res.h = (2 * bc % mod * now.f % mod + 2 * ac % mod * now.g % mod + ac * ac % mod * n % mod * n1 % mod * n21 % mod * inv6 % mod + bc * bc % mod * n1 % mod + ac * bc % mod * n % mod * n1 % mod + now.h) % mod;
        return res;
    }
    else
    {
        node now = calc(c, c - b - 1, a, m - 1);
        res.f = (n * m % mod - now.f) % mod;
        res.g = inv2 * (m * n % mod * n1 % mod - now.h - now.f) % mod;
        res.h = (n * m % mod * (m + 1) % mod - 2 * now.g - 2 * now.f - res.f) % mod;
        return res;
    }
}
signed main()
{
    int T;
    read(T);
    while (T--)
    {
        int n, a, b, c;
        read(n, a, b, c);
        node res = calc(a, b, c, n);
        printf("%lld %lld %lld\n", (res.f + mod) % mod, (res.h + mod) % mod, (res.g + mod) % mod);
    }
    return 0;
}