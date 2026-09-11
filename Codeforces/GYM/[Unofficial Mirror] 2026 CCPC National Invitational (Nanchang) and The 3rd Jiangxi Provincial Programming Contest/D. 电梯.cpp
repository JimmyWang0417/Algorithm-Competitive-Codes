#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
struct Main
{
    int n;
    vector<vector<int>> answer;
    vector<bool> vis;
    Main()
    {
        cin >> n;
        vis.resize(n);
        for (int i = 1; i < n; ++i)
            for (int j = 0; j < i; ++j)
            {
                vector<int> p;
                for (int k = j; k < n; k += i)
                    p.emplace_back(k);
                if (p.front() != 0)
                    p.insert(p.begin(), 0);
                if (p.back() != n - 1)
                    p.push_back(n - 1);
                if (p.size() == 3)
                {
                    if (!vis[p[1]])
                    {
                        vis[p[1]] = true;
                        answer.emplace_back(p);
                    }
                }
                else
                    answer.emplace_back(p);
            }
        cout << answer.size() << '\n';
        for (const auto &i : answer)
        {
            for (auto j : i)
                cout << (j + 1) << ' ';
            cout << '\n';
        }
    }
};
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    while (T--)
        Main();
    return 0;
}