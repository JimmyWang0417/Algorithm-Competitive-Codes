#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
constexpr int mod = 998244353;
template <typename T = int>
constexpr auto quickpow(i64 a, T b = mod - 2)
{
    i64 res = 1;
    while (b)
    {
        if (b & 1)
            (res *= a) %= mod;
        (a *= a) %= mod;
        b >>= 1;
    }
    return res;
}
struct Main
{
    constexpr static int dx[] = {0, 0, 1, -1};
    constexpr static int dy[] = {1, -1, 0, 0};
    int n, m;
    vector<string> s;
    vector<vector<int>> cnt;
    vector<vector<vector<pair<int, int>>>> G;
    auto calc(int i, int j)
    {
        return i * m + j;
    }
    vector<int> fa, tmpfa;
    auto find(int x) -> int
    {
        return fa[x] == x ? x : fa[x] = find(fa[x]);
    }
    auto unionn(int x, int y)
    {
        x = find(x), y = find(y);
        if (x == y)
            return;
        fa[x] = y;
    }
    stack<int> st;
    auto tmpfind(int x)
    {
        if (tmpfa[x] == x)
            return x;
        st.push(x);
        return tmpfa[x] = tmpfind(tmpfa[x]);
    }
    auto tmpunionn(int x, int y)
    {
        x = tmpfind(find(x)), y = tmpfind(find(y));
        if (x == y)
            return;
        st.push(x);
        tmpfa[x] = y;
    }
    auto check(int x, int y)
    {
        return tmpfind(find(x)) == tmpfind(find(y));
    }
    auto clear()
    {
        while (!st.empty())
        {
            tmpfa[st.top()] = st.top();
            st.pop();
        }
    }
    Main()
    {
        cin >> n >> m;
        s.resize(n);
        for (auto &i : s)
            cin >> i;
        cnt.resize(n, vector<int>(m));
        G.resize(n, vector<vector<pair<int, int>>>(m));
        int S = 0, T = 0;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
            {
                if (s[i][j] == 'U')
                {
                    cnt[i][j] = 2;
                    for (int k = i - 1; k >= 0; --k)
                    {
                        if (s[k][j] != '.')
                            break;
                        ++cnt[k][j];
                        G[i][j].emplace_back(k, j);
                    }
                }
                else if (s[i][j] == 'D')
                {
                    cnt[i][j] = 2;
                    for (int k = i + 1; k < n; ++k)
                    {
                        if (s[k][j] != '.')
                            break;
                        ++cnt[k][j];
                        G[i][j].emplace_back(k, j);
                    }
                }
                else if (s[i][j] == 'L')
                {
                    cnt[i][j] = 2;
                    for (int k = j - 1; k >= 0; --k)
                    {
                        if (s[i][k] != '.')
                            break;
                        ++cnt[i][k];
                        G[i][j].emplace_back(i, k);
                    }
                }
                else if (s[i][j] == 'R')
                {
                    cnt[i][j] = 2;
                    for (int k = j + 1; k < m; ++k)
                    {
                        if (s[i][k] != '.')
                            break;
                        ++cnt[i][k];
                        G[i][j].emplace_back(i, k);
                    }
                }
                else if (s[i][j] == '#')
                    cnt[i][j] = 2;
                else if (s[i][j] == 'S')
                    S = calc(i, j);
                else if (s[i][j] == 'E')
                    T = calc(i, j);
            }
        fa.resize(n * m), tmpfa.resize(n * m);
        iota(fa.begin(), fa.end(), 0);
        iota(tmpfa.begin(), tmpfa.end(), 0);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
            {
                if (cnt[i][j])
                    continue;
                if (i + 1 < n && !cnt[i + 1][j])
                    unionn(calc(i, j), calc(i + 1, j));
                if (j + 1 < m && !cnt[i][j + 1])
                    unionn(calc(i, j), calc(i, j + 1));
            }
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
            {
                if (s[i][j] == 'U' || s[i][j] == 'D' || s[i][j] == 'L' || s[i][j] == 'R')
                {
                    for (auto [x, y] : G[i][j])
                        --cnt[x][y];
                    for (auto [x, y] : G[i][j])
                    {
                        if (cnt[x][y])
                            continue;
                        for (int d = 0; d < 4; ++d)
                        {
                            int xx = x + dx[d], yy = y + dy[d];
                            if (xx < 0 || xx >= n || yy < 0 || yy >= m)
                                continue;
                            if (cnt[xx][yy])
                                continue;
                            tmpunionn(calc(x, y), calc(xx, yy));
                        }
                    }
                    if (check(S, T))
                    {
                        cout << i + 1 << ' ' << j + 1 << '\n';
                        return;
                    }
                    clear();
                    for (auto [x, y] : G[i][j])
                        ++cnt[x][y];
                }
            }
        cout << "-1 -1\n";
    }
};
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    cin >> T;
    while (T--)
        Main();
    return 0;
}