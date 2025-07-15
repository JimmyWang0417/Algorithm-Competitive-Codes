#include <bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
constexpr int N = 1e5 + 5;
constexpr int M = 3e6 + 5;
int n, m;
int p[M];
char str[M];
pair<ull, string> a[N];
inline void insert()
{
    cin >> (str + 1);
    p[1] = 0;
    int len = (int)strlen(str + 1);
    for (int i = 2, j = 0; i <= len; ++i)
    {
        while (j && str[i] != str[j + 1])
            j = p[j];
        if (str[i] == str[j + 1])
            ++j;
        p[i] = j;
    }
    if (len % (len - p[len]) == 0)
    {
        len = (len - p[len]);
        str[len + 1] = '\0';
    }
    ull hsh = 0;
    for (int i = 1; i <= len; ++i)
        hsh = hsh * 7 + (str[i] == 'P' ? 1 : (str[i] == 'K' ? 2 : 3));
    a[++m] = make_pair(hsh, (string)(str + 1));
}
int ch[M][3], tot = 1;
int where[M], cnt[M];
inline void insert(int id, int addcnt)
{
    auto calc = [](char c)
    {
        return (c == 'P' ? 0 : (c == 'K' ? 1 : 2));
    };
    auto &s = a[id].second;
    for (int i = 0, u = 1; ; ++i)
    {
        int c = calc(s[i % s.size()]);
        if (!ch[u][c])
        {
            u = ch[u][c] = ++tot;
            where[u] = id, cnt[u] = addcnt;
            break;
        }
        else
        {
            u = ch[u][c];
            if (where[u])
            {
                auto &t = a[where[u]].second;
                int d = calc(t[(i + 1) % t.size()]);
                int v = ch[u][d] = ++tot;
                where[v] = where[u], cnt[v] = cnt[u];
                where[u] = 0, cnt[u] = 0;
            }
        }
    }
}
ll answer;
inline int dfs(int u)
{
    if (!u)
        return 0;
    if (where[u])
        return cnt[u];
    int sze0 = dfs(ch[u][0]), sze1 = dfs(ch[u][1]), sze2 = dfs(ch[u][2]);
    answer += (ll)sze0 * sze1 * sze2;
    return sze0 + sze1 + sze2;
}
inline void _main()
{
    cin >> n;
    for (int i = 1; i <= n; ++i)
        insert();
    sort(a + 1, a + 1 + m);
    for (int i = 1, j = 1; i <= m; i = j)
    {
        while (j <= m && a[i] == a[j])
            ++j;
        insert(i, j - i);
    }
    dfs(1);
    cout << answer << '\n';
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