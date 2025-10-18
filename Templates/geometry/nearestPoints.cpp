#include <bits/stdc++.h>
#define lowbit(x) ((x) & (-(x)))
#define re register
#define ll long long
#define ull unsigned long long
#define rep(i, a, b) for (re int i = a; i <= b; ++i)
#define per(i, a, b) for (re int i = a; i >= b; --i)
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
inline void clear(T *array, int l, int r, int val)
{
    memset(&array[l], val, sizeof(T) * (r - l + 1));
}
using namespace std;
const int N = 4e5 + 5;
struct Point
{
    int x, y;
    inline bool operator<(const Point &rhs) const
    {
        return x < rhs.x;
    }
    inline bool operator>(const Point &rhs) const
    {
        return y < rhs.y;
    }
} a[N], b[N];
int n;
inline ll calc(const Point &x, const Point &y)
{
    return (ll)(x.x - y.x) * (x.x - y.x) + (ll)(x.y - y.y) * (x.y - y.y);
}
inline ll solve(int l, int r)
{
    if (l >= r)
        return 1e18;
    int tot = 0;
    int mid = (l + r) >> 1;
    ll mindis = min(solve(l, mid - 1), solve(mid + 1, r));
    int res = (int)ceil(sqrt((double)mindis));
    for (int i = l; i < mid; ++i)
        if (a[mid].x - res < a[i].x)
            b[++tot] = a[i];
    b[++tot] = a[mid];
    for (int i = mid + 1; i <= r; ++i)
        if (a[mid].x + res > a[i].x)
            b[++tot] = a[i];
    sort(b + 1, b + 1 + tot, greater<Point>());
    for (int i = 1; i < tot; ++i)
        for (int j = i + 1; j <= tot && b[i].y + res > b[j].y; ++j)
        {
            mindis = min(mindis, calc(b[i], b[j]));
            res = (int)ceil(sqrt((double)mindis));
        }
    return mindis;
}
signed main()
{
    read(n);
    for (int i = 1; i <= n; ++i)
        read(a[i].x, a[i].y);
    sort(a + 1, a + 1 + n);
    ll ans = solve(1, n);
    printf("%lld\n", ans);
    return 0;
}