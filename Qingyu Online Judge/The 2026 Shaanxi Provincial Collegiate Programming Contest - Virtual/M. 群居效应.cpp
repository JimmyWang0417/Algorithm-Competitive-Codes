#include <bits/stdc++.h>
using namespace std;

#define LOCAL
#ifdef LOCAL
#define dbg(...) fprintf(stderr, ##__VA_ARGS__)
#else
#define dbg(...) 42
#endif

#define all(x) (x).begin(), (x).end()
using LL = long long;
using ai2 = array<int, 2>;

constexpr int dir[4][2] = {
    {1, 0},
    {-1, 0},
    {0, 1},
    {0, -1}};

struct Main
{
    LL ans = 0;
    int n, m, A, B;
    vector<string> g;
    vector<vector<char>> opt;
    void main()
    {
        read();
        work();
        cout << ans << "\n";
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                if (g[i][j] == '#')
                    cout << "#";
                else
                    cout << opt[i][j];
            }
            cout << "\n";
        }
    }
    void read()
    {
        cin >> n >> m >> A >> B;
        g.assign(n, {});
        for (auto &s : g)
            cin >> s;
    }
    void work()
    {
        opt.assign(n, vector<char>(m, 0));
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
            {
                if (g[i][j] == '#')
                    continue;
                opt[i][j] = 'A';
                int cnt = 0;
                for (int d = 0; d < 4; ++d)
                {
                    const int ni = i + dir[d][0];
                    const int nj = j + dir[d][1];
                    if (ni >= 0 && nj >= 0 && ni < n && nj < m && g[ni][nj] == '.')
                        ++cnt;
                }
                ans += A + cnt;
                const LL add = B - A - cnt * 2;
                if (add > 0)
                {
                    opt[i][j] = 'B';
                    ans += add;
                }
            }
    }
};
signed main()
{
#ifndef LOCAL
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
#endif
    Main{}.main();
    return 0;
}
