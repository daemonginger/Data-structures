#include<bits/stdc++.h>
 
#define ll long long
#define ld long double
#define pb push_back
#define mp make_pair
#define PI 3.14159265359
#define endl '\n'

using namespace std;

const ll M = 1e9 + 7;
const int MAX = 1e5,N = 26;
ll p[MAX],h[MAX],n;
string s;

inline ll geth(ll x,ll y)
{
	return (h[x+y] - (x > 0 ? h[x-1] : 0) + M)%M;
}

inline bool sort1(const int& x,const int& y)
{
	ll l = 0,r = min(n-x,n-y);
	while(r-l>1)
	{
		ll mid = (r+l)/2;
		if(geth(x,mid) == geth(y,mid))
			l = mid;
		else
			r = mid;
	}
	
	return s[x+l] < s[y+l];
}

vector<int> f()
{
	n = s.size();
	h[0] = s[0] - 'a';
	for(int i=1;i<n+1;i++)
		h[i] = (h[i-1] + (s[i] - 'a')*p[i])%M;
	
	vector<int> ans;
	for(int i=0;i<n;i++)
		ans.pb(i);
	
	s += (char)('a' - 1);
	sort(ans.begin(),ans.end(),sort1);
	return ans;
}

int main()
{
   ios_base::sync_with_stdio(0);
   
	p[0] = 1;
	for(int i=1;i<MAX;i++)
		p[i] = (p[i-1]*N)%M;
	
	vector<int> v = f();
	
   return 0;
}