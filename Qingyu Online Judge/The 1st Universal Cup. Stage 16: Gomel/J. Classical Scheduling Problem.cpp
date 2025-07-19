#include <bits/stdc++.h>
#include <ext/pb_ds/priority_queue.hpp>
using namespace std;
typedef long long ll;
constexpr int N = 2e5 + 5;
int n;
ll t;
struct node
{
	int a, b, id;
	inline bool operator<(const node &rhs) const
	{
		return b < rhs.b;
	}
} a[N];
ll suf[N];
inline bool check(int mid)
{
	priority_queue<int> q;
	ll res = 0;
	for (int i = n; i >= 1; --i)
	{
		int x = max(a[i].b - mid, 0);
		while (q.size() > x)
		{
			res -= q.top();
			q.pop();
		}
		suf[i] = (q.size() == x ? res : t + 1);
		q.push(a[i].a);
		res += a[i].a; 
	}
	while (!q.empty())
		q.pop();
	res = 0;
	for (int i = 1; i <= n; ++i)
	{
		q.push(a[i].a);
		res += a[i].a;
		while (q.size() > mid)
		{
			res -= q.top();
			q.pop();
		}
		if (q.size() == mid && res + suf[i] <= t)
			return true;
	}
	return false;
}
int p[N], tot;
inline void solve(int mid)
{
	priority_queue<int> q;
	ll res = 0;
	for (int i = n; i >= 1; --i)
	{
		int x = max(a[i].b - mid, 0);
		while (q.size() > x)
		{
			res -= q.top();
			q.pop();
		}
		suf[i] = (q.size() == x ? res : t + 1);
		q.push(a[i].a);
		res += a[i].a; 
	}
	while (!q.empty())
		q.pop();
	res = 0;
	for (int i = 1; i <= n; ++i)
	{
		q.push(a[i].a);
		res += a[i].a;
		while (q.size() > mid)
		{
			res -= q.top();
			q.pop();
		}
		if (q.size() == mid && res + suf[i] <= t)
		{
			int qwq = a[i].b - mid;
			sort(a + 1, a + 1 + i, [](node x, node y) { return x.a < y.a; });
			for (int j = 1; j <= mid; ++j)
				p[++tot] = a[j].id;
			sort(a + 1 + i, a + 1 + n, [](node x, node y) { return x.a < y.a; });
			for (int j = i + 1; j <= i + qwq; ++j)
				p[++tot] = a[j].id;
			return;
		}
	}
}
inline void work()
{
	cin >> n >> t;
	for (int i = 1; i <= n; ++i)
	{
		cin >> a[i].a >> a[i].b;
		a[i].id = i;
	}
	sort(a + 1, a + 1 + n);
	int l = 1, r = n;
	while (l <= r)
	{
		int mid = (l + r) >> 1;
		if (check(mid))
			l = mid + 1;
		else
			r = mid - 1;
	}
	solve(r);
	cout << r << '\n';
	cout << tot << '\n';
	for (int i = 1; i <= tot; ++i)
		cout << p[i] << ' ';
	cout << '\n';
	tot = 0;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int T = 1;
	cin >> T;
	while (T--)
		work();
	return 0;
}