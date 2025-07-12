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
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> (a[i] + 1);
    auto calc = [](int i, int j)
    {
        int cnt = 0;
        if (a[i][j] == 'o')
        {
            ++cnt;
            for (int d = 0; d < 8; ++d)
            {
                int x = i + dx[d], y = j + dy[d];
                if (x < 1 || x > n || y < 1 || y > n)
                    continue;
                cnt += (a[x][y] == 'O');
            }
        }
        else if (a[i][j] == 'm')
        {
            ++cnt;
            for (int d = 0; d < 8; ++d)
            {
                int x = i + dx[d], y = j + dy[d];
                if (x < 1 || x > n || y < 1 || y > n)
                    continue;
                cnt += (a[x][y] == 'P');
            }
        }
        else if (a[i][j] == 'p')
        {
            ++cnt;
            for (int d = 0; d < 8; ++d)
            {
                int x = i + dx[d], y = j + dy[d];
                if (x < 1 || x > n || y < 1 || y > n)
                    continue;
                cnt += (a[x][y] == 'M');
            }
        }
        return cnt;
    };
    int cnt = 0, all = 0;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            if (calc(i, j))
                q.emplace(calc(i, j), i, j);
            else if (a[i][j] == 'O')
            {
                ++all;
                for (int d = 0; d < 8; d += 2)
                {
                    int x = i + dx[d], y = j + dy[d];
                    if (x < 1 || x > n || y < 1 || y > n)
                        continue;
                    all += (a[x][y] == 'O');
                }
            }
            else if (a[i][j] == 'M')
            {
                ++all;
                for (int d = 0; d < 8; d += 2)
                {
                    int x = i + dx[d], y = j + dy[d];
                    if (x < 1 || x > n || y < 1 || y > n)
                        continue;
                    all += (a[x][y] == 'P');
                }
            }
            else if (a[i][j] == 'P')
            {
                ++all;
                for (int d = 0; d < 8; d += 2)
                {
                    int x = i + dx[d], y = j + dy[d];
                    if (x < 1 || x > n || y < 1 || y > n)
                        continue;
                    all += (a[x][y] == 'M');
                }
            }
    cout << all << ' ';
    while (!q.empty())
    {
        auto [w, i, j] = q.top();
        q.pop();
        if (vis[i][j])
            continue;
        if (w <= 1)
            break;
        // cout << w << ' ' << i << ' ' << j << '\n';
        all += w;
        vis[i][j] = true;
        a[i][j] = (char)(a[i][j] - 'a' + 'A');
        for (int d = 0; d < 8; ++d)
        {
            int x = i + dx[d], y = j + dy[d];
            if (x < 1 || x > n || y < 1 || y > n)
                continue;
            if (calc(x, y))
                q.emplace(calc(x, y), x, y);
        }
    }
    cout << all << '\n';
    for (int i = 1; i <= n; ++i)
        cout << a[i] + 1 << '\n';
    cout << '\n';
    return 0;
}