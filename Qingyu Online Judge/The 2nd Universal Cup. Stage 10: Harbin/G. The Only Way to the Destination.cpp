#include <bits/stdc++.h>
typedef long long ll;
#define int ll
using namespace std;
constexpr int N = 1e6 + 5;
int n, m, q;
struct node
{
    int l, r, y;
    inline bool operator<(const node &rhs) const
    {
        return y == rhs.y ? l < rhs.l : y < rhs.y;
    }
} a[N];
pair<int, int> buf[2][N];
int ptot, qtot;
int p[N], tot;
int pre[N];
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n >> m >> q;
    int point = n * m, edge = 0;
    for (int i = 1; i <= q; ++i)
    {
        cin >> a[i].l >> a[i].r >> a[i].y;
        point -= a[i].r - a[i].l + 1;
    }
    sort(a + 1, a + 1 + q);
    auto f = buf[0], g = buf[1];
    for (int i = 1, j = 1; i <= q; i = j)
    {
        while (j <= q && a[i].y == a[j].y)
            ++j;
        if (a[i].y > a[i - 1].y + 1)
        {
            edge += (n - 1) * (a[i].y - a[i - 1].y - 1) + n * (a[i].y - a[i - 1].y - 2);
            f[ptot = 1] = make_pair(1, n);
            tot = 0;
            for (int l = 1; l <= ptot; ++l)
            {
                p[++tot] = f[l].first;
                p[++tot] = f[l].second + 1;
            }
            for (int r = 1; r <= qtot; ++r)
            {
                p[++tot] = g[r].first;
                p[++tot] = g[r].second + 1;
            }
            sort(p + 1, p + 1 + tot);
            tot = (int)(unique(p + 1, p + 1 + tot) - p - 1);
            for (int l = 1; l <= ptot; ++l)
            {
                int ql = (int)(lower_bound(p + 1, p + 1 + tot, f[l].first) - p);
                int qr = (int)(lower_bound(p + 1, p + 1 + tot, f[l].second + 1) - p);
                pre[ql] ++, pre[qr] --;
            }
            for (int r = 1; r <= qtot; ++r)
            {
                int ql = (int)(lower_bound(p + 1, p + 1 + tot, g[r].first) - p);
                int qr = (int)(lower_bound(p + 1, p + 1 + tot, g[r].second + 1) - p);
                pre[ql] ++, pre[qr] --;
            }
            for (int k = 1; k < tot; ++k)
            {
                pre[k] += pre[k - 1];
                edge += (p[k + 1] - p[k]) * (pre[k] == 2);
            }
            for (int k = 1; k <= tot; ++k)
                pre[k] = 0;
            swap(f, g);
            swap(ptot, qtot);
        }
        ptot = 0;
        if (1 <= a[i].l - 1)
            f[++ptot] = make_pair(1, a[i].l - 1);
        for (int k = i + 1; k < j; ++k)
            if (a[k - 1].r + 1 <= a[k].l - 1)
                f[++ptot] = make_pair(a[k - 1].r + 1, a[k].l - 1);
        if (a[j - 1].r + 1 <= n)
            f[++ptot] = make_pair(a[j - 1].r + 1, n);
//        for (int k = 1; k <= ptot; ++k)
//        	cout << f[k].first << ' ' << f[k].second << '\n';
        for (int k = 1; k <= ptot; ++k)
            edge += f[k].second - f[k].first;
            tot = 0;
            for (int l = 1; l <= ptot; ++l)
            {
                p[++tot] = f[l].first;
                p[++tot] = f[l].second + 1;
            }
            for (int r = 1; r <= qtot; ++r)
            {
                p[++tot] = g[r].first;
                p[++tot] = g[r].second + 1;
            }
            sort(p + 1, p + 1 + tot);
            tot = (int)(unique(p + 1, p + 1 + tot) - p - 1);
            for (int l = 1; l <= ptot; ++l)
            {
                int ql = (int)(lower_bound(p + 1, p + 1 + tot, f[l].first) - p);
                int qr = (int)(lower_bound(p + 1, p + 1 + tot, f[l].second + 1) - p);
                pre[ql] ++, pre[qr] --;
            }
            for (int r = 1; r <= qtot; ++r)
            {
                int ql = (int)(lower_bound(p + 1, p + 1 + tot, g[r].first) - p);
                int qr = (int)(lower_bound(p + 1, p + 1 + tot, g[r].second + 1) - p);
                pre[ql] ++, pre[qr] --;
            }
            for (int k = 1; k < tot; ++k)
            {
                pre[k] += pre[k - 1];
                edge += (p[k + 1] - p[k]) * (pre[k] == 2);
            }
            for (int k = 1; k <= tot; ++k)
                pre[k] = 0;
        swap(f, g);
        swap(ptot, qtot);
    }
    if (a[q].y != m)
    {
            edge += (n - 1) * (m - a[q].y) + n * (m - a[q].y - 1);
            f[ptot = 1] = make_pair(1, n);
            tot = 0;
            for (int l = 1; l <= ptot; ++l)
            {
                p[++tot] = f[l].first;
                p[++tot] = f[l].second + 1;
            }
            for (int r = 1; r <= qtot; ++r)
            {
                p[++tot] = g[r].first;
                p[++tot] = g[r].second + 1;
            }
            sort(p + 1, p + 1 + tot);
            tot = (int)(unique(p + 1, p + 1 + tot) - p - 1);
            for (int l = 1; l <= ptot; ++l)
            {
                int ql = (int)(lower_bound(p + 1, p + 1 + tot, f[l].first) - p);
                int qr = (int)(lower_bound(p + 1, p + 1 + tot, f[l].second + 1) - p);
                pre[ql] ++, pre[qr] --;
            }
            for (int r = 1; r <= qtot; ++r)
            {
                int ql = (int)(lower_bound(p + 1, p + 1 + tot, g[r].first) - p);
                int qr = (int)(lower_bound(p + 1, p + 1 + tot, g[r].second + 1) - p);
                pre[ql] ++, pre[qr] --;
            }
            for (int k = 1; k < tot; ++k)
            {
                pre[k] += pre[k - 1];
                edge += (p[k + 1] - p[k]) * (pre[k] == 2);
            }
            for (int k = 1; k <= tot; ++k)
                pre[k] = 0;
            swap(f, g);
            swap(ptot, qtot);
    }
//    cout << point << ' ' << edge << endl;
    if (point == edge + 1 && point)
        cout << "YES\n";
    else
        cout << "NO\n";
    return 0;
}