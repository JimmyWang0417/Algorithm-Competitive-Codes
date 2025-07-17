//#define __AVX__ 1
//#define __AVX2__ 1
//#pragma GCC optimize("Ofast, unroll-loops")
//#pragma GCC target("avx2, bmi, fma, popcnt")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr int N = 20005;
constexpr int M = 1e6 + 5;
constexpr int mod = 998244353;
template <typename T>
inline void add(T &x, T y)
{
	x += y;
	if (x >= mod)
		x -= mod;
}
template <typename T>
inline void del(T &x, T y)
{
	x -= y;
	if (x < 0)
		x += mod;
}
int n, m;
pair<int, int> edge[N + M];
int fa[N], sze[N];
int dp[N], sum;
inline void insert(int v)
{
	v = abs(v);
	if (!v)
		return;
	sum += v;
	for (int i = sum; i >= v; --i)
		add(dp[i], dp[i - v]);
}
inline void erase(int v)
{
	v = abs(v);
	if (!v)
		return;
	for (int i = v; i <= sum; ++i)
		del(dp[i], dp[i - v]);
	sum -= v;
}
inline int find(int x)
{
	return !fa[x] ? x : fa[x] = find(fa[x]);
}
inline void merge(int x, int y)
{
	sze[fa[x] = y] += sze[x];
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n >> m;
	n *= 2;
	for (int i = 1; i <= n; ++i)
		sze[i] = 1;
	for (int i = n + 1; i <= 2 * n; ++i)
		sze[i] = -1;
	for (int i = 1; i <= m; ++i)
		cin >> edge[m - i + 1].first >> edge[m - i + 1].second;
	for (int i = 1; i <= n; ++i)
	{
		edge[m + i].first = 1;
		edge[m + i].second = i;
	}
	m += n;
	dp[0] = 1;
	for (int i = 1; i <= n; ++i)
		insert(sze[i]);
	for (int i = 1; i <= m; ++i)
	{
		int u = edge[i].first, v = edge[i].second;
		if (find(u) == find(v))
			continue;
		if (find(u) == find(v + n))
			continue;
		erase(sze[find(u)]), erase(sze[find(v)]);
		insert(sze[find(u)] - sze[find(v)]);
		if (dp[sum / 2])
		{
			merge(find(u), find(v + n));
			merge(find(v), find(u + n));
		}
		else
		{
			erase(sze[find(u)] - sze[find(v)]);
			insert(sze[find(u)] + sze[find(v)]);
			merge(find(u), find(v));
			merge(find(u + n), find(v + n));
		}
	}
	for (int i = 1; i <= n; ++i)
		cout << (find(1) == find(i));
	cout << '\n';
	return 0;
} 