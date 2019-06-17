#include<bits/stdc++.h>
using namespace std;
#define fast ios::sync_with_stdio(0), cout.tie(0), cin.tie(0);
typedef long long int ll;

int max_one;

void find(int one, int zero, int k, int n)
{
    if(zero%k == 0 or k == 1 or zero == 0)
    {
        max_one = n;
        return;
    }
    
    if(one >= 2)
    {
        find(one-2,zero+2,k,n);
    }
}

int main()
{
    fast
    
    int T;
    
    cin >> T;
    
    while(T--)
    {
        int N;
        
        cin >> N;
        
        ll a[N+1];
        
        ll sum = 0;
        
        for(int i = 0; i < N; i++)
        {
            cin >> a[i];
            sum += a[i];
        }
        
        int K;
        ll X;
        cin >> K;
        cin >> X;
        
        if(X == 0)
        {
            cout << sum << endl;
            continue;
        }
        
        int zero,one;
        one = zero = 0;
        vector<ll> small,large;
        
        for(int i = 0; i < N; i++)
        {
            if((a[i]^X) >= a[i])
            {
                large.push_back(a[i]);
                zero++;
            }
            else
            {
                small.push_back(a[i]);
                one++;
            }
        }
    
        if(K == N)
        {
            ll sum1,sum2;
            sum1 = sum2 = 0;
            for(int i = 0; i < large.size(); i++)
            {
                sum1 = sum1 + (large[i]^X);
                sum2 = sum2 + large[i];
            }
            for(int i = 0; i < small.size(); i++)
            {
                sum1 = sum1 + (small[i]^X);
                sum2 = sum2 + small[i];
            }
            
            cout << max(sum1,sum2) << endl;
            continue;
        }

        max_one = N-1;
        zero = zero%2;
        one = N-1;
        
        find(one,zero,K,N);

        if(max_one == N)
        {
            ll ans = 0;
            for(int i = 0; i < large.size(); i++)
            {
                ans = ans + (large[i]^X);
            }
            for(int i = 0; i < small.size(); i++)
            {
                ans = ans + (small[i]);
            }
            cout << ans << endl;
            continue;
        }
        
        ll temp = 0,ans = 0;
        sum = 0;
        vector<ll> v;
        for(int i = 0; i < large.size(); i++)
        {
            v.push_back((large[i]^X));
            sum = sum + (large[i]^X);
        }
        for(int i = 0; i < small.size(); i++)
        {
            v.push_back(small[i]);
            sum = sum + small[i];
        }
        for(int i = 0; i < v.size(); i++)
        {
            temp = sum - v[i];
            temp = temp + (v[i]^X);
            if(temp > ans)
                ans = temp;
        }
        cout << ans << endl;
    }
}
