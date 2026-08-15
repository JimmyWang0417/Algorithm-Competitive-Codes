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
struct Main
{
    int n, m, q;
    Main()
    {
        cin >> n >> m >> q;
        set<int> row{0, n}, col{0, m};
        multiset<int> R{n}, C{m};
        while (q--)
        {
            int opt, k;
            cin >> opt >> k;
            if (opt == 1)
            {
                auto it = row.lower_bound(k);
                auto x = *prev(it), y = *it;
                R.erase(R.find(y - x));
                R.insert(k - x), R.insert(y - k);
                row.insert(k);
            }
            else
            {
                auto it = col.lower_bound(k);
                auto x = *prev(it), y = *it;
                C.erase(C.find(y - x));
                C.insert(k - x), C.insert(y - k);
                col.insert(k);
            }
            cout << (i64)*R.rbegin() * *C.rbegin() << '\n';
        }
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

