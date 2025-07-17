#include <bits/stdc++.h>
using namespace std;

void solve()
{
    int n, l;
    cin >> n >> l;
    vector<pair<int, int>> tip(n + 1);
    vector<pair<int, int>> has;
    for (int i = 1; i <= n; i++)
    {
        cin >> tip[i].first >> tip[i].second;
        if (tip[i].first == -1 && tip[i].second == -1)
        {
            continue;
        }
        has.push_back(tip[i]);
    }
    if (n > l)
    {
        cout << "NIE" << "\n";
        return;
    }
    if (has.empty())
    {
        if (n <= l)
        {
            cout << "TAK" << "\n";
        }
        else
        {
            cout << "NIE" << "\n";
        }
        return;
    }
    sort(has.begin(), has.end(), [&](pair<int, int> &a, pair<int, int> &b)
         { return max(a.first, a.second) < max(b.first, b.second); });
    int ok = 0;
    int ook = 0;
    for (int i = 0; i < has.size() - 1; i++)
    {
        if (max(has[i].first, has[i].second) >= max(has[i + 1].first, has[i + 1].second))
        {
            cout << "NIE" << "\n";
            return;
        }
        if (min(has[i + 1].first, has[i + 1].second) != -1 && max(has[i].first, has[i].second) >= min(has[i + 1].first, has[i + 1].second))
        {
            cout << "NIE" << "\n";
            return;
        }
        if (has[i].second != -1 && has[i + 1].first != -1 && has[i + 1].first - has[i].second >= 2)
        {
            ook++;
        }
        if (min(has[i + 1].first, has[i + 1].second) == -1)
            ok += max(has[i + 1].first, has[i + 1].second) - max(has[i].first, has[i].second) - 1;
        else
            ok += min(has[i + 1].first, has[i + 1].second) - max(has[i].first, has[i].second) - 1;
    }
    int ma = max(has.back().first, has.back().second);
    int mi = has[0].first;
    if (mi == -1)
    {
        mi = has[0].second;
    }
    ok += mi - 1 + l - ma;
    if (has[0].first != -1 && has[0].first > 1)
    {
        ook++;
    }
    if (has.back().second != -1 && has.back().second < l)
    {
        ook++;
    }
    if (ok >= n - has.size() && n - has.size() >= ook)
    {
        cout << "TAK" << "\n";
    }
    else
    {
        cout << "NIE" << "\n";
    }
}

int main()
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