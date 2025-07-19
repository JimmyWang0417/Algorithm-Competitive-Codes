#include <bits/stdc++.h>
using namespace std;

#define Alice cout << "Alice" << "\n"
#define Bob cout << "Bob" << "\n"

void solve()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    if (s[0] == 'L' || s.back() == 'R')
    {
        Alice;
        return;
    }
    int cnt = 0;
    for (int i = 0; i < s.length(); i++)
    {
        cnt += (s[i] == 'R' ? 1 : -1);
        if (cnt < 0)
        {
            Alice;
            return;
        }
    }
    if (cnt)
    {
        Alice;
        return;
    }
    Bob;
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