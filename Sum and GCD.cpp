#include<bits/stdc++.h>
using namespace std;
#define fast ios::sync_with_stdio(0), cout.tie(0), cin.tie(0);
typedef long long int ll;
#define endl '\n'

int main()
{
    fast
    
    int T;
    cin >> T;
    
    while(T--)
    {
        int N;
        
        cin >> N;
        
        ll A[N+5];
        
        for(int i = 0; i < N; i++)
            cin >> A[i];
            
        sort(A,A+N);
            
        ll Precomputed_gcds[N+5];
        ll hcf = 0;
    
        for(int i = N-1; i >= 0; i--)
        {
            hcf = __gcd(hcf, A[i]);
            Precomputed_gcds[i] = hcf;
        }
        
        hcf = 0;
        ll ans1 = 0;
        
        for(int i = 0; i < N-1; i++)
        {
            hcf = __gcd(hcf, A[i]);
            if(hcf + Precomputed_gcds[i+1] > ans1)
                ans1 = hcf + Precomputed_gcds[i+1];
        }
        
        hcf = 0;
        set<ll> s;
        
        for(int i = 0; i < N; i++)
        {
            s.insert(A[i]);
        }
        
        ll ans2 = 0;
        if(s.size() > 2)
        {
            vector<ll> v;
            for(auto it = s.begin(); it != s.end(); it++)
            {
                v.push_back(*it);
            }
            
            for(int i = 0; i < v.size(); i++)
            {
                if(i != v.size()-2)
                {
                    hcf = __gcd(hcf, v[i]);
                }
            }
            
            ans2 = hcf + v[v.size()-2];
        }
        
        cout << max(ans1,ans2) << endl;
    }
}
