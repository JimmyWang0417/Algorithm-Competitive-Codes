#include <bits/stdc++.h>
using namespace std;

#define ld long double
#define eps 1e-8

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ld A, B;
    int n, x1, x2;

    cin >> A >> B >> n >> x1 >> x2;
    vector<ld> tip(n + 1);

    auto cul = [&](ld mid) -> ld
    {
        tip[1] = x1;
        tip[2] = mid;
        for (int i = 3; i <= n; i++)
        {
            tip[i] = A * tip[i - 1] + B * tip[i - 2];
        }
        return tip[n];
    };

    ld l = -10000, r = 10000;
    ld mid;
    while (r - l > eps)
    {
        mid = (l + r) / 2;
        if (cul(mid) < x2)
        {
            l = mid;
        }
        else
        {
            r = mid;
        }
    }

    tip[1] = x1;
    tip[2] = mid;
    for (int i = 3; i <= n; i++)
    {
        tip[i] = A * tip[i - 1] + B * tip[i - 2];
    }
    for (int i = 1; i <= n; i++)
    {
        cout << fixed << setprecision(10) << tip[i] << "\n";
    }
}