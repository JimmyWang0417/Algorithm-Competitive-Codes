#include <bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
constexpr int N = 2e5 + 5;
constexpr double base = 1.0 / 3.0;
inline void _main()
{
    while (1)
    {
        string s;
        cin >> s;
        if (s == "WIN" || s == "LOSE")
            return;
        int m, b;
        cin >> m >> b;
        if (b <= m * base)
            cout << "PLAY" << endl;
        else
            cout << "SKIP" << endl;
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    cin >> T;
    T = 1;
    while (T--)
        _main();
    return 0;
}