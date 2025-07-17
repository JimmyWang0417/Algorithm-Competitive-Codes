import sys

input = sys.stdin.readline

for _ in range(int(input())):
    A, B, C, X, Y, D = map(int, input().split())
    # 全用A
    ans = ((D + X - 1) // X) * A
    # 全用A, 如果有余数用B补齐
    if D > X and D % X:
        t = (D // X) * A
        if (D % X) <= (D // X) * Y:
            t += (D % X) * B
            if t < ans: ans = t
        else:
            # 多的用C补齐
            t += (D // X) * Y * B
            t += ((D % X) - (D // X) * Y) * C
            if t < ans: ans = t
    # 全用A 只用一个B, 剩下的用C补齐
    if D > X and D % X > Y:
        t = (D // X) * A + Y * B
        t += (D % X - Y ) * C
        if t < ans: ans = t
    # 用A凑齐剩下的用B
    if D > X:
        cnt = (D + X + Y - 1) // (X + Y)
        t = A * cnt
        if D - X * cnt > 0:
            t += B * (D - X * cnt)
        if t < ans: ans = t
    # A + B, 然后全用C
    if D > X:
        if D <= X + Y:
            t = A + B * (D - X)
            if t < ans: ans = t
        else:
            t = A + B * Y + (D - X - Y) * C
            if t < ans: ans = t
    # 不断重复 A + B
    cnt = D // (X + Y)
    t = cnt * (A + B * Y)
    if D % (X + Y):
        r = D % (X + Y)
        if r <= X:
            t += A
        else:
            t += A + (r - X) * B
    if t < ans: ans = t
    ## 不断重复A + B, 但是如果有余数用C补齐
    if D > X + Y:
        cnt = D // (X + Y)
        t = cnt * (A + B * Y)
        t += (D % (X + Y)) * C
        if t < ans: ans = t
    print(ans)