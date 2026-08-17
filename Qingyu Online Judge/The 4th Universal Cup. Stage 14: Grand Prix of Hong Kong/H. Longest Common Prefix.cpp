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
    Main()
    {
        string s;
        cin >> s;
        for (int i = 0; i + 1 < (int)s.length(); ++i)
            if (s[i] == s[i + 1])
            {
                cout << s.length() - 1 << '\n';
                return;
            }
        cout << s.length() - 2 << '\n';
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

