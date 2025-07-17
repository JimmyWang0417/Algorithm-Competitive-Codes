#include <bits/stdc++.h>
#define int long long
using namespace std;
inline int read()
{
    int x = 0, f = 1;
    char c = getchar();
    while (c < 48)
    {
        if (c == '-')
            f = 0;
        c = getchar();
    }
    while (c >= 48)
        x = (x << 3) + (x << 1) + (c ^ 48), c = getchar();
    return f ? x : -x;
}
int n;
void solve()
{
    n = read();
    cout << (n == 1 ? "YES" : "NO") << endl;
}
signed main()
{
    int T = read();
    while (T--)
        solve();
}