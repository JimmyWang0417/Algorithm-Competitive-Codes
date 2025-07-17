#include <bits/stdc++.h>
using namespace std;
constexpr int N = 105;
int n, a[N];
inline void work()
{
	cin >> n;
	for (int i = 1; i <= n; ++i)
		cin >> a[i];
	vector<pair<int, int>> answer;
	for (int i = 1; i <= n; ++i)
	{
		if (a[i] == i)
			continue;
		for (int j = n; j >= 1; --j)
			if (a[i] > a[j])
			{
				sort(a + i, a + j + 1);
				answer.emplace_back(i, j);
				break;
			}
	}
	cout << answer.size() << '\n';
	for (auto [l, r] : answer)
		cout << l << ' ' << r << '\n';
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int T;
	cin >> T;
	while (T--)
		work();
	return 0;
}