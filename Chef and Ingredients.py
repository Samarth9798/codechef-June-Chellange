T = int(input())

mod = 1000000007

while T:
    
    N,K = map(int,input().split())
    
    KK = N + K - 1
    
    ans = K-1
    
    last_term = (2*K - KK - 1)
    
    if last_term > 0:
        
        d = KK - K
        
        first_term = last_term % d 
        
        n = last_term//d + 1
        
        AP = n * (first_term + last_term)//2 
        
        ans = int(ans + AP)%mod
    
    print(int(ans)%mod)
    
    T-=1
