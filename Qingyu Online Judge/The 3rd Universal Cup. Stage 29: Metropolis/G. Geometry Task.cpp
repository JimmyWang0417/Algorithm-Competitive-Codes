#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
constexpr int N = 1e6 + 5;
constexpr int mod = 998244353;
int n;
ll a[N], b[N], c[N];
int p[N], ptot;
int q[N], qtot;
int pre[N], suf[N];
inline bool check(ll mid)
{
	int all = 0;
	ptot = qtot = 0;
	for (int i = 1; i <= n; ++i)
	{
		if (a[i] < 0)
			p[++ptot] = (int)(upper_bound(c + 1, c + 1 + n, floor((long double)(mid - b[i]) / a[i])) - c - 1);
		else if (a[i] > 0)
			q[++qtot] = (int)(lower_bound(c + 1, c + 1 + n, ceil((long double)(mid - b[i]) / a[i])) - c);
		else
			all += (b[i] >= mid);
	}
	sort(p + 1, p + 1 + ptot);
	sort(q + 1, q + 1 + qtot);
	for (int i = 1, j = 1; i <= n; ++i)
	{
		while (j <= ptot && p[j] < i)
			++j;
		pre[i] = pre[i - 1];
		if (j <= ptot)
		{
			++pre[i];
			++j;
		}
	}
	for (int i = n, j = qtot; i >= 1; --i)
	{
		while (j >= 1 && q[j] > i)
			--j;
		suf[i] = suf[i + 1];
		if (j >= 1)
		{
			++suf[i];
			--j;
		}
	}
	int ans = all;
	for (int i = 0; i + all <= n; ++i)
		ans = max(ans, pre[i] + all + suf[i + all + 1]);
	for (int i = 0; i <= n + 1; ++i)
		pre[i] = suf[i] = 0;
	return ans >= (n + 1) / 2;
}
inline void _main()
{
	cin >> n;
	for (int i = 1; i <= n; ++i)
		cin >> a[i];
	for (int i = 1; i <= n; ++i)
		cin >> b[i];
	for (int i = 1; i <= n; ++i)
		cin >> c[i];
	sort(c + 1, c + 1 + n);
	ll l = -2e18, r = 2e18;
	while (l <= r)
	{
		ll mid = (l + r) >> 1;
		if (check(mid))
			l = mid + 1;
		else
			r = mid - 1;
	}
	cout << r << '\n';
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int test = 1;
	cin >> test;
	while (test--)
		_main();
	return 0;
}