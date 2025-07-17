#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr int N = 3e5 + 5;
constexpr ll hashmod = 106433706259420361;
constexpr int mod = 1e9 + 7;
int n, a[N];
int dp[N];
ll power[N * 10];
int dight[N];
ll hsh[N];
inline void solve(int l, int r)
{
	if (l == r)
	{
		(dp[r] += dp[l - 1]) %= mod;
		return;
	}
	int mid = (l + r) >> 1;
	solve(l, mid);
	unordered_set<int> mp;
	for (int i = mid, j = 0; i >= l; --i)
	{
		int x = a[i];
		while (mp.count(x))
			mp.erase(x++);
		mp.insert(x);
		j = max(j, x);
		dight[i] = j;
		hsh[i] = (i == mid ? power[a[i]] : (hsh[i + 1] + power[a[i]]) % hashmod);
	}
	mp.clear();
	for (int i = mid + 1, j = 0; i <= r; ++i)
	{
		int x = a[i];
		while (mp.count(x))
			mp.erase(x++);
		mp.insert(x);
		j = max(j, x);
		dight[i] = j;
		hsh[i] = (i == mid + 1 ? power[a[i]] : (hsh[i - 1] + power[a[i]]) % hashmod);
	}
	unordered_map<ll, int> where;
	vector<pair<int, int>> p;
	for (int i = mid + 1, j = mid; i <= r; ++i)
	{
		while (j >= l && dight[j] <= dight[i])
		{
			where[hsh[j]] = j;
			--j;
		}
		if (where[(power[dight[i] + 1] - hsh[i] + hashmod) % hashmod])
			p.emplace_back(where[(power[dight[i] + 1] - hsh[i] + hashmod) % hashmod], i);
	}
	where.clear();
	for (int i = mid, j = mid + 1; i >= l; --i)
	{
		while (j <= r && dight[j] < dight[i])
		{
			where[hsh[j]] = j;
			++j;
		}
		if (where[(power[dight[i] + 1] - hsh[i] + hashmod) % hashmod])
			p.emplace_back(i, where[(power[dight[i] + 1] - hsh[i] + hashmod) % hashmod]);
	}
	for (auto [i, j] : p)
		(dp[j] += dp[i - 1]) %= mod;
	solve(mid + 1, r);
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	power[0] = 1;
	for (int i = 1; i <= 1.5e6; ++i)
		power[i] = power[i - 1] * 2 % hashmod;
	cin >> n;
	for (int i = 1; i <= n; ++i)
		cin >> a[i];
	dp[0] = 1;
	solve(1, n);
	cout << dp[n] << '\n';
	return 0;
}