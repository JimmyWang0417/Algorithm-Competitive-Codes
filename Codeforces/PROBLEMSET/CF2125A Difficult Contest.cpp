#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr int N = 1e6 + 5;
constexpr int mod = 998244353;
inline void _main()
{
    string s;
    cin >> s;
    sort(s.begin(), s.end(), [](char x, char y)
         { int a = (x == 'F' ? 27 : (x == 'N' ? 28 : (x - 'A')));
        int b =(y == 'F' ? 27 : (y == 'N' ? 28 : (y - 'A')));
        return a < b; });
    cout << s << '\n';
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