#include <bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
constexpr int N = 2e5 + 5;
inline void _main()
{
    int l, r;
    cin >> l >> r;
    if (l % 2 && r % 2)
    {
        cout << "Alice\n";
        return;
    }
    if (r % 2 && l % 2 == 0)
    {
        cout << "Bob\n";
        return;
    }
    if (l % 2)
    {
        if (r >= 2 * l)
            cout << "Alice\n";
        else
            cout << "Bob\n";
    }
    else
    {
        if (r >= 2 * (l + 1))
            cout << "Bob\n";
        else
            cout << "Alice\n";
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