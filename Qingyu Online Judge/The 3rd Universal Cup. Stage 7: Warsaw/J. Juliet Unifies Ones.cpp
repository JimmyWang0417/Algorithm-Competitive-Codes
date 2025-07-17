#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    int n = s.length();
    s = ' ' + s;
    vector<int> tsum(n + 1);
    for (int i = 1; i <= n; i++)
    {
        tsum[i] = tsum[i - 1] + (s[i] == '1');
    }

    int ans = 1e9;
    for (int i = 1; i <= n; i++)
    {
        for (int j = i; j <= n; j++)
        {
            if (tsum[j] - tsum[i - 1])
                ans = min(ans, tsum[i - 1] + tsum[n] - tsum[j] + j - i + 1 - (tsum[j] - tsum[i - 1]));
            else
                ans = min(ans, tsum[i - 1] + tsum[n] - tsum[j]);
        }
    }

    cout << ans << "\n";
}