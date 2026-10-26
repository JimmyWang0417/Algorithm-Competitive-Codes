#include <bits/stdc++.h>
using namespace std;

#define all(x) (x).begin(), (x).end()

struct Main
{
    int n, m, K;
    vector<int> a;
    vector<vector<int>> b;
    void main()
    {
        cin >> m >> n >> K;
        a.assign(n, 0);
        for (auto &x : a)
            cin >> x;
        b.assign(K, {});
        for (int j = 0, i = n - 1; i >= 0; --i)
        {
            if (i > 0)
                b[j].push_back(a[i] - a[i - 1] - 1);
            else
                b[j].push_back(a[i] - 1);
            if (++j == K)
                j = 0;
        }
        int sg = 0;
        for (auto &vec : b)
        {
            for (int i = 0; i < int(vec.size()); i += 2)
            {
                sg ^= vec[i];
            }
        }
        if (sg)
            cout << "Twinkle\n";
        else
            cout << "Nova\n";
    }
};

signed main()
{
#ifndef LOCAL
    cin.tie(nullptr)->sync_with_stdio(false);
#endif
    Main{}.main();
}
