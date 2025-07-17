#include <bits/stdc++.h>
using namespace std;

inline int c2d(const char &c)
{
    if (c == 'D')
        return 0;
    else if (c == 'C')
        return 1;
    else if (c == 'H')
        return 2;
    else
        return 3; // c=='S'
}

void solve()
{
    int n;
    cin >> n;
    vector<int> a(4);
    string s;
    for (int i = 1; i <= n; i++)
    {
        cin >> s;
        a[c2d(s[1])]++;
    }
    vector<int> b(6);
    for (int i = 0; i <= 5; i++)
    {
        cin >> b[i];
    }
    if (b[4])
    {
        b[4] += b[5];
        b[5] = 0;
    }
    auto check = [&](int ii, int jj, int kk, int pp) -> int
    {
        vector<int> need = {ii, jj, kk, pp};
        for (int i = 0; i <= 3; i++)
        {
            for (int fuck = 0; fuck <= 3; fuck++)
            {
                for (int iii = 0; iii <= 3; iii++)
                {
                    for (int ffuck = 0; ffuck <= 3; ffuck++)
                    {
                        vector<int> aa(a);
                        int bbb = b[4];
                        if (bbb && aa[fuck])
                            aa[i]++, aa[fuck]--, bbb--;
                        if (bbb && aa[ffuck])
                            aa[iii]++, aa[ffuck]--;
                        for (int j = 0; j <= 3; j++)
                        {
                            if (b[j] && aa[j] < need[j])
                            {
                                int add = 0;
                                for (int k = 0; k <= 3; k++)
                                {
                                    if (aa[j] < need[j] && aa[k] > need[k])
                                    {
                                        aa[j] += (aa[k] - need[k]);
                                        add += (aa[k] - need[k]);
                                        aa[k] = need[k];
                                        if (add > 3)
                                        {
                                            aa[j] -= (add - 3);
                                            aa[k] += (add - 3);
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                        int f = b[5];
                        int flag = 1;
                        for (int j = 0; j <= 3; j++)
                        {
                            if (need[j] - aa[j] > 1)
                            {
                                flag = 0;
                                break;
                            }
                            if (aa[j] == 0 && need[j])
                            {
                                flag = 0;
                                break;
                            }
                            if (need[j] - aa[j] == 1)
                            {
                                if (!f)
                                {
                                    flag = 0;
                                    break;
                                }
                                else
                                {
                                    int ff = 0;
                                    for (int k = 0; k <= 3; k++)
                                    {
                                        if (aa[k] - need[k] >= 1)
                                        {
                                            ff = 1;
                                            break;
                                        }
                                    }
                                    if (!ff)
                                    {
                                        flag = 0;
                                        break;
                                    }
                                    f = 0;
                                }
                            }
                        }
                        if (flag)
                        {
                            return 1;
                        }
                    }
                }
            }
        }
        return 0;
    };
    int ans = 0;
    for (int i = 0; i <= 3; i++)
    {
        for (int j = 0; j <= 3; j++)
        {
            for (int k = 0; k <= 3; k++)
            {
                for (int p = 0; p <= 3; p++)
                {
                    if (check(i * 5, j * 5, k * 5, p * 5))
                    {
                        ans = max(ans, i + j + k + p);
                    }
                }
            }
        }
    }
    cout << ans << "\n";
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