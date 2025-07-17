#include <bits/stdc++.h>
using namespace std;
constexpr int N = 1024 + 5;
constexpr int mod = 998244353;
int n;
struct node
{
	int pop, popgoto;
	int push, pushgoto;
} a[N];
bool exist[N];
bool vis[N][N];
int sum[N], nxt[N];
inline void dfs(int u)
{
	if (exist[u])
		return;
	exist[u] = true;
	sum[u] = 1;
	vis[u][u] = true;
	int v = a[u].pushgoto;
	while (1)
	{
		if (a[v].pop == a[u].push)
		{
			sum[u] = (sum[u] + 1) % mod;
			nxt[u] = a[v].popgoto;
			break;
		}
		if (vis[u][v])
		{
			cout << -1 << '\n';
			exit(0);
		}
		vis[u][v] = true;
		dfs(v);
		(sum[u] += sum[v]) %= mod;
		v = nxt[v];
	}
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	a[0].pushgoto = 1;
	cin >> n;
	for (int i = 1; i <= n; ++i)
	{
		string s;
		int x;
		cin >> s;
		if (s == "HALT;")
		{
			cin >> s;
			cin >> x;
			a[i].push = x;
			cin >> s;
			cin >> x;
			a[i].pushgoto = x;
		}
		else
		{
			cin >> x;
			a[i].pop = x;
			cin >> s;
			cin >> x;
			a[i].popgoto = x;
			cin >> s;
			cin >> s;
			cin >> x;
			a[i].push = x;
			cin >> s;
			cin >> x;
			a[i].pushgoto = x;
		}
	}
	dfs(0);
	cout << (sum[0] + mod - 1) % mod << '\n';
	return 0;
}