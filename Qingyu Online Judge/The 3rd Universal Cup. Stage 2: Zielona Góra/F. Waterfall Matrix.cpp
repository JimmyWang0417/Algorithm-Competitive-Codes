#include <bits/stdc++.h>
using namespace std;
constexpr int N = 2e5 + 5;
typedef long long ll;
int n;
int p[N], tot;
struct node
{
	int x, y, w;
	inline bool operator<(const node &rhs) const
	{
		return (x == rhs.x ? (y == rhs.y ? w < rhs.w : y < rhs.y) : x < rhs.x);
	}
} a[N], b[N];
int match[N];
inline ll solve(int l, int r, int ql, int qr)
{
	if (ql > qr)
		return 0;
	if (l == r)
	{
		ll res = 0;
		for (int i = ql; i <= qr; ++i)
			res += abs(a[i].w - p[l]);
		return res;
	}
	int mid = (l + r) >> 1;
	set<pair<int, int>> se;
	for (int i = ql; i <= qr; ++i)
	{
		if (a[i].w > p[mid])
		{
			auto it = se.upper_bound(make_pair(a[i].y, INT_MAX));
			if (it != se.begin())
			{
				--it;
				match[i] = it -> second;
				match[it -> second] = i;
				se.erase(it);
			}
		}
		else
			se.emplace(a[i].y, i);
	}
	int res = INT_MIN;
	int L = ql, R = qr;
	for (int i = qr; i >= ql; --i)
	{
		if (a[i].w > p[mid] && a[i].y > res)
		{
			if (!match[i] || a[match[i]].y <= res)
				res = a[i].y;
		}
		if (a[i].y <= res)
			b[R--] = a[i];
		else
			b[L++] = a[i];
	}
	reverse(b + ql, b + L);
	copy(b + ql, b + qr + 1, a + ql);
	for (int i = ql; i <= qr; ++i)
		match[i] = 0;
	return solve(l, mid, ql, R) + solve(mid + 1, r, L, qr);
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; ++i)
	{
		cin >> a[i].x >> a[i].y >> a[i].w;
		p[i] = a[i].w;
	}
	sort(p + 1, p + 1 + n);
	sort(a + 1, a + 1 + n);
	tot = (int)(unique(p + 1, p + 1 + n) - p - 1);
	cout << solve(1, tot, 1, n) << '\n';
	return 0;
}