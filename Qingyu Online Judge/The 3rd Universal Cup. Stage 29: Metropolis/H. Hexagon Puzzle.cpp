#include <bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
constexpr int N = 1e6 + 5;
int nx[11];
int n, col[1100][1100];
inline void _main()
{
    auto print = []()
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n - i; j++)
                cout << ' ';
            for (int j = 1; j <= i; j++)
            {
                if (!col[i][j])
                    cout << '.';
                else
                    cout << (char)('A' + col[i][j] - 1);
                if (j != i)
                    cout << ' ';
            }
            if (i != n)
                cout << '\n';
        }
    };
    cin >> n;
    if (n <= 2)
    {
        print();
        return;
    }
    nx[1] = 2, nx[2] = 3, nx[3] = 4, nx[4] = 5, nx[5] = 1;
    nx[6] = 7, nx[7] = 8, nx[8] = 9, nx[9] = 10, nx[10] = 6;
    if ((n % 3) == 1)
    {
        col[1][1] = col[2][1] = col[3][2] = 1, col[3][1] = col[4][2] = col[4][3] = 2;
        for (int i = 5; i <= n; i += 3)
        {
            int p = (i & 1) ? 6 : 1, j;
            col[i - 1][1] = col[i][1] = col[i + 1][2] = p, p = nx[p];
            col[i + 1][1] = col[i + 2][2] = col[i + 2][3] = p, p = nx[p];
            for (j = 2; j <= i - 3; j += 2)
            {
                col[i][j] = col[i][j + 1] = col[i + 1][j + 2] = p, p = nx[p];
                col[i + 1][j + 1] = col[i + 2][j + 2] = col[i + 2][j + 3] = p, p = nx[p];
            }
            if (j == i - 1)
            {
                col[i - 1][i - 1] = col[i][i - 1] = col[i + 1][i] = p, p = nx[p];
                col[i][i] = col[i + 1][i + 1] = col[i + 2][i + 1] = p, p = nx[p];
            }
            else
            {
                col[i][i - 2] = col[i][i - 1] = col[i - 1][i - 1] = p, p = nx[p];
                col[i + 1][i - 1] = col[i + 1][i] = col[i][i] = p, p = nx[p];
                col[i + 2][i] = col[i + 2][i + 1] = col[i + 1][i + 1] = p, p = nx[p];
            }
        }
    }
    else if ((n % 3) == 0)
    {
        col[1][1] = col[2][1] = col[3][2] = 1;
        for (int i = 4; i <= n; i += 3)
        {
            int p = (i & 1) ? 1 : 6, j;
            col[i - 1][1] = col[i][1] = col[i + 1][2] = p, p = nx[p];
            col[i + 1][1] = col[i + 2][2] = col[i + 2][3] = p, p = nx[p];
            for (j = 2; j <= i - 3; j += 2)
            {
                col[i][j] = col[i][j + 1] = col[i + 1][j + 2] = p, p = nx[p];
                col[i + 1][j + 1] = col[i + 2][j + 2] = col[i + 2][j + 3] = p, p = nx[p];
            }
            if (j == i - 1)
            {
                col[i - 1][i - 1] = col[i][i - 1] = col[i + 1][i] = p, p = nx[p];
                col[i][i] = col[i + 1][i + 1] = col[i + 2][i + 1] = p, p = nx[p];
            }
            else
            {
                col[i][i - 2] = col[i][i - 1] = col[i - 1][i - 1] = p, p = nx[p];
                col[i + 1][i - 1] = col[i + 1][i] = col[i][i] = p, p = nx[p];
                col[i + 2][i] = col[i + 2][i + 1] = col[i + 1][i + 1] = p, p = nx[p];
            }
        }
    }
    else
    {
        col[1][1] = col[2][1] = col[3][2] = 1;
        col[2][2] = col[3][3] = col[4][3] = 2;
        col[3][1] = col[4][1] = col[5][2] = 3;
        col[4][2] = col[5][3] = col[5][4] = 4;
        for (int i = 6; i <= n; i += 3)
        {
            int p = (i & 1) ? 1 : 6, j;
            col[i - 1][1] = col[i][1] = col[i + 1][2] = p, p = nx[p];
            col[i + 1][1] = col[i + 2][2] = col[i + 2][3] = p, p = nx[p];
            for (j = 2; j <= i - 3; j += 2)
            {
                col[i][j] = col[i][j + 1] = col[i + 1][j + 2] = p, p = nx[p];
                col[i + 1][j + 1] = col[i + 2][j + 2] = col[i + 2][j + 3] = p, p = nx[p];
            }
            if (j == i - 1)
            {
                col[i - 1][i - 1] = col[i][i - 1] = col[i + 1][i] = p, p = nx[p];
                col[i][i] = col[i + 1][i + 1] = col[i + 2][i + 1] = p, p = nx[p];
            }
            else
            {
                col[i][i - 2] = col[i][i - 1] = col[i - 1][i - 1] = p, p = nx[p];
                col[i + 1][i - 1] = col[i + 1][i] = col[i][i] = p, p = nx[p];
                col[i + 2][i] = col[i + 2][i + 1] = col[i + 1][i + 1] = p, p = nx[p];
            }
        }
    }
    print();
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