#include<bits/stdc++.h>

#define ll long long
#define pb push_back
#define mp make_pair
#define PI 3.14159265359
#define endl '\n'

using namespace std;

const int MAX = 1e6,LMAX = 21;
int t[MAX][LMAX],lg[MAX+1];

// r exclu.
int get_rmq(int l,int r)
{
	int k = lg[r-l];
	return min(t[l][k],t[r - (1 << k)][k]);
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
	for(int i=0;i<n;i++)
		cin >> t[i][0];
	
	for(int j=1;j<LMAX;j++)
		for(int i=0;i<MAX;i++)
		{
			int x = i + (1 << j);
			if(x < MAX)
				t[i][j] = min(t[i][j-1],t[i + (1 << (j-1))][j-1]);
		}
	
	return 0;
}