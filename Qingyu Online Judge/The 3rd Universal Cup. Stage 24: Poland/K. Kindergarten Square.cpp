#include <bits/stdc++.h>
#define int long long
using namespace std;
constexpr int N = 405;
int n;
char a[N][N];
bool vis[N][N];
priority_queue<tuple<int, int, int>> q;
constexpr int dx[] = {1, -1, 0, 0, 1, -1, 1, -1};
constexpr int dy[] = {0, 0, 1, -1, 1, -1, -1, 1};
inline void _main()
{
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    int w = c - a;
    if (w != d - b || w <= 0 || b - a != 1)
        cout << "-1\n";
    else if ((a - 1) / w != (b - 1) / w)
        cout << "-1\n";
    else
        cout << (d - 1) / w + 1 << ' ' << w << '\n';
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