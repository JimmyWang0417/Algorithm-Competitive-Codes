auto Floyd(const int &n)
{
    static int dis[MAXN + 1][MAXN + 1]; // 最短路矩阵
    static int pos[MAXN + 1][MAXN + 1];
    memcpy(dis, val, sizeof(val));
    memset(pos, 0, sizeof(pos));
    i64 ans = 0;
    for (int k = 1; k <= n; ++k)
    {
        for (int i = 1; i < k; ++i)
            for (int j = 1; j < i; ++j)
                if (ans > (i64)val[i][k] + val[k][j] + dis[i][j])
                { // 发现了更短的环
                    // 由于这里保证了 j<i<k，所以三个点不同，不会出现零环。
                    function<void(int, int)> get_path = [&](int u, int v)
                    { // 获得 u 到 v 之间的路径
                        if (pos[u][v] == 0)
                            return;

                        int k = pos[u][v];
                        get_path(u, k);
                        path[++cnt] = k;
                        get_path(k, v);
                    };
                    ans = val[i][k] + val[k][j] + dis[i][j], cnt = 0;
                    path[++cnt] = i, path[++cnt] = k,
                    path[++cnt] = j; // 依次加入 i,k,j 三点
                    get_path(j, i);  // 加入 j 到 i 的路径
                }

        for (int i = 1; i <= n; ++i) // 正常 Floyd 更新最短路
            for (int j = 1; j <= n; ++j)
            {
                if (dis[i][j] > dis[i][k] + dis[k][j])
                {
                    dis[i][j] = dis[i][k] + dis[k][j];
                    pos[i][j] = k; // 当前路径可以由 k 更新得到
                }
            }
    }
    return ans;
}