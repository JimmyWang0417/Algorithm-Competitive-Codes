def solve():
    s = input()
    n = int(s)
    m = len(s)

    for k in [m - 1, m]:
        if k == 0:
            continue
        for a in range(1, 10):
            x = int(str(a) * k)
            y = n - x
            if y <= 0:
                continue
            str_y = str(y)
            if min(str_y) != max(str_y):
                continue
            print(x, y)
            return


if __name__ == '__main__':
    T = int(input())
    for i in range(T):
        solve()
