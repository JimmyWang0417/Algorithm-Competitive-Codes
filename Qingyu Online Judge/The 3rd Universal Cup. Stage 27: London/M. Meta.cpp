#include <bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
constexpr int N = 2e5 + 5;
int n, p[N];
inline void _main()
{
    cin >> n;
    for (int i = 1; i <= n; ++i)
    {
        string s;
        int a, b, c;
        cin >> s >> a >> b >> c;
        if (a == -1)
            a = 1e9;
        if (b == -1)
            b = 1e9;
        if (c == -1)
            c = 1e9;
        p[i] = min(a, min(b, c));
    }
    int leaf = 300, cnt = 0;;
    sort(p + 1, p + 1 + n);
    for (int i = 1; i <= n && p[i] <= leaf; ++i)
    {
        ++cnt;
        leaf -= p[i];
    }
    cout << cnt << '\n';
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--)
        _main();
    return 0;
}