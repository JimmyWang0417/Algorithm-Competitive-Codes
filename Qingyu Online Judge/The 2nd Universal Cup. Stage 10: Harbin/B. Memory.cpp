#include <bits/stdc++.h>
using namespace std;

#define int long long

constexpr int N = 1e5 + 5;

int n, a[N];

int c, d[64];
inline void insert(int x)
{
    if (d[63] < 0)
        c = -1;
    else if (d[63] > 0)
        c = 1;
    for (int i = 63; i >= 1; --i)
        d[i] = d[i - 1];
    d[0] = x + d[1] / 2;
    d[1] %= 2;
}
inline void print()
{
    for (int i = 0; i < 63; ++i)
    {
        if (d[i] == 0)
            continue;
        if (d[i] > 0)
        {
            cout << '+';
            return;
        }
        else
        {
            cout << '-';
            return;
        }
    }
    if (c > 0)
        cout << '+';
    else if (c == 0)
        cout << '0';
    else
        cout << '-';
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    for (int i = 1; i <= n; ++i)
    {
        insert(a[i]);
        print();
    }
    cout << endl;
    return 0;
}
