#include<bits/stdc++.h>

#define ll long long
#define pb push_back
#define mp make_pair
#define PI 3.14159265359
#define endl '\n'

using namespace std;

const int MAX = 1e6,LMAX = 21;

struct ver
{
	int id,f,h;
	vector<int> s;
	int anc[LMAX];
};

int lg[MAX+1];
ver t[MAX+1];

void dfs_h(int x,int h)
{
	ver &v = t[x];
	v.h = h;
	for(int y : v.s)
		dfs_h(y,h+1);
}

int get_lca(int x,int y)
{
	if(t[x].h < t[y].h)
		swap(x,y);
	
	int log = lg[t[x].h];
	
	for(int i=log;i>=0;i--)
		if(t[x].h - (1 << i) >= t[y].h)
			x = t[x].anc[i];
		
	if(x == y)
		return x;
	
	for(int i=log;i>=0;i--)
		if(t[x].anc[i] != t[y].anc[i])
		{
			x = t[x].anc[i];
			y = t[y].anc[y];
		}
	
	// At this moment, x and y are the two sons of the LCA that lead to the vertices of the query.
	// It can be useful to get them in some problems.
	
	return t[x].f;
}

int main()
{
	ios_base::sync_with_stdio(0);
	
	for(int i=0;i<=LMAX;i++)
		for(int j = 1 << i;j < 1 << (i+1);j++)
			if(j <= MAX)
				lg[j] = i;
	
	int n;
	cin >> n;
	
	for(int i=0;i<n-1;i++)
	{
		int x,y;
		cin >> x >> y;
		t[x].s.pb(y);
		t[y].f = x;
	}
	
	t[1].f = 1;
	for(int i=1;i<n+1;i++)
	{
		t[i].id = i;
		t[i].anc[0] = t[i].f;
	}
	for(int j=1;j<LMAX;j++)
		t[1].anc[j] = 1;
	
	for(int j=1;j<LMAX;j++)
		for(int i=2;i<n+1;i++)
			t[i].anc[j] = t[t[i].anc[j-1]].anc[j-1];
	
	dfs_h(1,0);
	
	return 0;
}