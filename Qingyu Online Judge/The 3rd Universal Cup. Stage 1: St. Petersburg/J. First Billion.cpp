#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

stringstream A;

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<pair<int, int>> tip(n);
    for (int i = 0; i < n; i++)
    {
        cin >> tip[i].first;
        tip[i].second = i;
    }
    // cout<<tip[6].first+tip[8].first+tip[4].first+tip[5].first+tip[0].first<<endl;
    sort(tip.begin(), tip.end());
    vector<int> use(min(40, n));
    vector<vector<int>> son(min(40, n));

    for (int i = 0; i < min(40, n); i++)
    {
        use[i] = tip[i].first;
        son[i].push_back(tip[i].second);
    }

    int pos = 0;
    for (int i = 40; i < n; i++)
    {
        use[pos] += tip[i].first;
        son[pos].push_back(tip[i].second);
        ++pos;
        pos %= 40;
    }

    n = use.size();
    auto out = [&](int bit, int f) -> int
    {
        int res = 0;
        for (int i = 0; i < n / 2; i++)
        {
            if ((bit >> i) & 1)
            {
                int p = i;
                if (f == 2)
                {
                    p += n / 2;
                }
                res += son[p].size();
                for (auto j : son[p])
                {
                    A << j + 1 << " ";
                }
            }
        }
        return res;
    };

    gp_hash_table<int, int> a, b;
    for (int i = 0; i < (1 << (n / 2)); i++)
    {
        int now_a = 0;
        int now_b = 0;
        for (int j = 0; j < n / 2; j++)
        {
            if ((i >> j) & 1)
            {
                now_a += use[j];
                now_b += use[j + n / 2];
            }
        }
        a[now_a] = i;
        b[now_b] = i;
        if (now_a == 1e9)
        {
            cout << out(i, 1) << " ";
            cout << A.str();
            return 0;
        }
        if (now_b == 1e9)
        {
            cout << out(i, 2) << " ";
            cout << A.str();
            return 0;
        }
    }

    for (auto [x, y] : a)
    {
        int need = 1e9 - x;
        if (b[need])
        {
            cout << out(y, 1) +
                        out(b[need], 2)
                 << " ";
            cout << A.str();
            return 0;
        }
    }

    // assert(0);
}