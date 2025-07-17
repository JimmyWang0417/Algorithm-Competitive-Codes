#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define N 1010
ll n, m;
ll dua[N], dub[N];
set<ll> a, b;
ll dui[N];
ll fa[N << 1];
inline ll getf(ll x)
{
    if (fa[x] == x)
        return x;
    return fa[x] = getf(fa[x]);
}
int main()
{
    //	freopen("test1.in","r",stdin);
    // freopen(".in","r",stdin);
    //	freopen("test1.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    ll ti;
    cin >> ti;
    while (ti--)
    {
        a.clear();
        b.clear();
        for (int i = 1; i <= n; i++)
            dui[i] = 0;
        cin >> n >> m;
        for (int i = 1; i <= n; i++)
            dua[i] = dub[i] = 2;
        for (int i = 1; i <= 2 * n; i++)
            fa[i] = i;
        ll u, v;
        for (int i = 1; i <= m; i++)
        {
            cin >> u >> v;
            dua[u]--;
            dub[v]--;
            fa[getf(u)] = getf(v + n);
            dui[u] = v;
        }
        for (int i = 1; i <= n; i++)
            a.insert(i), b.insert(i);
        cout << 2 * n - m << '\n';
        ll g = 0, tot = 0;
        while (!a.empty())
        {
            g++;
            ll o = ((*a.begin()));
            auto p = ((b.begin()));
            while (g != 2 * n - m && (dui[o] == (*p) || getf(o) == getf(n + (*p))))
            {
                tot++;
                p++;
                assert(p != b.end());
            }
            dua[o]--;
            dub[(*p)]--;
            dui[o] = (*p);
            fa[getf(o)] = getf(n + (*p));
            cout << o << ' ' << (*p) << '\n';
            if (!dua[o])
                a.erase(o);
            if (!dub[*p])
                b.erase(p);
        } // cerr<<tot;
        for (int i = 1; i <= (n << 1); i++)
            assert(getf(i) == getf(1));
    }
    return 0;
}
