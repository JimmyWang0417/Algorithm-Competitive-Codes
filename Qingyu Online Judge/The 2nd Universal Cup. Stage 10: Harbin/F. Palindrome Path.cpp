#include <bits/stdc++.h>

using namespace std;
int n, m;
char s[35][35];
int sx, sy, ex, ey;
const int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
const int C[4] = {'D', 'R', 'U', 'L'};
vector<int> sav[35][35];
bool pd[35][35];
vector<int> ned;
bool dfs(int x, int y)
{
    pd[x][y] = true;
    bool chk = false;
    for (int i = 0; i < 4; i++)
    {
        int nx = x + dx[i], ny = y + dy[i];
        if (nx < 1 || ny < 1 || nx > n || ny > m || s[nx][ny] != '1' || pd[nx][ny])
            continue;
        if (dfs(nx, ny))
            ned.push_back(i), chk = true;
        sav[x][y].push_back(i);
    }
    if (x == ex && y == ey)
        return true;
    return chk;
}
bool check(int x, int y)
{
    return (x >= 1 && y >= 1 && x <= n && y <= m && s[x][y] == '1');
}
vector<int> ans;
void calc(int x, int y, int op)
{
    int hav = 0;
    int X = ex, Y = ey;
    while (check(x + dx[op ^ 2], y + dy[op ^ 2]) && check(X + dx[op], Y + dy[op]))
    {
        ans.push_back(op ^ 2);
        x += dx[op ^ 2];
        y += dy[op ^ 2];
        X += dx[op];
        Y += dy[op];
        hav++;
    }
    if (check(X + dx[op], Y + dy[op]))
        ans.push_back(op ^ 2);
    for (int i = 1; i <= hav + 1; i++)
        ans.push_back(op);
}
void Solve(int x, int y)
{
    for (auto i : sav[x][y])
    {
        int nx = x + dx[i], ny = y + dy[i];
        calc(x, y, i);
        Solve(nx, ny);
        calc(nx, ny, i ^ 2);
    }
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%s", s[i] + 1);
    scanf("%d%d%d%d", &sx, &sy, &ex, &ey);
    dfs(sx, sy);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (s[i][j] == '1' && !pd[i][j])
            {
                puts("-1");
                return 0;
            }
    Solve(sx, sy);
    int x = sx, y = sy;
    reverse(ned.begin(), ned.end());
    for (auto i : ned)
    {
        calc(x, y, i);
        x += dx[i], y += dy[i];
    }
    for (auto x : ans)
        putchar(C[x]);
    reverse(ans.begin(), ans.end());
    for (auto x : ans)
        putchar(C[x]);
    return 0;
}