#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
struct Main
{
    Main()
    {
        i64 n;
        cin >> n;
        if (n % 2 == 1)
            cout << "No\n";
        else
            cout << "Yes\n" << n / 2 << ' ' << n / 2 << '\n';
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
