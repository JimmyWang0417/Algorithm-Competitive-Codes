#include <bits/stdc++.h>
using namespace std;
constexpr int N = 3e5 + 5;
int n, m;
char A[N], B[N];
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n >> m >> A >> B;
	int cnt = 0;
	for (int i = 0; i < n; ++i)
		cnt += (A[i] == 'B');
	
	deque<char> a, b;
	for (int i = 0; i < m; ++i)
		a.push_back(A[i]);
	for (int i = n - m; i < n; ++i)
		b.push_back(B[i]);
	b.push_back(B[0]);
	
	vector<pair<int, int>> answer;
	
	if (cnt <= n / 2)
	{
		for (int i = m - 1, j = 0; cnt--;)
		{
			while (a.front() != 'B')
			{
				A[(i - a.size() + 1 + n) % n] = a.front();
				a.pop_front();
				a.push_back(A[i = (i + 1) % n]);
			}
			while (b.back() != 'C')
			{
				B[(j - b.size() + 1 + n) % n] = b.front();
				b.pop_front();
				b.push_back(B[j = (j + 1) % n]);
			}
			answer.emplace_back((i - m + 1 + n) % n, (j - m + n) % n);
			answer.emplace_back((i - m + 1 + n) % n, (j - m + 1 + n) % n);
			a.pop_front(), b.pop_back();
			a.push_back('C'), b.push_front('B');
		}
	}
	else
	{
		cnt = n - cnt;
		for (int i = m - 1, j = 0; cnt--;)
		{
			while (a.front() != 'C')
			{
				A[(i - a.size() + 1 + n) % n] = a.front();
				a.pop_front();
				a.push_back(A[i = (i + 1) % n]);
			}
			while (b.back() != 'B')
			{
				B[(j - b.size() + 1 + n) % n] = b.front();
				b.pop_front();
				b.push_back(B[j = (j + 1) % n]);
			}
			answer.emplace_back((i - m + 1 + n) % n, (j - m + n) % n);
			answer.emplace_back((i - m + 1 + n) % n, (j - m + 1 + n) % n);
			a.pop_front(), b.pop_back();
			a.push_back('B'), b.push_front('C');
		}
	}
	cout << answer.size() << '\n';
	for (auto [u, v] : answer)
		cout << u + 1 << ' ' << v + 1 << '\n';
	return 0;
}