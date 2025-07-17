#include <bits/stdc++.h>
using namespace std;

#define int long long

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    string s;
    vector<vector<int>> op;
    vector<char> col;
    while (n--)
    {
        cin >> s;
        if (s == "Circle")
        {
            vector<int> o(3);
            cin >> o[0] >> o[1] >> o[2];
            op.push_back(o);
            char x;
            cin >> x;
            col.push_back(x);
        }
        else if (s == "Rectangle")
        {
            vector<int> o(4);
            cin >> o[0] >> o[1] >> o[2] >> o[3];
            op.push_back(o);
            char x;
            cin >> x;
            col.push_back(x);
        }
        else
        {
            int a, b, c, d;
            cin >> a >> b >> c >> d;
            vector<char> ans;
            for (int j = d; j >= b; j--)
            {
                for (int i = a; i <= c; i++)
                {
                    int f = 0;
                    for (int k = op.size() - 1; k >= 0; k--)
                    {
                        auto &o = op[k];
                        if (o.size() == 4)
                        {
                            if (i >= o[0] && i <= o[2] && j >= o[1] && j <= o[3])
                            {
                                ans.push_back(col[k]);
                                f = 1;
                                break;
                            }
                        }
                        else
                        {
                            if ((i - o[0]) * (i - o[0]) + (j - o[1]) * (j - o[1]) <= o[2] * o[2])
                            {
                                ans.push_back(col[k]);
                                f = 1;
                                break;
                            }
                        }
                    }
                    if (!f)
                    {
                        ans.push_back('.');
                    }
                }
            }

            // reverse(ans.begin(),ans.end());
            int cnt = 0;
            for (int i = 0; i < ans.size(); i++)
            {
                cout << ans[i];
                cnt++;
                if (cnt == c - a + 1)
                {
                    cout << "\n";
                    cnt = 0;
                }
            }
        }
    }
}
