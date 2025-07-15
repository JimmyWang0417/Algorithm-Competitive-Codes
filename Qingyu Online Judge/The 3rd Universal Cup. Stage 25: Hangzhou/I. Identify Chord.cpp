#include <bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
map<int, map<int, int>> mp;
inline int query(int x, int y)
{
    if (x == y)
        return 0;
    if (x > y)
        swap(x, y);
    if (!mp[x][y])
    {
        cout << "? " << (x + 1) << ' ' << (y + 1) << endl;
        int d;
        cin >> d;
        mp[x][y] = d;
    }
    return mp[x][y];
}
inline void _main()
{
    int n;
    cin >> n;
    auto pre = [&](int u)
    {
        return (u - 1 + n) % n;
    };
    auto nxt = [&](int u)
    {
        return (u + 1) % n;
    };
    int u = 0, v = (n + 1) / 2;
    if (n % 2 == 0)
    {
        while (query(u, v) >= n / 2)
        {
            u = (u + 1) % n;
            v = (v + 1) % n;
        }
    }
    else
    {
        while (query(u, v) >= n / 2 && query(u, pre(v)) >= n / 2)
        {
            u = (u + 1) % n;
            v = (v + 1) % n;
        }
        if (query(u, v) >= n / 2)
            v = pre(v);
    }
    int dis = query(u, v) - 1;
    int ansu = 0, ansv = 0;
    if (query(u, v) <= query(pre(u), v) && query(u, v) <= query(nxt(u), v))
        ansu = u;
    else if (query(u, v) > query(pre(u), v))
    {
        int l = 1, r = (u - v + n) % n;
        while (l <= r)
        {
            int mid = (l + r) >> 1; 
            if (query(u, v) - mid == query((u - mid + n) % n, v))
                l = mid + 1;
            else
                r = mid - 1;
        }
        ansu = (u - r + n) % n;
        dis -= r;
    }
    else
    {
        int l = 1, r = (v - u + n) % n;
        while (l <= r)
        {
            int mid = (l + r) >> 1; 
            if (query(u, v) - mid == query((u + mid) % n, v))
                l = mid + 1;
            else
                r = mid - 1;
        }
        ansu = (u + r) % n;
        dis -= r;
    }
    if (query(ansu, (v + dis) % n) == 1)
        ansv = (v + dis) % n;
    else
        ansv = (v - dis + n) % n;
    cout << "! " << ansu + 1 << ' ' << ansv + 1 << endl;
    mp.clear();
    int nmsl;
    cin >> nmsl;
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