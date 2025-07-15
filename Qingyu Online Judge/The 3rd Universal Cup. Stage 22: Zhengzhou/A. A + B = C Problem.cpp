#include <bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
typedef pair<long double, ll> node;
inline ll lcm(int x, int y)
{
    return (ll)x / __gcd(x, y) * y;
}
inline void _main()
{
    int A, B, C;
    cin >> A >> B >> C;
    if (lcm(A, B) % C != 0 || lcm(A, C) % B != 0 || lcm(B, C) % A != 0)
    {
        cout << "NO\n";
        return;
    }
    int g = __gcd(A, __gcd(B, C));
    int p = __gcd(A, B) / g, q = __gcd(A, C) / g, r = __gcd(B, C) / g;
    if (p == q && q == r)
    {
        if (g == 1)
            cout << "YES\n0\n0\n0\n";
        else if (g == 2)
            cout << "NO\n";
        else
        {
            cout << "YES\n";
            for (int i = 0; i < g - 2; ++i)
                cout << '0';
            cout << "10\n";
            for (int i = 0; i < g - 2; ++i)
                cout << '0';
            cout << "01\n";
            for (int i = 0; i < g - 2; ++i)
                cout << '0';
            cout << "11\n";
        }
    }
    else if (p == q)
    {
        cout << "YES\n";
        for (int i = 1; i < g; ++i)
            cout << '0';
        cout << "1\n";
        for (int i = 1; i < g * r; ++i)
            cout << '0';
        cout << "1\n";
        for (int i = 1; i <= g * r; ++i)
            cout << ((i % g == 0) ^ (i == g * r));
        cout << '\n';
    }
    else if (p == r)
    {
        cout << "YES\n";
        for (int i = 1; i < g * q; ++i)
            cout << '0';
        cout << "1\n";
        for (int i = 1; i < g; ++i)
            cout << '0';
        cout << "1\n";
        for (int i = 1; i <= g * q; ++i)
            cout << ((i % g == 0) ^ (i == g * q));
        cout << '\n';
    }
    else if (q == r)
    {
        cout << "YES\n";
        for (int i = 1; i < g * p; ++i)
            cout << '0';
        cout << "1\n";
        for (int i = 1; i <= g * p; ++i)
            cout << ((i % g == 0) ^ (i == g * p));
        cout << '\n';
        for (int i = 1; i < g; ++i)
            cout << '0';
        cout << "1\n";
    }
    else
    {
        cout << "YES\n";
        for (int i = 0; i < A; ++i)
            cout << ((i / g % p == p - 1) ^ (i / g % q == q - 1));
        cout << '\n';
        for (int i = 0; i < B; ++i)
            cout << ((i / g % p == p - 1) ^ (i / g % r == r - 1));
        cout << '\n';
        for (int i = 0; i < C; ++i)
            cout << ((i / g % q == q - 1) ^ (i / g % r == r - 1));
        cout << '\n';
    }
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