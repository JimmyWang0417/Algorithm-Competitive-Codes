#include <bits/stdc++.h>
#define int ll
using namespace std;
typedef long long ll;
template <typename T>
inline void ckmax(T &x, T y)
{
	if (x < y)
		x = y;
}
template <typename T>
inline void ckmin(T &x, T y)
{
	if (x > y)
		x = y;
}
constexpr int N = 1e6 + 5;
int n;
auto cross = [](pair<int, int> x, pair<int, int> y, pair<int, int> z)
{
	return (ll)(x.first - y.first) * (z.second - y.second)
		  -(ll)(z.first - y.first) * (x.second - y.second);
};
inline vector<pair<int, int>> build()
{
	vector<pair<int, int>> g;
	for (int i = 0; i <= n; ++i)
	{
		int x;
		cin >> x;
		while (g.size() > 1 && cross(g[g.size() - 2], g.back(), {i, x}) <= 0)	
			g.pop_back();
		g.emplace_back(i, x);
	}
	return g;
}
inline vector<pair<int, int>> merge(vector<pair<int, int>> a, vector<pair<int, int>> b)
{
	vector<pair<int, int>> g;
	for (int i = 0, j = 0; i < (int)a.size() && j < (int)b.size(); )
	{
		pair<int, int> now = make_pair(a[i].first + b[j].first, a[i].second + b[j].second);
        while (g.size() > 1 && cross(g[g.size() - 2], g.back(), now) <= 0)
			g.pop_back();
        g.push_back(now);
        if (i + 1 == (int)a.size())
        	++j;
        else if (j + 1 == (int)b.size())
        	++i;
        else
        {
        	ll d = (a[i + 1].second - a[i].second) * (b[j].first - b[j + 1].first)
        		  -(b[j + 1].second - b[j].second) * (a[i].first - a[i + 1].first);
        	if (d >= 0)
        		++j;
        	if (d <= 0)
        		++i;
		}
	}
	return g;
}
int answer[N], answertot;
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n;
	auto hull = merge(build(), merge(build(), build()));
	for (int i = 0, j = 0; i <= n * 3; ++i)
	{
        if (j < (int)hull.size() && i == hull[j].first) 
		{
			++j;
			continue;
        }
        answer[++answertot] = i;
	}
	cout << answertot << '\n';
	for (int i = 1; i <= answertot; ++i)
		cout << answer[i] << ' ';
	cout << '\n';
	return 0;
}