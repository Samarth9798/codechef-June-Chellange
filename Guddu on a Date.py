T = int(input())
while T:
    N = int(input())
    print(N,end="")
    N = list(str(N))
    s = 0
    for i in N:
        s = s + int(i)
    if s%10 == 0:
        print(0)
    else:
        print(int(10-s%10))
    T-=1
