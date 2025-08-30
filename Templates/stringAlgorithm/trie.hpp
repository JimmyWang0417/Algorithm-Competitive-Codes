namespace stringAlgorithm
{
    struct trie
    {
        vector<array<int, 26>> tree;
        vector<int> where;
        auto insert(const string &s)
        {
            auto newnode = [&]()
            {
                tree.emplace_back();
                return (int)tree.size() - 1;
            };
            int u = 0;
            for (int i = 0; i < (int)s.size(); ++i)
            {
                int c = s[i] - 'a';
                if (!tree[u][c])
                    tree[u][c] = newnode();
                u = tree[u][c];
            }
            return u;
        }
        auto match(const string &s)
        {
            int u = 0;
            for (int i = 0; i < (int)s.size(); ++i)
            {
                int c = s[i] - 'a';
                if (!tree[u][c])
                    return -1;
                u = tree[u][c];
            }
            return u;
        }
        trie() = default;
        trie(const vector<string> &s) : tree(1), where(s.size())
        {
            for (int i = 0; i < (int)s.size(); ++i)
                where[i] = insert(s[i]);
        }
    };
}