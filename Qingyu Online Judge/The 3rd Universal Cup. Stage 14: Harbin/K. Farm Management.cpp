#include <bits/stdc++.h>
using namespace std;
#define int long long
int a[100010], l[100010], r[100010];
int s[100010], s2[100010];
int n, m;
const int INF = 1e9;
struct node
{
    int a, sheng, l;
    bool operator<(const node &b) const
    {
        return a > b.a;
    }
};
vector<node> v;
int qry(int l, int t)
{
    int e = lower_bound(s + 1, s + n + 1, t) - s;
    e = min(e, l);
    return s2[e - 1] + (t - s[e - 1]) * v[e].a;
}
signed main()
{
    cin >> n >> m;
    int sum = 0;
    int cnt2 = 0;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i] >> l[i] >> r[i];
        v.push_back({a[i], r[i] - l[i], l[i]});
        sum += a[i] * l[i];
        cnt2 += l[i];
    }
    v.push_back({INF, 0, 0});
    sort(v.begin(), v.end());
    for (int i = 1; i <= n; i++)
    {
        s2[i] = s2[i - 1] + v[i].a * v[i].sheng;
        s[i] = s[i - 1] + v[i].sheng;
    }
    int cnt = m - cnt2;
    int max1 = 0;
    int ans;
    for (int i = 1; i <= n; i++)
    {
        int l = v[i].l;
        int sheng = v[i].sheng;
        int a = v[i].a;
        ans = sum - a * l + qry(i, cnt + l);
        max1 = max(max1, ans);
    }
    cout << max1 << endl;
}