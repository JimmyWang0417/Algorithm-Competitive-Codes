#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
typedef long long ll;
constexpr int N = 1e5 + 5;
int n, m;
int a[N], b[N], c[N], d[N];
int mp[N];
inline void work()
{
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
	cin >> n >> m;
	for (int i = 1; i <= n; ++i)
		cin >> a[i];
	for (int i = 1; i <= m; ++i)
		cin >> b[i] >> c[i];
	for (int i = 1; i <= n; ++i)
		mp[i] = m + 1;
	for (int i = m; i >= 1; --i)
	{
		d[i] = mp[c[i]];
		mp[c[i]] = i;
	}
	for (int i = 1; i <= n; ++i)
		q.emplace(mp[i], a[i]);
	for (int i = 1; i <= m; ++i)
	{
		int res = b[i] - b[i - 1];
		while (res)
		{
			if (q.empty())
				break;
			auto u = q.top();
			q.pop();
			int v = min(res, u.second);
			res -= v;
			u.second -= v;
			if (u.second)
				q.push(u);
		}
		if (res)
		{
			cout << b[i] - res << '\n';
			return;
		}
		if (!q.empty() && q.top().first == i)
			q.pop();
		q.emplace(d[i], a[c[i]]);
	}
	ll res = b[m];
	while (!q.empty())
	{
		res += q.top().second;
		q.pop();
	}
	cout << res << '\n';
}
signed main()
{
//	freopen("project.in", "r", stdin);
//	freopen("project.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int T = 1;
	cin >> T;
	while (T--)
		work();
	return 0;
}