#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
constexpr int N = 2e5 + 5;
constexpr int base = 1e6 + 33;
constexpr int mod = 998244353;
template <typename T>
inline void add(T &x, T y)
{
	x += y;
	if (x >= mod)
		x -= mod;
}
int n, a[N];
pair<int, int> p[N];
int c[N];
#define lowbit(x) ((x) & (-(x)))
inline void update(int pos, int val)
{
	for (int i = pos; i <= n; i += lowbit(i))
		add(c[i], val);
}
inline void clear(int pos)
{
	for (int i = max(pos, 1); i <= n && c[i]; i += lowbit(i))
		c[i] = 0;
}
inline int query(int pos)
{
	int res = 0;
	for (int i = pos; i >= 1; i -= lowbit(i))
		add(res, c[i]);
	return res;
}
inline void cdq(int *dp, int l, int r)
{
	if (l == r)
		return;
	int mid = (l + r) >> 1;
	cdq(dp, l, mid);
	for (int i = mid, j = 1; i >= l; --i)
	{
		p[i] = make_pair(i, i + j);
		j = max(j, a[i]);
	}
	for (int i = mid + 1, j = 1; i <= r; ++i)
	{
		j = max(j, a[i]);
		p[i] = make_pair(i - j, i);
	}
	sort(p + l, p + mid + 1);
	sort(p + mid + 1, p + r + 1);
	for (int i = mid + 1, j = l; i <= r; ++i)
	{
		while (j <= mid && p[j].first <= p[i].first)
		{
			update(p[j].second, dp[p[j].first]);
			++j;
		}
		add(dp[p[i].second], query(p[i].second));
	}
	for (int i = l; i <= mid; ++i)
		clear(p[i].second);
	cdq(dp, mid + 1, r);
}
int f[N], g[N];
ll dp[N], pre[N], mp[N];
vector<tuple<int, int, int>> q;
inline void solve(int l, int r)
{
	if (l == r)
		return;
	int mid = (l + r) >> 1;
	solve(l, mid), solve(mid + 1, r);
	for (int i = mid, j = 1; i >= l; --i)
	{
		p[i] = make_pair(i, i + j);
		j = max(j, a[i]);
	}
	for (int i = mid + 1, mx = 1, nx = 1, pos = mid + 1; i < r; ++i)
	{
		if (a[i] > mx)
		{
			nx = mx;
			mx = a[i];
			pos = i;
		}
		else
			nx = max(nx, a[i]);
		q.emplace_back(i - mx, i, pos);
		q.emplace_back(i - nx, i, -pos);
	}
	sort(p + l, p + mid + 1);
	sort(q.begin(), q.end());
	for (int i = 0, j = l; i < (int)q.size(); ++i)
	{
		while (j <= mid && p[j].first <= get<0>(q[i]))
		{
			update(p[j].second, f[p[j].first]);
			++j;
		}
		if (get<2>(q[i]) > 0)
		{
			ll now = (ll)query(get<1>(q[i])) * g[get<1>(q[i]) + 1] % mod;
			(pre[get<1>(q[i])] += now) %= mod;
			(mp[get<2>(q[i])] += mod - now) %= mod;
		}
		else
		{
			ll now = (ll)query(get<1>(q[i])) * g[get<1>(q[i]) + 1] % mod;
			(mp[-get<2>(q[i])] += now) %= mod;
		}
	}
	for (int i = r - 1; i >= mid + 1; --i)
		(pre[i] += pre[i + 1]) %= mod;
	q.clear();
	for (int i = l; i <= mid; ++i)
		clear(p[i].second);
	
	for (int i = mid + 1, j = 1; i <= r; ++i)
	{
		p[i] = make_pair(n + 1 - i, n + 1 - i + j);
//		printf("%d %d %d\n", i, n + 1 - i, n + 1 - i + j);
		j = max(j, a[i]);
	}
	for (int i = mid, mx = 1, nx = 1, pos = mid; i > l; --i)
	{
		if (a[i] > mx)
		{
			nx = mx;
			mx = a[i];
			pos = i;
		}
		else
			nx = max(nx, a[i]);
		q.emplace_back(n + 1 - i - mx, n + 1 - i, pos);
		q.emplace_back(n + 1 - i - nx, n + 1 - i, -pos);
	}
	sort(p + mid + 1, p + r + 1);
	sort(q.begin(), q.end());
	for (int i = 0, j = mid + 1; i < (int)q.size(); ++i)
	{
		while (j <= r && p[j].first <= get<0>(q[i]))
		{
			update(p[j].second, g[n + 1 - p[j].first]);
			++j;
		}
		if (get<2>(q[i]) > 0)
		{
			ll now = (ll)query(get<1>(q[i])) * f[(n + 1) - (get<1>(q[i]) + 1)] % mod;
			(pre[n + 1 - get<1>(q[i])] += now) %= mod;
			(mp[get<2>(q[i])] += mod - now) %= mod;
//			printf("%d %d %d %d %d\n", l, r, get<2>(q[i]), n + 1 - get<1>(q[i]), now);
		}
		else
		{
			ll now = (ll)query(get<1>(q[i])) * f[(n + 1) - (get<1>(q[i]) + 1)] % mod;
			(mp[-get<2>(q[i])] += now) %= mod;
//			printf(" %d %d %d %d %d\n", l, r, get<2>(q[i]), n + 1 - get<1>(q[i]), now);
		}
	}
	for (int i = l + 1; i <= mid; ++i)
		(pre[i] += pre[i - 1]) %= mod;
	q.clear();
	for (int i = mid + 1; i <= r; ++i)
		clear(p[i].second);
	
	for (int i = l; i <= r; ++i)
	{
//		printf("%d %lld %lld\n", i, pre[i], mp[i]);
		(dp[i] += pre[i] + mp[i]) %= mod;
		pre[i] = mp[i] = 0;
	}
//	printf(" %d %d %lld\n", l, r, dp[1]);
}
inline void work()
{
	cin >> n;
	for (int i = 1; i <= n; ++i)
		cin >> a[i];
	f[0] = 1;
	cdq(f, 0, n);
	reverse(a + 1, a + 1 + n);
	g[0] = 1;
	cdq(g, 0, n);
	reverse(g, g + n + 2);
	reverse(a + 1, a + 1 + n);
//	for (int i = 0; i <= n + 1; ++i)
//		cout << f[i] << ' ';
//	cout << '\n';
//	for (int i = 0; i <= n + 1; ++i)
//		cout << g[i] << ' ';
//	cout << '\n';
	solve(0, n + 1);
	for (int i = 1; i <= n; ++i)
		cout << dp[i] << ' ';
	cout << '\n';
	for (int i = 0; i <= n + 1; ++i)
		f[i] = g[i] = 0;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int test = 1;
//	cin >> test;
	while (test --)
		work();
	return 0;
}