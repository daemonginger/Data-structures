#include<bits/stdc++.h>

#define ll long long
#define pb push_back
#define mp make_pair
#define PI 3.14159265359
#define endl '\n'

using namespace std;


struct ver
{
	int id,f,h,anc;
	vector<int> s;
	ver (){}
};

const int MAX = 1e6,SMAX = 1e3,INF = 2*1e9+1;
ver t[MAX+1];

void dfs(int x,int h,int anc)
{
	ver &v = t[x];
	v.h = h;
	v.anc = anc;
	int next_anc = (h+1)%SMAX ? anc : x;
	for(int y : v.s)
		dfs(y,h+1,next_anc);
}

int get_lca(int x,int y)
{	
	while(t[x].anc != t[y].anc)
		if(t[x].h > t[y].h)
			x = t[x].anc;
		else
			y = t[y].anc;
		
	while(x != y)
		if(t[x].h > t[y].h)
			x = t[x].f;
		else
			y = t[y].f;
	
	return x;
}

int main()
{
	ios_base::sync_with_stdio(0);
	
	int n;
	cin >> n;
	for(int i=0;i<n;i++)
		t[i].id = i;
	
	for(int i=0;i<n-1;i++)
	{
		int x,y;
		cin >> x >> y;
		t[y].f = x;
		t[x].s.pb(y);
	}
	
	t[1].f = 1;
	dfs(1,0,1);
	
	return 0;
}