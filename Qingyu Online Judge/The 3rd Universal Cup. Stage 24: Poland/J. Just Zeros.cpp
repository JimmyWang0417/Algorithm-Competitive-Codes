#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
constexpr int N = 1e5 + 5;
int n, m, q;
int popcount[1 << 8];
struct node
{
    int ans;
    int a[N];
    int b[N];
    inline void init()
    {
        for (int i = 0; i < m; ++i)
            b[i] = min(popcount[a[i]], popcount[((1 << n) - 1) ^ a[i]] + 1);
        for (int i = 0; i < m; ++i)
            ans += b[i];
    }
    inline void P(int x, int y)
    {
        --x, --y;
        ans -= b[y];
        a[y] ^= (1 << x);
        b[y] = min(popcount[a[y]], popcount[((1 << n) - 1) ^ a[y]] + 1);
        ans += b[y];
    }
    inline void K(int y)
    {
        --y;
        ans -= b[y];
        a[y] ^= ((1 << n) - 1);
        b[y] = min(popcount[a[y]], popcount[((1 << n) - 1) ^ a[y]] + 1);
        ans += b[y];
    }
} a[(1 << 8) + 5];
char str[8][N];
inline void _main()
{
    cin >> n >> m >> q;
    for (int i = 0; i < n; ++i)
        cin >> str[i];
    for (int i = 1; i < (1 << n); ++i)
        popcount[i] = popcount[i >> 1] + (i & 1);
    int nowS = 0;
    for (int j = 0; j < m; ++j)
    {
        int all = 0;
        for (int i = 0; i < n; ++i)
            all |= (str[i][j] == '1') << i;
        for (int S = 0; S < (1 << n); ++S)
            a[S].a[j] = all ^ S;
    }
    for (int S = 0; S < (1 << n); ++S)
        a[S].init();
    auto calc = [&]()
    {
        int ans = INT_MAX;
        for (int S = 0; S < (1 << n); ++S)
            ans = min(ans, a[S].ans + popcount[S ^ nowS]);
        return ans;
    };
    cout << calc() << '\n';
    while (q--)
    {
        char c;
        int x, y;
        cin >> c >> x;
        if (c == 'P')
        {
            cin >> y;
            for (int i = 0; i < (1 << n); ++i)
                a[i].P(x, y);
        }
        else if (c == 'R')
            nowS ^= 1 << (x - 1);
        else
            for (int i = 0; i < (1 << n); ++i)
                a[i].K(x);
        // cout << nowS << ' ' << a[2].ans << '\n';
        cout << calc() << '\n';
    }
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