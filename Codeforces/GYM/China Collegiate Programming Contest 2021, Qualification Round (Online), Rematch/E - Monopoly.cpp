#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define N 100010
ll n, m;
ll sum[N];
ll a[N];
map<ll, ll> dui;
ll cn = 0;
#define T pair<ll, ll>
#define fi first
#define se second
#define mk make_pair
#define inf 1e9
set<T> s[N], tt;
int main()
{
    //	freopen("test1.in","r",stdin);
    // freopen(".in","r",stdin);
    // freopen("test1.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    ll ti;
    cin >> ti;
    while (ti--)
    {
        for (int i = 1; i <= cn; i++)
            s[i].clear();
        cn = 0;
        tt.clear();
        dui.clear();
        cin >> n >> m;
        for (int i = 1; i <= n; i++)
            cin >> a[i], sum[i] = sum[i - 1] + a[i];
        ll tem = sum[n];
        if (!tem)
        {
            for (int i = 1; i <= n; i++)
                tt.insert(mk(sum[i], i));
            ll x;
            for (int i = 1; i <= m; i++)
            {
                cin >> x;
                if (!x)
                {
                    cout << 0 << '\n';
                    continue;
                }
                auto o = tt.lower_bound(mk(x, 0));
                if (o == tt.end() || (*o).fi != x)
                {
                    cout << -1 << '\n';
                    continue;
                }
                cout << (*o).se << '\n';
            }
            continue;
        }
        for (int i = 1; i <= n; i++)
        {
            ll o = (sum[i] % tem + tem) % tem;
            if (dui.find(o) == dui.end())
                dui[o] = ++cn;
            s[dui[o]].insert(mk(sum[i], i));
        }
        ll x;
        for (int i = 1; i <= m; i++)
        {
            cin >> x;
            if (!x)
                cout << 0 << '\n';
            else
            {
                ll o = (x % tem + tem) % tem;
                if (dui.find(o) == dui.end())
                {
                    cout << -1 << '\n';
                    continue;
                }
                else
                {
                    ll ji = dui[o];
                    if (tem < 0)
                    {
                        auto r = s[ji].lower_bound(mk(x, 0));
                        if (r == s[ji].end())
                        {
                            cout << -1 << '\n';
                            continue;
                        }
                        ll u = (x - (*r).fi) / tem * n + (*r).se;
                        cout << u << '\n';
                        continue;
                    }
                    else
                    {
                        auto r = s[ji].upper_bound(mk(x, inf));
                        if (r == s[ji].begin())
                        {
                            cout << -1 << '\n';
                            continue;
                        }
                        r--;
                        ll ttem = ((*r).fi);
                        r = s[ji].lower_bound(mk(ttem, 0));
                        ll u = (x - (*r).fi) / tem * n + ((*r).se);
                        cout << u << '\n';
                        continue;
                    }
                }
            }
        }
    }
    return 0;
}
