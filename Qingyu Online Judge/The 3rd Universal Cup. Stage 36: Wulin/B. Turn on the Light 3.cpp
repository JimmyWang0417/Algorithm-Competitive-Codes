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
constexpr int mod = 998244353;
template <typename T>
auto &operator<<(ostream &in, const vector<T> &rhs)
{
    for (auto i : rhs)
        in << i << ' ';
    return in;
}
struct Main
{
    int n, m;
    Main()
    {
        cin >> n >> m;
        vector<bool> vis(n + 5);
        for (int i = 1; i <= m; ++i)
        {
            int x;
            cin >> x;
            if (vis[x])
                cout << "the lights are already on!\n";
            else
            {
                int res = 0;
                for (int j = x; j <= n; j += x)
                {
                    if (vis[j])
                        continue;
                    ++res;
                    vis[j] = true;
                }
                cout << res << '\n';
            }
        }
    }
};
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    cin >> T;
    while (T--)
        Main();
    return 0;
}
