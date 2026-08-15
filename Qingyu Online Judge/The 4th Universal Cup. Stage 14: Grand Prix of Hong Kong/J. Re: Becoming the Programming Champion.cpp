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
struct Main
{
    int n, a[3];
    vector<int> b[3];
    Main()
    {
        i64 s = 0, st = 0;
        i64 t;
        cin >> n >> a[0] >> a[1] >> a[2];
        for (int i = 0; i < n; ++i)
        {
            int p, c;
            cin >> p >> c;
            s += c;
            b[p - 1].push_back(c);
        }
        for (int i = 0; i < 3; ++i)
            sort(b[i].begin(), b[i].end());
        cin >> t;
        while (s)
        {
            st += s;
            int pos = 0, mx = 0;
            for (int i = 0; i < 3; ++i)
                if (!b[i].empty() && s <= a[i] && mx < b[i].back())
                {
                    pos = i;
                    mx = b[i].back();
                }
            if (!mx)
                break;
            b[pos].pop_back();
            s -= mx;
        }
        cout << ((!s && st < t) ? "YES\n" : "NO\n");
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

