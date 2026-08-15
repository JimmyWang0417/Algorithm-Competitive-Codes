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
constexpr double eps = 1e-7;
struct Main
{
    Main()
    {
        int n;
        cin >> n;
        vector<int> a(n + 5), b(n + 5);
        for (int i = 1; i <= n; ++i)
            cin >> a[i];
        for (int i = 1; i <= n; ++i)
            cin >> b[i];
        vector<pair<int, int>> answer;
        for (int i = 1; i <= n; ++i)
        {
            if (a[i] <= b[i])
                continue;
            vector<pair<int, int>> p;
            for (int j = 1; j < i; ++j)
                p.emplace_back(a[j], j);
            sort(p.begin(), p.end(), greater<>());
            for (auto [_, j] : p)
            {
                if (a[i] <= b[i])
                    break;
                if (a[i] > a[j] && b[j] >= a[i])
                {
                    answer.emplace_back(i, j);
                    swap(a[i], a[j]);
                }
            }
            if (a[i] > b[i])
            {
                cout << "NO\n";
                return;
            }
        }
        cout << "YES\n"
             << answer.size() << '\n';
        for (auto [x, y] : answer)
            cout << y << ' ' << x << '\n';
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

