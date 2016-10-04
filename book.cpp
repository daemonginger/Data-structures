// Base code

#include<bits/stdc++.h>

#define ll long long
#define ld long double
#define pb push_back
#define mp make_pair
#define PI 3.14159265359
#define endl '\n'
#define MOD1 1000000033
#define MOD2 99999971
#define MOD3 99999959

using namespace std;

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	
	
	return 0;
}

//////////////////

// Dijkstra's //

const int INF = 2147483647;
const int MAX = 5005;
int D[MAX], N; // Keeps minimum distance to each node
vector<pair<int,int>> E[MAX]; // Adjacency list
 
void dijkstra()
{
    for(int i = 1; i <= N; i++) D[i] = INF;
    D[1] = 0;
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> q;
    q.push({0,1});
 
    while(!q.empty())
    {
        pair<int,int> p = q.top();
        q.pop();
 
        int u = p.second, dist = p.first;
        if(dist > D[u]) continue;
 
        for(pair<int,int> pr : E[u])
        {
            int v = pr.first;
            int next_dist = dist + pr.second;
 
            if(next_dist < D[v])
            {
                D[v] = next_dist;
                q.push({next_dist,v});
            }
        }
    }
}

//////////////////

// Union-find //

int root(int v){return par[v] < 0 ? v : (par[v] = root(par[v]));}
void merge(int x,int y){	//	x and y are some tools (vertices)
        if((x = root(x)) == (y = root(y))     return ;
	if(par[y] < par[x])	// balancing the height of the tree
		swap(x, y);
	par[x] += par[y];
	par[y] = x;
}

//////////////////

// Plus grand rectangle dans histogramme //

const int MAX = 1e6+1;
int t[MAX],l[MAX],r[MAX],n;

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	for(int i=0;i<n;i++)
		cin >> t[i];
	
	vector<int> v;
	for(int i=0;i<n;i++)
	{
		while(!v.empty() && t[v.back()] >= t[i])
			v.pop_back();
		l[i] = (v.empty() ? -1 : v.back());
		v.pb(i);
	}
	
	v.clear();
	for(int i=n-1;i>=0;i--)
	{
		while(!v.empty() && t[v.back()] >= t[i])
			v.pop_back();
		r[i] = (v.empty() ? n : v.back());
		v.pb(i);
	}
	
	ll ans = 0;
	for(int i=0;i<n;i++)
		ans = max(ans,(ll)t[i]*(r[i] - l[i] - 1));
	
	return 0;
}

//////////////////

// Largest palindrome in string //

string s,t;

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> s;
	for(int i=0;i<(int)s.size();i++)
	{
		t.pb(s[i]);
		t.pb('.');
	}
	
	int ans = 0;
	for(int i=0;i<(int)t.size();i++)
	{
		int j,ans0;
		for(j=1,ans0=(t[i]!='.');i-j >= 0 && i+j < (int)t.size() && t[i-j] == t[i+j];ans0+=2*(t[i-j]!='.'),j++);
		ans = max(ans,ans0);
	}
	return 0;
}

//////////////////

// KMP //

const int MAX = 1e6+1;
int f[MAX];

void preKMP(string pattern)
{
    int m = pattern.length(), k;
    f[0] = -1;
    for (int i = 1; i < m; i++)
    {
        k = f[i - 1];
        while (k >= 0)
        {
            if (pattern[k] == pattern[i - 1])
                break;
            else
                k = f[k];
        }
        f[i] = k + 1;
    }
}

bool KMP(string pattern, string target)
{
    int m = pattern.length();
    int n = target.length();
    int f[m];     
    preKMP(pattern, f);     
    int i = 0;
    int k = 0;
    while (i < n)
    {
        if (k == -1)
        {
            i++;
            k = 0;
        }
        else if (target[i] == pattern[k])
        {
            i++;
            k++;
            if (k == m)
                return 1;
        }
        else
            k = f[k];
    }
    return 0;
}

//////////////////

// Bipartite graph matching //

// I added this after the selection. It could have saved me a lot of time. Maybe the first place.

// Note : this O(n*m) implementation was enough too pass SWERC 2014 problem D (n <= 20000 and m <= 20000)... Don't use a faster matching algorithm.

bool dfs(int v) // v is in X, it reaturns true if and only if there is an augmenting path starting from v
{
	if(marque[v])
		return false;
	marque[v] = true;
	for(auto &u : g[v])
		if(match[u] == -1 or dfs(match[u])) // match[i] = the vertex i is matched with in the current matching, initially -1
			return match[v] = u, match[u] = v, true;
	return false;
}

// In the main :

memset(match, -1, sizeof match);
for(int i=0;i<n;i++)
	if(match[i] == -1)
	{
		memset(marque, false, sizeof marque);
		dfs(i);
	}

//////////////////