#include <bits/stdc++.h>
#include <ext/pb_ds/priority_queue.hpp>
using namespace std;
constexpr int N = 5e5 + 5;
typedef long long ll;
struct node
{
	ll sum1, sum2;
	__gnu_pbds::priority_queue<int> p, q;
	__gnu_pbds::priority_queue<int, greater<int>> x, y;
	inline int firsttop()
	{
		while (!q.empty() && p.top() == q.top())
		{
			p.pop();
			q.pop();
		}
		return p.top();
	}
	inline int firstsize()
	{
		return (int)(p.size() - q.size());
	}
	inline void firstpush(int v)
	{
		sum1 += v;
		p.push(v);
	}
	inline void firstpop(int v)
	{
		sum1 -= v;
		q.push(v);
	}
	inline int secondtop()
	{
		while (!y.empty() && x.top() == y.top())
		{
			x.pop();
			y.pop();
		}
		return x.top();
	}
	inline int secondsize()
	{
		return (int)(x.size() - y.size());
	}
	inline void secondpush(int v)
	{
		sum2 += v;
		x.push(v);
	}
	inline void secondpop(int v)
	{
		sum2 -= v;
		y.push(v);
	}
	inline int size()
	{
		return firstsize() + secondsize();
	}
	inline void update()
	{
		while (firstsize() > (size() + 1) / 2)
		{
			secondpush(firsttop());
			firstpop(firsttop());
		}
		while (firstsize() < (size() + 1) / 2)
		{
			firstpush(secondtop());
			secondpop(secondtop());
		}
	}
	inline void push(int v)
	{
		if (!firstsize() || v <= firsttop())
			firstpush(v);
		else
			secondpush(v);
		update();
	}
	inline void pop(int v)
	{
		if (firstsize() && v <= firsttop())
			firstpop(v);
		else
			secondpop(v);
		update();
	}
	inline ll calc()
	{
		int mid = firsttop();
		return ((ll)mid * firstsize() - sum1) + (sum2 - (ll)mid * secondsize());
	}
};
ll m;
int n, a[N];
inline void work()
{
	cin >> n >> m;
	node q;
	q.sum1 = q.sum2 = 0;
	int res = 0;
	for (int i = 1, j = 1; i <= n; ++i)
	{
		cin >> a[i];
		a[i] -= i;
		q.push(a[i]);
		while (q.calc() > m)
			q.pop(a[j++]);
		res = max(res, i - j + 1);
	}
	cout << res << '\n';
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