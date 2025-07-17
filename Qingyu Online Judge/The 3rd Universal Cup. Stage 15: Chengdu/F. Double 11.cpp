#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
typedef long long ll;
typedef long double ld;
constexpr int N = 2e5 + 5;
constexpr auto eps = 1e-9;
int n, m, a[N];
ll sum[N];
ld f[N];
int g[N];
int head, tail, p[N], q[N];
inline auto solve(ld add)
{
	auto calc = [](int l, int r)
	{
		return sqrt((ld)(sum[r] - sum[l]) * (r - l)) + f[l];
	};
	head = 1, tail = 1;
	p[head] = q[head] = 0;
	for (int i = 1; i <= n; ++i)
	{
		while (head < tail && p[head + 1] <= i)
			++head;
		f[i] = calc(q[head], i) + add;
		g[i] = g[q[head]] + 1;
		while (head <= tail && calc(i, p[tail]) < calc(q[tail], p[tail]))
			--tail;
		if (head <= tail)
		{
			int l = p[tail], r = n, ans = -1;
			while (l <= r)
			{
				int mid = (l + r) >> 1;
				if (calc(i, mid) > calc(q[tail], mid) - eps)
					l = mid + 1;
				else
					r = mid - 1;
			}
			if (l == n + 1)
				continue;
			p[++tail] = l;
			q[tail] = i;
		}
		else
		{
			p[++tail] = i + 1;
			q[tail] = i;
		}
	}
	return make_pair(f[n], g[n]);
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; ++i)
		cin >> a[i];
	sort(a + 1, a + 1 + n);
	for (int i = 1; i <= n; ++i)
		sum[i] = sum[i - 1] + a[i];
	ld l = -1e9, r = 1e9;
	while (abs(r - l) > eps)
	{
		ld mid = (l + r) / 2;
		auto [res, cnt] = solve(mid);
		if (cnt >= m)
			l = mid;
		else
			r = mid;
	}
	auto [res, cnt] = solve(l);
	printf("%.10Lf\n", res - cnt * l);
	return 0;
} 