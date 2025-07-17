#include <bits/stdc++.h>
using namespace std;

#define fore(i, a, b) for (ll i = a, overflowed = b; i < overflowed; i++)
#define mset(a, b) memset(a, b, sizeof(a))
#define ALL(a) a.begin(), a.end()
#define SZ(a) ll(a.size())
#define fst first
#define snd second
#define pb push_back
#define FIO                  \
    ios::sync_with_stdio(0); \
    cin.tie(0);              \
    cout.tie(0)

typedef long double ld;
typedef long long ll;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;

vector<pair<ll, ll>> v;

ll sg(ll x)
{
    return x >= 0;
}

bool cmp(ll x, ll y)
{
    if (sg(v[x].fst) != sg(v[y].fst))
        return sg(v[x].fst) < sg(v[y].fst);
    if (sg(v[x].fst))
    {
        return v[x].snd < v[y].snd;
    }
    else
    {
        return v[x].fst - v[x].snd < v[y].fst - v[y].snd;
    }
}

bool solve()
{
    vector<ll> pos;
    fore(i, 0, SZ(v)) pos.pb(i);
    sort(ALL(pos), cmp);
    ll va = 0;
    for (auto i : pos)
    {
        va += v[i].fst;
        if (va > v[i].snd)
            return 0;
    }
    return 1;
}

ll fl(ll x, ll y)
{
    if (x >= 0)
        return x / y;
    return -(-x + y - 1) / y;
}

int main()
{
    FIO;
    ll t;
    cin >> t;
    while (t--)
    {
        ll n;
        cin >> n;
        vector<ll> a(n), b(n), c(n);
        fore(i, 0, n) cin >> a[i] >> b[i] >> c[i];
        auto na = a;
        fore(i, 0, n) a[i] -= b[i];
        ll sb = 0;
        for (auto i : b)
            sb += i;
        vector<ll> d(n);
        fore(i, 0, n) d[i] = (sb + b[i]) * c[i];
        ll l = 0, r = 2e18;
        while (l <= r)
        {
            ll m = (l + r) / 2;
            v.clear();
            fore(i, 0, n) v.pb({a[i], fl(m - d[i], c[i])});
            if (solve())
                r = m - 1;
            else
                l = m + 1;
        }
        // cout<<l<<"\n";
        v.clear();
        fore(i, 0, n) v.pb({a[i], fl(l - d[i], c[i])});
        vector<ll> res(n);
        fore(i, 0, n) res[i] = i;
        sort(ALL(res), cmp);
        for (auto i : res)
            cout << i + 1 << " ";
        cout << "\n";
    }
    return 0;
}