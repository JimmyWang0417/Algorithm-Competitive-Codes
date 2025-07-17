#include <bits/stdc++.h>
using namespace std;
constexpr int N = 2e3 + 5;
typedef long long ll;
int n;
struct node
{
	int x, y;
	node(int _x = 0, int _y = 0) : x(_x), y(_y) {}
	inline ll operator*(const node &rhs) const
	{
		return (ll)x * rhs.y - (ll)y * rhs.x;
	}
	inline double get()
	{
		return atan2(y, x);
	}
	inline node operator+(const node &rhs) const
	{
		return node(x + rhs.x, y + rhs.y);
	}
	inline node operator-(const node &rhs) const
	{
		return node(x - rhs.x, y - rhs.y);
	}
} a[N];
int b[N], m;
int c[N], q;
double d[N];
bool vis[N];
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; ++i)
	{
		int x, y;
		cin >> x >> y;
		a[i] = node(x, y);
	}
	swap(a[1], *min_element(a + 1, a + 1 + n, [](node x, node y)
		{
			return x.x < y.x;
		}));
	sort(a + 2, a + 1 + n, [](node x, node y)
		{
			return (x - a[1]).get() < (y - a[1]).get();
		});
	b[m = 1] = 1;
	for (int i = 2; i <= n; ++i)
	{
		while (m > 1 && (a[b[m - 1]] - a[b[m]]) * (a[i] - a[b[m]]) >= 0)
			--m;
		b[++m] = i;
	}
	while (m > 1 && (a[b[m - 1]] - a[b[m]]) * (a[1] - a[b[m]]) >= 0)
		--m;
	int cnt = 1;
	for (int i = 1; i <= m; ++i)
		vis[b[i]] = true;
	for (int i = 1; i <= n; ++i)
	{
		if (vis[i])
			continue;
		q = 0;
		for (int j = 1; j <= n; ++j)
		{
			if (vis[j] || i == j)
				continue;
			c[++q] = j;
		}
		for (int j = 1; j <= n; ++j)
			d[j] = (a[j] - a[i]).get();
		sort(b + 1, b + 1 + m, [&](int x, int y)
			{
				return d[x] < d[y];
			});
		sort(c + 1, c + 1 + q, [&](int x, int y)
			{
				return d[x] < d[y];
			});
		for (int j = 1, l = 1, r = 1; j < m; ++j)
		{
			while (l <= q && d[c[l]] <= d[b[j]])
				++l;
			while (r <= q && d[c[r]] < d[b[j + 1]])
				++r;	
			if (l < r)
			{
				bool flag = true;
				ll area = abs((a[b[j]] - a[i]) * (a[b[j + 1]] - a[i]));
				for (int k = l; k <= r; ++k)
				{
					ll x = abs((a[c[k]] - a[i]) * (a[c[k]] - a[b[j]]));
					ll y = abs((a[c[k]] - a[i]) * (a[c[k]] - a[b[j + 1]]));
					ll z = abs((a[c[k]] - a[b[j]]) * (a[c[k]] - a[b[j + 1]]));
					if (x + y + z == area && x && y)
					{
						flag = false;
						break;
					}
				}
				cnt += flag;
			}
			else
				++cnt;
		}
		bool flag = true;
		ll area = abs((a[b[m]] - a[i]) * (a[b[1]] - a[i]));
		for (int k = 1; k <= q; ++k)
		{
			if (d[c[k]] > d[b[m]]
				|| d[c[k]] < d[b[1]])
			{
				ll x = abs((a[c[k]] - a[i]) * (a[c[k]] - a[b[m]]));
				ll y = abs((a[c[k]] - a[i]) * (a[c[k]] - a[b[1]]));
				ll z = abs((a[c[k]] - a[b[m]]) * (a[c[k]] - a[b[1]]));
				if (x + y + z == area && x && y)
				{
					flag = false;
					break;
				}
			}
		}
		cnt += flag;
	}
	cout << cnt << '\n';
	return 0;
}