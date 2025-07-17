#include <bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
constexpr int N = 2e5 + 5;
inline int query(int l, int r)
{
    int x;
    cout << l << ' ' << r << endl;
    cin >> x;
    if (x == 0)
        exit(0);
    return x;
}
inline void dfs(const vector<int> &p)
{
    if (p.size() <= 1)
        return;
    vector<int> q[51];
    for (int i = 1; i < (int)p.size(); ++i)
        q[query(p[0], p[i])].push_back(p[i]);
    for (int i = 1; i <= 50; ++i)
        dfs(q[i]);
}
inline void _main()
{
    int n;
    cin >> n;
    vector<int> a(n);
    iota(a.begin(), a.end(), 1);
    dfs(a);
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--)
        _main();
    return 0;
}