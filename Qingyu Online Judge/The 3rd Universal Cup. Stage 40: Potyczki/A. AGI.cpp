#include <bits/stdc++.h>
using namespace std;
constexpr int limit = 6;
auto _main()
{
    int n;
    cin >> n;
    vector<tuple<int, int, int>> a(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> get<0>(a[i]) >> get<1>(a[i]);
        get<2>(a[i]) = i;
    }
    sort(a.begin(), a.end());
    string s(n, 'N');
    for (int i = 0; i < n - 1; i += 2)
    {
        if (get<1>(a[i]) <= get<1>(a[i + 1]))
            s[get<2>(a[i + 1])] = 'T';
        else
            s[get<2>(a[i])] = 'T';
    }
    cout << s << '\n';
}
signed main()
{
    int T = 1;
    cin >> T;
    while (T--)
        _main();
    return 0;
}
