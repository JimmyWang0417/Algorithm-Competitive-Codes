for (int u = 1; u <= n; u++)
    for (auto &[v, w] : e[u])
        w += dis[u] - dis[v];