T = int(input())
for _ in range(T):
    a = list(map(int, input().split('.')))
    b = list(map(int, input().split('.')))
    if a < b:
        print("B")
    elif a > b:
        print("A")
    else:
        print("Equal")
