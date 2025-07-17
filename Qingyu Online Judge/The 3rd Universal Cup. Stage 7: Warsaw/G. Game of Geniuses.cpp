#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> ans(n);
    for (int i = 0; i < n; i++)
    {
        vector<int> o(n);
        for (int j = 0; j < n; j++)
        {
            cin >> o[j];
        }
        ans[i] = *min_element(o.begin(), o.end());
    }

    cout << *max_element(ans.begin(), ans.end()) << "\n";
}