#include<bits/stdc++.h>

#define ll long long
#define pb push_back
#define mp make_pair
#define PI 3.14159265359
#define endl '\n'

using namespace std;

const int MAX = 1e6,SMAX = 1e3,INF = 2*1e9+1;
int t[MAX],sq[SMAX];

void set_rmq(int id,int val)
{
	t[id] = val;
	int sid = id/SMAX;
	sq[sid] = min(sq[sid],val);
}

// r exclu.
int get_rmq(int l,int r)
{
	int ans = INF;
	for(int i=(l+SMAX-1)/SMAX;(i+1)*SMAX-1<r;i++)
		ans = min(ans,sq[i]);
	int lb = min((l/SMAX + 1)*SMAX,r);
	for(int i=l;i<lb;i++)
		ans = min(ans,t[i]);
	for(int i=max((r/SMAX)*SMAX,l);i<r;i++)
		ans = min(ans,t[i]);
	return ans;
}

int main()
{
	ios_base::sync_with_stdio(0);
	
	for(int i=0;i<MAX;i++)
		t[i] = INF;
	
	int n;
	cin >> n;
	for(int i=0;i<n;i++)
		cin >> t[i];
	
	for(int i=0;i<SMAX;i++)
	{
		int cur_min = INF;
		for(int j=0;j<SMAX;j++)
			cur_min = min(cur_min,t[SMAX*i+j]);
		sq[i] = cur_min;
	}
	
	return 0;
}