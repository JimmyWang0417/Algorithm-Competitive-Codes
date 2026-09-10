auto spfa()
{
    fill(dis.begin(), dis.end(), 0);
    fill(pre.begin(), pre.end(), 0);
    fill(cnt.begin(), cnt.end(), 0);
    fill(exist.begin(), exist.end(), true);
    queue<int> que;
    for (int i = 1; i <= n; ++i)
        que.push(i);
    while (!que.empty())
    {
        int u = que.front();
        que.pop(), exist[u] = false;
        for (int i = head[u]; i; i = edge[i].next)
        {
            int v = edge[i].to;
            if (edge[i].cap && dis[v] > dis[u] + edge[i].cost)
            {
                dis[v] = dis[u] + edge[i].cost;
                pre[v] = i;
                cnt[v] = cnt[u] + 1;
                if (cnt[v] >= n)
                    return v;
                if (!exist[v])
                    que.push(v), exist[v] = true;
            }
        }
    }
    return -1;
}
