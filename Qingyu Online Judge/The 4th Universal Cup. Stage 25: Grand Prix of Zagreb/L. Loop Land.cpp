#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>
using namespace std;
typedef int64_t i64;
typedef uint64_t u64;
typedef __int128_t i128;
typedef __uint128_t u128;
typedef __float80 f80;
typedef __float128 f128;
constexpr int mod = 1e6 + 3;
template <typename T = int>
constexpr auto quickpow(i64 a, T b = mod - 2)
{
    a %= mod;
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
    int n, m;
    vector<int> col;
    vector<vector<pair<int, int>>> G;
    auto addEdge(int u, int v, int w = 1)
    {
        G[u].emplace_back(v, w);
        G[v].emplace_back(u, w);
    }
    auto dfs(int u, int c) -> void
    {
        col[u] = c;
        for (auto [v, w] : G[u])
        {
            if (col[v])
                continue;
            dfs(v, (c - 1 + w) % 2 + 1);
        }
    }
    auto calc(int x, int y, int k)
    {
        return x * m * 4 + y * 4 + k;
    }
    vector<string> a;
    Main()
    {
        cin >> n >> m;
        a.resize(n);
        for (auto &s : a)
            cin >> s;
        int s = 4 * n * m, t = 4 * n * m + 1;
        G.resize(t + 1), col.resize(t + 1);
        addEdge(s, t);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
            {
                if (i - 1 >= 0)
                    addEdge(calc(i - 1, j, 2), calc(i, j, 0), 0);
                else
                    addEdge(t, calc(i, j, 0));
                if (j - 1 >= 0)
                    addEdge(calc(i, j - 1, 3), calc(i, j, 1), 0);
                else
                    addEdge(t, calc(i, j, 1));
                if (i + 1 == n)
                    addEdge(t, calc(i, j, 2));
                if (j + 1 == m)
                    addEdge(t, calc(i, j, 3));
            }
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
            {
                if (a[i][j] == '0')
                {
                    for (int k = 0; k < 4; ++k)
                        addEdge(t, calc(i, j, k));
                }
                else if (a[i][j] == '1')
                {
                    for (int k = 0; k < 4; ++k)
                        addEdge(calc(i, j, k), calc(i, j, (k + 1) % 4));
                }
                else if (a[i][j] == '2')
                {
                    addEdge(calc(i, j, 0), calc(i, j, 2));
                    addEdge(calc(i, j, 1), calc(i, j, 3));
                }
                else if (a[i][j] == '3')
                {
                    addEdge(t, calc(i, j, 1));
                    addEdge(t, calc(i, j, 2));
                    addEdge(calc(i, j, 0), calc(i, j, 3));
                }
                else if (a[i][j] == '4')
                {
                    addEdge(t, calc(i, j, 1));
                    addEdge(t, calc(i, j, 3));
                    addEdge(calc(i, j, 0), calc(i, j, 2));
                }
                else if (a[i][j] == '5')
                {
                    addEdge(t, calc(i, j, 2));
                    addEdge(t, calc(i, j, 3));
                    addEdge(calc(i, j, 0), calc(i, j, 1));
                }
                else if (a[i][j] == '6')
                {
                    addEdge(t, calc(i, j, 0));
                    addEdge(t, calc(i, j, 1));
                    addEdge(calc(i, j, 2), calc(i, j, 3));
                }
                else if (a[i][j] == '7')
                {
                    addEdge(t, calc(i, j, 0));
                    addEdge(t, calc(i, j, 2));
                    addEdge(calc(i, j, 1), calc(i, j, 3));
                }
                else if (a[i][j] == '8')
                {
                    addEdge(t, calc(i, j, 0));
                    addEdge(t, calc(i, j, 3));
                    addEdge(calc(i, j, 1), calc(i, j, 2));
                }
                else if (a[i][j] == '9')
                {
                    for (int k = 0; k < 4; ++k)
                        addEdge(s, calc(i, j, k));
                }
                else if (a[i][j] == 'A')
                {
                    addEdge(s, calc(i, j, 1));
                    addEdge(s, calc(i, j, 3));
                    addEdge(calc(i, j, 0), calc(i, j, 2));
                }
                else
                {
                    addEdge(s, calc(i, j, 0));
                    addEdge(s, calc(i, j, 2));
                    addEdge(calc(i, j, 1), calc(i, j, 3));
                }
            }
        for (int i = 0; i <= t; ++i)
        {
            if (col[i])
                continue;
            dfs(i, 1);
        }
        for (int i = 0; i < 2 * n - 1; ++i)
        {
            for (int j = 0; j < 2 * m - 1; ++j)
            {
                if (i & 1)
                {
                    if (j & 1)
                        cout << '.';
                    else if (col[calc(i / 2, j / 2, 2)] != col[s])
                        cout << '|';
                    else
                        cout << '.';
                }
                else
                {
                    if (j & 1)
                    {
                        if (col[calc(i / 2, j / 2, 3)] != col[s])
                            cout << '-';
                        else
                            cout << '.';
                    }
                    else
                        cout << (a[i / 2][j / 2] != '0' ? 'o' : '.');
                }
            }
            cout << '\n';
        }
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

