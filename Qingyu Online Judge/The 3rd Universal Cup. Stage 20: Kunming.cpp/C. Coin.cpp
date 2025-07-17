#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve()
{
    int n, k;
    cin >> n >> k;
    int fir = 1;
    int d = 1;
    while (1)
    {
        int r = d * k;
        int tim = (r - fir) / d;
        fir = tim * d + fir;
        if (fir >= n)
        {
            fir -= tim * d;
            tim = (n - fir) / d;
            fir = tim * d + fir;
            cout << fir << "\n";
            break;
        }
        d = max(d + 1, (fir + d + k - 1) / k);
    }
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
}