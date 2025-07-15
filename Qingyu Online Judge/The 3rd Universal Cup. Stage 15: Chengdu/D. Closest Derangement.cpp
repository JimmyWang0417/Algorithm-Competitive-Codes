#include <bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
constexpr int N = 4e5 + 5;
typedef pair<int, bool> node;
int n, m, tot;
int a[N], b[N];
int dp[23][N], Log[N];
node p[N];
int d[2][3] = {{+2, -1, -1}, {+1, +1, -2}};
inline void _main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    if (n % 2 == 0)
    {
        if (m == 1)
        {
            for (int i = 1; i <= n; ++i)
                cout << (a[i] & 1 ? (a[i] + 1) : (a[i] - 1)) << ' ';
            cout << '\n';
        }
        else
            cout << "-1\n";
    }
    else
    {
        for (int i = 1; i <= n; ++i)
            b[a[i]] = i;

        Log[0] = -1;
        for (int i = 1; i <= n; ++i)
        {
            dp[0][i] = b[i];
            Log[i] = Log[i >> 1] + 1;
        }
        for (int j = 0; j < Log[n]; ++j)
            for (int i = 1; i + (2 << j) - 1 <= n; ++i)
                dp[j + 1][i] = min(dp[j][i], dp[j][i + (1 << j)]);
        auto minpos = [](int x, int y)
        {
            int k = Log[y - x + 1];
            return min(dp[k][x], dp[k][y - (1 << k) + 1]);  
        };

        tot = 0;
        for (int i = 1; i + 2 <= n; i += 2)
        {
            p[++tot] = make_pair(i, 0);
            p[++tot] = make_pair(i, 1);
        }
        if (m > tot)
        {
            cout << "-1\n";
            return;
        }
        auto calc = [](node x, int pos)
        {
            if (a[pos] < x.first)
                return (a[pos] & 1 ? a[pos] + 1 : a[pos] - 1);
            else if (a[pos] > x.first + 2)
                return (a[pos] & 1 ? (a[pos] - 1) : a[pos] + 1);
            else
                return a[pos] + d[x.second][a[pos] - x.first];
        };
        auto compare = [&](node x, node y) 
        {
            vector<int> q(6);
            q[0] = b[x.first], q[1] = b[x.first + 1], q[2] = b[x.first + 2];
            q[3] = b[y.first], q[4] = b[y.first + 1], q[5] = b[y.first + 2];
            if (x.first + 3 < y.first)
                q.push_back(minpos(x.first + 3, y.first - 1));
            if (y.first + 3 < x.first)
                q.push_back(minpos(y.first + 3, x.first - 1));
            sort(q.begin(), q.end());
            q.erase(unique(q.begin(), q.end()), q.end());

            for (auto pos : q)
            {
                int i = calc(x, pos), j = calc(y, pos);
                if (i == j)
                    continue;
                if (i < j)
                    return true;
                else
                    return false;
            }
            return false;
        };

        nth_element(p + 1, p + m, p + 1 + tot, compare);
        
        for (int i = 1; i <= n; ++i)
            cout << calc(p[m], i) << ' ';
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