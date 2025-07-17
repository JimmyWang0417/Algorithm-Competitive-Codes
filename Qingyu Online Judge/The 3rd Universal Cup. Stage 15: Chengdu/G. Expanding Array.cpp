#include <bits/stdc++.h>
using namespace std;

signed main()
{
    int n;
    cin >> n;
    vector<int> tip(n + 1);
    set<int> tot;
    for (int i = 1; i <= n; i++)
    {
        cin >> tip[i];
        tot.insert(tip[i]);
    }

    auto g = [&](int x, int y) -> void
    {
        for (int i = 0; i <= 1; i++)
        {
            for (int j = 0; j <= 1; j++)
            {
                for (int k = 0; k <= 1; k++)
                {
                    int o = 0;
                    for (int p = 0; p < 30; p++)
                    {
                        int a = (x >> p) & 1;
                        int b = (y >> p) & 1;
                        if (a & b)
                        {
                            o += i * (1 << p);
                        }
                        if (a == 0 && b == 1)
                        {
                            o += j * (1 << p);
                        }
                        if (a == 1 && b == 0)
                        {
                            o += k * (1 << p);
                        }
                    }
                    tot.insert(o);
                }
            }
        }
    };

    for (int i = 1; i < n; i++)
    {
        g(tip[i], tip[i + 1]);
    }
    cout << tot.size() << "\n";
}