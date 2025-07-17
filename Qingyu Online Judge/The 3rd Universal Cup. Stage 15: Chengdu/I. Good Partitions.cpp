#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
typedef long long ll;
constexpr int N = 2e5 + 5;
int n, m, a[N];
int tree[N * 4];
#define lc (rt << 1)
#define rc (rt << 1 | 1)
inline void pushup(int rt)
{
	tree[rt] = __gcd(tree[lc], tree[rc]);
}
inline void build(int rt, int l, int r)
{
	tree[rt] = 0;
	if (l == r)
		return;
	int mid = (l + r) >> 1;
	build(lc, l, mid);
	build(rc, mid + 1, r);
}
inline void update(int rt, int l, int r, int pos, int val)
{
	if (l == r)
	{
		tree[rt] = val;
		return;
	}
	int mid = (l + r) >> 1;
	if (pos <= mid)
		update(lc, l, mid, pos, val);
	else
		update(rc, mid + 1, r, pos, val);
	pushup(rt);
}
inline int query(int rt, int l, int r, int pos)
{
	if (l == r)
		return tree[rt];
	int mid = (l + r) >> 1;
	if (pos <= mid)
		return query(lc, l, mid, pos);
	else
		return __gcd(tree[lc], query(rc, mid + 1, r, pos));
}
vector<int> g[N];
inline void update(int pos, int val)
{
	if (pos == 0 || pos == n + 1)
		return;
	update(1, 1, n, pos, val);
}
pair<int, int> p[N];
set<pair<int, int>> se;
inline void update()
{
		int pos, val;
		cin >> pos >> val;
		auto it = --se.upper_bound(make_pair(pos, 2e9));
		auto L = *prev(it), R = *next(it);
		auto u = *it;
		se.erase(L), se.erase(u), se.erase(R);
		update(L.first, 0);
		update(u.first, 0);
		update(R.first, 0);
		a[pos] = val;
		int tot = 0;
		p[++tot] = L;
		if (u.first < pos)
			p[++tot] = make_pair(u.first, pos - 1);
		p[++tot] = make_pair(pos, pos);
		if (pos < u.second)
			p[++tot] = make_pair(pos + 1, u.second);
		p[++tot] = R;
		int qwq = 1;
		for (int j = 2; j <= tot; ++j)
		{
			if (a[p[qwq].second] <= a[p[j].first])
				p[qwq].second = p[j].second;
			else
				p[++qwq] = p[j];
		}
		for (int j = 1; j <= qwq; ++j)
		{
			se.insert(p[j]);
			update(p[j].first, p[j].second - p[j].first + 1);
		}
}
inline void query()
{
	auto it = --(--se.end());
	if (it -> first == 1)
		cout << n << '\n';
	else
	{
		int gcd = query(1, 1, n, it -> first - 1), 
			len = (it -> second - it -> first + 1);
		int res = 0;
		for (int i : g[gcd])
			if (len >= n % i)
				++res;
		cout << res << '\n';
	}
}
inline void work()
{
	cin >> n >> m;
	for (int i = 1; i <= n; ++i)
		cin >> a[i];
	build(1, 1, n);
	for (int l = 1, r = 1; l <= n; l = r)
	{
		r = l + 1;
		while (r <= n && a[r] >= a[r - 1])
			++r;
		se.emplace(l, r - 1);
		update(l, r - l);
	}
	a[0] = 2e9 + 1, a[n + 1] = -2e9 - 1;
	se.emplace(0, 0);
	se.emplace(n + 1, n + 1);
	query(); 
	for (int i = 1; i <= m; ++i)
	{
		update();
		query();
	}
	se.clear();
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	for (int i = 1; i <= 2e5; ++i)
		for (int j = i; j <= 2e5; j += i)
			g[j].push_back(i);
	int T;
	cin >> T;
	while (T--)
		work();
	return 0;
} 