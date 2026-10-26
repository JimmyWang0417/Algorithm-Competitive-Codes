#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
constexpr int N = 4e5 + 5;
ull base, invbase;
int n, m;
int a[N], fa[N];
int st[N], top;
vector<int> g[N];
struct Query
{
	int l, r, id;
	auto operator<(const Query &rhs) const
	{
		return l < rhs.l;
	}
} b[N];
ull power[N], invpower[N];
ull c[N];
auto lowbit = [](int x)
{
	return x & (-x);
};
auto update(int pos, ull val)
{
	for (int i = pos; i <= n; i += lowbit(i))
		c[i] += val;
}
auto query(int pos)
{
	ull res = 0;
	for (int i = pos; i; i -= lowbit(i))
		res += c[i];
	return res;
}
auto query(int l, int r)
{
	return query(r) - query(l - 1);
}
ull p[N];
int tot;
auto inverse(ull x)
{
	ull res = 1;
	for (int i = 1; i <= 6; ++i)
		res *= 2 - x * res;
	return res;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n;
	auto rng = mt19937_64(chrono::system_clock::now().time_since_epoch().count());
	base = rng() | 1;
	invbase = inverse(base);
	power[0] = invpower[0] = 1;
	for (int i = 1; i <= n; ++i)
	{
		power[i] = power[i - 1] * base;
		invpower[i] = invpower[i - 1] * invbase;
	}
	for (int i = 1; i <= n; ++i)
		cin >> a[i];
	cin >> m;
	for (int i = 1; i <= m; ++i)
	{
		cin >> b[i].l >> b[i].r;
		b[i].id = i;
	}
	sort(b + 1, b + 1 + m);
	for (int i = 1; i <= n; ++i)
	{
		while (top && a[st[top]] > a[i])
			--top;
		g[fa[i] = st[top]].push_back(i);
		st[++top] = i;
	}
	g[0].clear();
	for (int i = 1; i <= n; ++i)
		if (fa[i])
			update(i, (i - fa[i]) * power[i]);
		else
			update(i, -1 * power[i]);
	for (int i = 1, j = 1; i <= n; ++i)
	{
		while (j <= m && b[j].l == i)
		{
			p[++tot] = query(b[j].l, b[j].r) * invpower[i - 1];
			++j;
		}
		for (int k : g[i])
			update(k, (fa[k] - k - 1) * power[k]);
	}
	sort(p + 1, p + 1 + tot);
	tot = (int)(unique(p + 1, p + 1 + tot) - p - 1);
	cout << tot << '\n';
	return 0;
}
