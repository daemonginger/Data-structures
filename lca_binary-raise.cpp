#include<bits/stdc++.h>

#define ll long long
#define pb push_back
#define mp make_pair
#define PI 3.14159265359
#define endl '\n'

using namespace std;

const int MAX = ...,LMAX = ...; // LMAX should be at least 31 - __builtin_clz(MAX+1)
int h[MAX],anc[MAX][LMAX];

// in this function, replace !x by "x is the root of the tree"
int f(int x) {return h[x] || !x ? h[x] : h[x] = f(anc[x][0])+1;}

int get_lca(int x,int y)
{
	if(h[x] < h[y])
		swap(x,y);
	
	for(int i=31-__builtin_clz(h[x]);i>=0;i--)
		if(h[x] - (1 << i) >= h[y])
			x = anc[x][i];
		
		if(x == y)
			return x;
		
		for(int i=31-__builtin_clz(h[x]);i>=0;i--)
			if(anc[x][i] != anc[y][i])
			{
				x = anc[x][i];
				y = anc[y][i];
			}
			
			// At this moment, x and y are the two sons of the LCA that lead to the vertices of the query.
			// It can be useful to get them in some problems.
			
			return anc[x][0];
}

int main()
{
	ios_base::sync_with_stdio(0);
	
	int n;
	cin >> n;
	// this code is one-based and 0 embodies the root. anc[i][0] is the father of i (ancestor of order 0).
	for(int i=1;i<=n;i++)
		scanf("%d",&anc[i][0]);
	
	for(int j=1;j<LMAX;j++)
		for(int i=1;i<=n;i++)
			anc[i][j] = anc[anc[i][j-1]][j-1];
		for(int i=1;i<=n;i++)
			f(i);
	
	return 0;
}