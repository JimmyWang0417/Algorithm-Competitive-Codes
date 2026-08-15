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
constexpr int mod = 1e9 + 7;
struct Main
{
    int n;
    string s;
    struct matrix : vector<vector<i64>>
    {
        using vector<vector<i64>>::vector;
        matrix(size_t n, size_t m) : vector(n, vector<i64>(m)) {}
        auto friend operator*(const matrix &lhs, const matrix &rhs)
        {
            matrix res(lhs.size(), rhs.front().size());
            for (int i = 0; i < (int)res.size(); ++i)
                for (int j = 0; j < (int)res.front().size(); ++j)
                    for (int k = 0; k < (int)lhs.front().size(); ++k)
                        (res[i][j] += lhs[i][k] * rhs[k][j]) %= mod;
            return res;
        }
    };
    Main()
    {
        cin >> n >> s;
        matrix F(1, 4);
        {
            int x = s.front() - '0';
            F[0] = {x, x, 1, 1};
        }
        for (int i = 1; i < (int)s.size(); ++i)
        {
            int x = s[i] - '0';
            matrix G(4, 4);
            // +
            G[0][0]++, G[3][0] += x;
            G[3][1] += x;
            G[3][2]++;
            G[3][3]++;
            // *
            G[0][0]++, G[1][0] += x - 1;
            G[1][1] += x;
            G[1][2]++;
            G[3][3]++;
            // digit
            G[0][0]++, G[1][0] += 9, G[2][0] += x;
            G[1][1] += 10, G[2][1] += x;
            G[2][2]++;
            G[3][3]++;
            F = F * G;
        }
        cout << F[0][0] << '\n';
    }
};
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--)
        Main();
    return 0;
}
