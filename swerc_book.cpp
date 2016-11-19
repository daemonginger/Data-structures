//////// MACROS ////////

typedef long long ll;

#define PI 3.14159265359
#define MOD1 1000000033
#define MOD2 99999971
#define MOD3 99999959

         //////// SEGTREES ////////

const int MAX = 1e6+1;
int n;
ll t[2*MAX]; // Segtree size must be at least 2*n.

void build() {  // build the tree. Input values from n to 2*n-1 before calling build.
	for (int i = n - 1; i > 0; --i) t[i] = t[i<<1] + t[i<<1|1];
}

/////// Point updates and range queries ///////
// Exemple : sum-queries and sum-updates

void modify(int p, int value) {  // set value at position p 0-based
	for (t[p += n] = value; p > 1; p >>= 1) t[p>>1] = t[p] + t[p^1];
}

int query(int l, int r) {  // sum on interval [l, r) r exclu, 0-based
	int res = 0;
	for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
		if (l&1) res += t[l++];
		if (r&1) res += t[--r];
	}
	return res;
}

/////////////////////////

/////// Point queries and range updates ///////
// Exemple : sum-queries and sum-updates

void modify(int l, int r, int value) { // set value on interval [l, r) r exclu, 0-based
	for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
		if (l&1) t[l++] += value;
		if (r&1) t[--r] += value;
	}
}

int query(int p) { // get value at position p 0-based
	int res = 0;
	for (p += n; p > 0; p >>= 1) res += t[p];
	return res;
}

/////////////////////////

/////// Range queries and range updates ///////
// Exemple : max-queries and sum-updates

int h = sizeof(int) * 8 - __builtin_clz(n);
int d[MAX]; // To store values to be propagated later.

void apply(int p, int value) {
	t[p] += value;
	if (p < n) d[p] += value;
}

// Warining : include both functions build, they are both important !

void build() {  // build the tree. Input values from n to 2*n-1 before calling build.
	for (int i = n - 1; i > 0; --i) t[i] = max(t[i<<1],t[i<<1|1]);
}

void build(int p) {
	while (p > 1) p >>= 1, t[p] = max(t[p<<1], t[p<<1|1]) + d[p];
}

void push(int p) {
	for (int s = h; s > 0; --s) {
		int i = p >> s;
		if (d[i] != 0) {
			apply(i<<1, d[i]);
			apply(i<<1|1, d[i]);
			d[i] = 0;
		}
	}
}

void inc(int l, int r, int value) { // set value on interval [l, r) r exclu, 0-based
	l += n, r += n;
	int l0 = l, r0 = r;
	for (; l < r; l >>= 1, r >>= 1) {
		if (l&1) apply(l++, value);
		if (r&1) apply(--r, value);
	}
	build(l0);
	build(r0 - 1);
}

int query(int l, int r) { // get value on interval [l, r) r exclu, 0-based
	l += n, r += n;
	push(l);
	push(r - 1);
	int res = -2e9;
	for (; l < r; l >>= 1, r >>= 1) {
		if (l&1) res = max(res, t[l++]);
		if (r&1) res = max(t[--r], res);
	}
	return res;
}

//////////////

///////// RANGE MINIMUM QUERY (REQUÊTES DE MIN EN O(1) SUR INTERVALLE DE TABLEAU STATIQUE)

const int MAX = 1e6,LMAX = 21;
int t[MAX][LMAX],lg[MAX+1];

// r exclu.
int get_rmq(int l,int r)
{
	int k = 31 - __builtin_clz(r-l);
	return min(t[l][k],t[r - (1 << k)][k]);
}

int main()
{
	ios_base::sync_with_stdio(0);
	
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

/////////

                 /////// GRAPHS ///////
                 
//// BELLMAN-FORD TESTED ON FR-IOI ////

const ll INF = 2e17;
const int MAX = 1e3+1;
int n,m,x,y;
ll d[MAX],w;
vector<pair<int,ll>> t[MAX];

int main()
{
	ios_base::sync_with_stdio(0);
	cin >> n >> m;
	
	for(int i=0;i<m;i++)
	{
		cin >> x >> y >> w;
		t[x].pb({y,w});
	}
	
	// IN THIS CODE, SOURCE IS 1 AND DESTINATION IS n, vertices are numbered from 1 to n.
	
	for(int i=1;i<=n;i++)
		d[i] = INF;
	d[1] = 0;
	
	for(int i=0;i<n;i++)
		for(int j=1;j<=n;j++)
			for(auto p : t[j])
				d[p.first] = min(d[p.first],d[j] + p.second);
			
	for(int j=1;j<=n;j++)
		for(auto p : t[j])
			if(d[j] + p.second < d[p.first])
			{
				// CYCLE ABSORBANT
				cout << "ERREUR" << endl;
				return 0;
			}
					
	cout << d[n] << endl;
				
	return 0;
}

////////

// STRONGLY CONNECTED COMPONENTS (TARJAN) //

// WARNING : INDICES OF VERTICES ARE 1-BASED

const int MAX = 1e5+1;
int n,m,cur_comp,low[MAX],id[MAX],comp,c[MAX];
vector<int> t[MAX],v;
bool onstack[MAX];

void dfs(int x)
{
	id[x] = ++comp;
	low[x] = comp;
	onstack[x] = 1;
	v.pb(x);
	for(int y : t[x])
		if(!id[y])
		{
			dfs(y);
			low[x] = min(low[x],low[y]);
		}
		else if(onstack[y])
			low[x] = min(low[x],id[y]);
		if(low[x] == id[x])
		{
			onstack[x] = 0;
			while(v.back() != x)
			{
				c[v.back()] = cur_comp;
				onstack[v.back()] = 0;
				v.pop_back();
			}
			c[x] = cur_comp++;
			v.pop_back();
		}
}

void tarjan(void)
{
	for(int i=1;i<=n;i++)
		if(!id[i])
			dfs(i);
}

// BIPARTITE GRAPH MATCHING //

const int MAX = 1e5+1;
bool marque[MAX];
int match[MAX],n;
vector<int> g[MAX];

// Note : this O(n*m) implementation was enough too pass SWERC 2014 problem D (n <= 20000 and m <= 20000)... Don't use a faster matching algorithm.

bool dfs(int v) // v is in X, it returns true if and only if there is an augmenting path starting from v
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

/////// FINDING BRIDGES ///////

const int MAXN = ...;
vector<int> g[MAXN];
bool used[MAXN];
int timer, tin[MAXN], fup[MAXN];

void dfs (int v, int p = -1) {
	used[v] = true;
	tin[v] = fup[v] = timer++;
	for (size_t i=0; i<g[v].size(); ++i) {
		int to = g[v][i];
		if (to == p)  continue;
		if (used[to])
			fup[v] = min (fup[v], tin[to]);
		else {
			dfs (to, v);
			fup[v] = min (fup[v], fup[to]);
			if (fup[to] > tin[v])
				IS_BRIDGE(v,to);
		}
	}
}

void find_bridges() {
	timer = 0;
	for (int i=0; i<n; ++i)
		used[i] = false;
	for (int i=0; i<n; ++i)
		if (!used[i])
			dfs (i);
}

////////////

/////// FINDING CUTPOINTS ///////

vector<int> g[MAXN];
bool used[MAXN];
int timer, tin[MAXN], fup[MAXN];

void dfs (int v, int p = -1) {
	used[v] = true;
	tin[v] = fup[v] = timer++;
	int children = 0;
	for (size_t i=0; i<g[v].size(); ++i) {
		int to = g[v][i];
		if (to == p)  continue;
		if (used[to])
			fup[v] = min (fup[v], tin[to]);
		else {
			dfs (to, v);
			fup[v] = min (fup[v], fup[to]);
			if (fup[to] >= tin[v] && p != -1)
				IS_CUTPOINT(v);
			++children;
		}
	}
	if (p == -1 && children > 1)
		IS_CUTPOINT(v);
}

int main() {
	int n;
	
	timer = 0;
	for (int i=0; i<n; ++i)
		used[i] = false;
	dfs (0);
}

//////////////

///// EULER TOUR TESTED /////

const int MAX = 1e3+1;
set<pair<int,int>> s;
vector<int> t[MAX];
int n,m,x,y;

void f(int x)
{
	for(int y : t[x])
		if(s.find({min(x,y),max(x,y)}) == s.end())
		{
			s.insert({min(x,y),max(x,y)});
			f(y);
		}
		// PUSH X TO SOME VECTOR IN ORDER TO KEEP THE ANSWER.
		printf("%d ",x);
}

int main()
{
	scanf("%d %d",&n,&m);
	
	while(m--)
	{
		scanf("%d %d",&x,&y);
		t[x].pb(y);
		t[y].pb(x);
	}
	for(int i=1;i<=n;i++)
		if(t[i].size()%2)
		{
			// THERE'S NO EULER TOUR.
			printf("-1\n");
			return 0;
		}
		f(1);
	printf("\n");
	return 0;
}

////////////

/////// MAXIMUM FLOW (DINIC O(N^2*M)) TESTED///////

const int MAXN = ...;
const int INF = 1000000000;

int n, c[MAXN][MAXN], f[MAXN][MAXN], s, t, d[MAXN], ptr[MAXN], q[MAXN],m;

// INITIALISATION: c is the matrix of the capacities, put the capaties of the edges between
// the vertices, and let the other values at 0.
// s is the source vertex and t is the destination vertex.

// you can choose to number vertices from 0 to n-1 or from 1 to n, both will work.

// Check minimal cut just below here to see an example of initialization.

bool bfs() {
	int qh=0, qt=0;
	q[qt++] = s;
	memset (d, -1, (n+1) * sizeof d[0]);
	d[s] = 0;
	while (qh < qt) {
		int v = q[qh++];
		for (int to=0; to<=n; ++to)
			if (d[to] == -1 && f[v][to] < c[v][to]) {
				q[qt++] = to;
				d[to] = d[v] + 1;
			}
	}
	return d[t] != -1;
}

int dfs (int v, int flow) {
	if (!flow)  return 0;
	if (v == t)  return flow;
	for (int & to=ptr[v]; to<=n; ++to) {
		if (d[to] != d[v] + 1)  continue;
		int pushed = dfs (to, min (flow, c[v][to] - f[v][to]));
		if (pushed) {
			f[v][to] += pushed;
			f[to][v] -= pushed;
			return pushed;
		}
	}
	return 0;
}

int dinic() {
	int flow = 0;
	for (;;) {
		if (!bfs())  break;
		memset (ptr, 0, (n+1) * sizeof ptr[0]);
		while (int pushed = dfs (s, INF))
			flow += pushed;
	}
	return flow;
}

//////////////

/////// FIND THE MINIMUM CUT IN O(N^2*M) TESTED ///////

// Just run Dinic and use the last residual graph.
// For example if vertices are from 0 to n-1, source vertex is 0 and destination is n-1.

int main()
{
	scanf("%d %d",&n,&m);
	s = 0;
	t = n-1;
	for(int i=0;i<m;i++)
	{
		int x,y;
		scanf("%d %d",&x,&y);
		scanf("%d",&c[x][y]);
	}
	dinic();
	vector<pair<int,int>> minimal_cut;
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
				if(c[i][j] && d[i] != -1 && d[j] == -1)
					minimal_cut.push_back({i,j});
	return 0;
}

////////

/////// ASSIGNMENT TASK (HUNGARIAN ALGO N^3)

vector<int> u (n+1), v (m+1), p (m+1), way (m+1);
for (int i=1; i<=n; ++i) {
	p[0] = i;
	int j0 = 0;
	vector<int> minv (m+1, INF);
	vector<char> used (m+1, false);
	do {
		used[j0] = true;
		int i0 = p[j0],  delta = INF,  j1;
		for (int j=1; j<=m; ++j)
			if (!used[j]) {
				int cur = a[i0][j]-u[i0]-v[j];
				if (cur < minv[j])
					minv[j] = cur,  way[j] = j0;
				if (minv[j] < delta)
					delta = minv[j],  j1 = j;
			}
			for (int j=0; j<=m; ++j)
				if (used[j])
					u[p[j]] += delta,  v[j] -= delta;
				else
					minv[j] -= delta;
				j0 = j1;
	} while (p[j0] != 0);
	do {
		int j1 = way[j0];
		p[j0] = p[j1];
		j0 = j1;
	} while (j0);
}

// To retreive the answer in the main :

vector<int> ans (n+1);
for (int j=1; j<=m; ++j)
	ans[p[j]] = j;

////// STRING PROCESSING //////

////// SUFFIX ARRAY (nlog(n)^2 using hashes) //////

const int MAX = 1e5+1,N = 26;
ll p[MAX],h[MAX],n;
string s;

inline ll geth(ll x,ll y) // returns the hash of the substring starting at x with lenght y
{
	return h[x] - h[x+y]*p[y];
}

inline int lcp(int x,int y) // returns size of longest common prefixes of suffixes starting at x and y. O(log(n))
{
	int l = 0,r = min(n-x,n-y)+1;
	while(r-l > 1)
	{
		int mid = (l+r)/2;
		if(geth(x,mid) == geth(y,mid))
			l = mid;
		else
			r = mid;
	}
	return l;
}

inline bool sort1(const int& x,const int& y)
{
	int l = lcp(x,y);
	return s[x+l] < s[y+l];
}

vector<int> f() //// returns the indices of sorted suffixes
{
	n = s.size();
	p[0] = 1;
	for(int i=1;i<MAX;i++)
		p[i] = p[i-1]*N;
	h[n] = 0;
	vector<int> ans(n);
	for (int i=n-1;i>=0;--i)
		h[i] = h[i+1]*26 + s[i] - 'a',ans[i] = i;
	
	s += (char)('a' - 1);
	stable_sort(ans.begin(),ans.end(),sort1);
	return ans;
}

//////////

///// AHO-CORASIC /////

struct vertex {
	int next[K];
	bool leaf;
	int p;
	char pch;
	int link;
	int go[K];
};

vertex t[NMAX+1];
int sz;

void init() {
	t[0].p = t[0].link = -1;
	memset (t[0].next, 255, sizeof t[0].next);
	memset (t[0].go, 255, sizeof t[0].go);
	sz = 1;
}

void add_string (const string & s) {
	int v = 0;
	for (size_t i=0; i<s.length(); ++i) {
		char c = s[i]-'a';
		if (t[v].next[c] == -1) {
			memset (t[sz].next, 255, sizeof t[sz].next);
			memset (t[sz].go, 255, sizeof t[sz].go);
			t[sz].link = -1;
			t[sz].p = v;
			t[sz].pch = c;
			t[v].next[c] = sz++;
		}
		v = t[v].next[c];
	}
	t[v].leaf = true;
}

int go (int v, char c);

int get_link (int v) {
	if (t[v].link == -1)
		if (v == 0 || t[v].p == 0)
			t[v].link = 0;
		else
			t[v].link = go (get_link (t[v].p), t[v].pch);
		return t[v].link;
}

int go (int v, char c) {
	if (t[v].go[c] == -1)
		if (t[v].next[c] != -1)
			t[v].go[c] = t[v].next[c];
		else
			t[v].go[c] = v==0 ? 0 : go (get_link (v), c);
		return t[v].go[c];
}

///////////////

///////////

                                     //////// GEOMETRY ////////

///// Tricks /////

///// 1 : CLOCKWISE ORDER /////

// How to know if any polygon is given in clockwise order : check the sign of the sum of (x2 − x1)(y2 + y1). 
// If it's > 0, the polygon is given in clockwise order.

// WARNING : this formula works for direct orthogonal bases only. If the y-axis is inverted (like in most algorithm tasks),
// the order is clockwise if and only if the previous sum is < 0.

///// 2 : Area of polygon /////

// The above formula actualy gives twice the oriented area of the polygon !

// Pick's formula (when points of polygon are on a integer grid) : Area = number of points strictly inside polygon - (points on border)/2 - 1

///// POINT IN POLYGON (PIP) PROBLEM FOR ANY POLYGON O(n*m) /////

// t = coordinates of polygon vertices
// n = number of vertices
// x,y = coordinates of the point to test

// POINT ON BORDER IS CONSIDERED INSIDE BY DEFAULT, CHANGE "on" TO TUNE THIS

// TESTE SUR FRANCE-IOI

const ll OFFSET = 2e9;

int sd(ll d)
{
	if(d > 0)
		return 1;
	else if(d < 0)
		return -1;
	return 0;
}

bool is_inside(int **t,int n,int x,int y)
{
	sum = 0;
	bool on = 1;
	for(int i=0;i<n;i++)
	{
		int j = (i+1)%n;
		if((ll)(x - t[i][0])*(y - t[j][1]) - (ll)(x - t[j][0])*(y - t[i][1]) == 0 &&
				(ll)(t[i][0] - x)*(t[j][0] - x) + (ll)(t[i][1] - y)*(t[j][1] - y) <= 0)
			return on;	
		
		ll xb = (ll)t[i][0]*(t[j][1] - t[i][1]) + (y - t[i][1])*(t[j][0] - t[i][0]);
		ll d = t[j][1] - t[i][1],sd = sgn(d);
		if(sd*xb > (ll)sd*d*x &&
			OFFSET*y + 1 > OFFSET*min(t[i][1],t[j][1]) && OFFSET*y + 1 < OFFSET*max(t[i][1],t[j][1]))
			sum += sd;
	}
	return sum != 0;
}

/// PIP (POINT IN POLYGON) FOR CONVEX POLYGONS IN O(n + m*log(n)) ///

// POINT ON BORDER IS CONSIDERED INSIDE BY DEFAULT, CHANGE "on" TO TUNE THIS

// PAS TESTE SUR UN JUGE MAIS SUR DES GROS TESTS EN LOCAL CA MARCHE

const int MAX = 1e6+1,INF = 2e9;
int n,m;
bool ans[MAX];
pair<int,int> p[MAX];

int sgn(ll d)
{
	if(d > 0)
		return 1;
	else if(d < 0)
		return -1;
	return 0;
}

inline bool ison(int x,int y,int i,int j) // CHECK IF POINT IS ON SEGMENT
{
	return (ll)(x - p[i].first)*(y - p[j].second) - (ll)(x - p[j].first)*(y - p[i].second) == 0 &&
				(ll)(p[i].first - x)*(p[j].first - x) + (ll)(p[i].second - y)*(p[j].second - y) <= 0;
}

int main()
{
	bool on = 1; // whether points on border should be considered in or out
	int i_min = 0,m_min = INF,i_max = 0,m_max = -INF; // don't use the pair<int,int> trick because <= and >= are important
	for(int i=0;i<n;i++)
	{
		int j = (i-1+n)%n;
		if(p[i].first < m_min || (p[i].first == m_min && p[i].first == p[j].first))
		{
			m_min = p[i].first;
			i_min = i;
		}
		if(p[i].first > m_max || (p[i].first == m_max && p[i].first == p[j].first))
		{
			m_max = p[i].first;
			i_max = i;
		}
	}
	//    cout << i_min << " " << i_max << endl;
	for(int k=0;k<m;k++)
	{
		int x,y;
		scanf("%d %d",&x,&y); // inputing the coordinates of this query
		if(n == 2)
			ans[k] = ison(x,y,0,1) && on;
		else if(x < m_min || x > m_max)
			ans[k] = 0;
		else
		{
			int l = i_min,r = i_max;
			while((l+1)%n != r)
			{
				int mid = (l + ((r-l+n)%n)/2)%n;
				if(p[mid].first <= x)
					l = mid;
				else
					r = mid;
			}
			// l is now the last point in ascending curve with absisse <= x
			int j = (l+1)%n,a = sgn((ll)(x - p[l].first)*(y - p[j].second) - (ll)(x - p[j].first)*(y - p[l].second));
			if(!a)
			{
				ans[k] = ison(x,y,l,j) && on;
				continue;
			}
			
			l = i_max,r = i_min;
			while((l+1)%n != r)
			{
				int mid = (l + ((r-l+n)%n)/2)%n;
				if(p[mid].first >= x)
					l = mid;
				else
					r = mid;
			}
			// l is now the last point in descending curve with absisse >= x
			j = (l+1)%n;
			int b = (ll)(x - p[l].first)*(y - p[j].second) - (ll)(x - p[j].first)*(y - p[l].second);
			ans[k] = (a ? a*b > 0 : ison(x,y,l,j) && on);
		}
	}
}

///// CONVEX HULL (GRAHAM SCAN) TESTED /////

const int MAX = 1e4+1,INF = 2e9;
int n,x = INF,y = INF;
vector<pair<int,int>> v; // v contains the convex hull with coordinates of points
pair<int,int> t[MAX]; // points to get the convex hull from

bool comp(pair<int,int> const& p1,pair<int,int> const& p2)
{
	int x1 = p1.first - x,y1 = p1.second - y,x2 = p2.first - x,y2 = p2.second - y;
	ll d = (ll)x2*y1 - (ll)x1*y2;
	if(!x1 && !y1)
		return 1;
	else if(!x2 && !y2)
		return 0;
	return d < 0;
}

int main()
{
	if(n == 1)
	{
		v.pb(t[0]);
		return 0;
	}
	for(int i=0;i<n;i++)
	{
		if(t[i].second < y || (t[i].second == y && t[i].first < x))
		{
			x = t[i].first;
			y = t[i].second;
		}
	}
	sort(t,t+n,comp);
	v.pb(t[0]);
	v.pb(t[1]);
	for(int i=2;i<n;i++)
	{
		int l = v.size();
		while(l > 2 && (ll)(t[i].first - v[l-1].first)*(v[l-2].second - v[l-1].second) <=
			(ll)(v[l-2].first - v[l-1].first)*(t[i].second - v[l-1].second))
		{
			v.pop_back();
			l--;
		}
		v.pb(t[i]);
	}
	return 0;
}
////////////////

///// EQUATION OF STRAIGHT LINE GIVEN TWO POINTS (x1,y1) and (x2,y2) /////
ll a = y1 - y2,b = x1 - x2,c = -a*x1 - b*y1;
/////////////

///// INTERSECTION OF 2 LINES /////
Say the lines are defined by :
a1*x + b1*y + c1 = 0
a2*x + b2*y + c2 = 0

det = a1*b2 - a2*b1
if det != 0, solution is :

x = -(c1*b2 - c2*b1)/det
Y = -(a1*c2 - a2*c1)/det
/////////////

///// INTERSECTION OF 2 SEGMENTS /////
First, find a cartesian equation for both segments.
Then compute the intersection of the lines.
Then check if the point lies on both segment.

To check if point (x,y) lies on the segment [(x1,y1),(x2,y2)] :
(x - x1)*(x - x2) + (y - y1)*(y - y2) must be <= 0
/////////////

///// INTERSECTION OF STRAIGHT LINE AND CIRCLE /////
mult = (a^2 + b^2)*sqrt((a^2 + b^2)*r^2 - c^2)
ax = x0 + b*mult
ay = y0 - a*mult
bx = x0 - b*mult
by = y0 + a*mult
/////////////

///// INTERSECTION OF CIRCLE AND CIRCLE /////
Assuming we have circles of equations :
x2 + y2 = r12
(x - x2)^2 + (y - y2)^2 = r22

If the two circles have a intersection (easy to check), then the equation of the line passing
by the two points of intersection is given by :

a = -2x^2
b = -2y^2
c = x2^2 + y2^2 + r1^2 - r^2

You can then use the line-circle formula.
/////////////

///// 2 NEAREST POINTS O(nlog(n)) /////

struct pt {
	int x, y, id;
};

inline bool cmp_x (const pt & a, const pt & b) {
	return a.x < b.x || a.x == b.x && a.y < b.y;
}

inline bool cmp_y (const pt & a, const pt & b) {
	return a.y < b.y;
}

pt a[MAXN];

double mindist;
int ansa, ansb;

inline void upd_ans (const pt & a, const pt & b) {
	double dist = sqrt ((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y) + .0);
	if (dist < mindist)
		mindist = dist,  ansa = a.id,  ansb = b.id;
}

void rec (int l, int r) {
	if (r - l <= 3) {
		for (int i=l; i<=r; ++i)
			for (int j=i+1; j<=r; ++j)
				upd_ans (a[i], a[j]);
			sort (a+l, a+r+1, &cmp_y);
		return;
	}
	
	int m = (l + r) >> 1;
	int midx = a[m].x;
	rec (l, m),  rec (m+1, r);
	static pt t[MAXN];
	merge (a+l, a+m+1, a+m+1, a+r+1, t, &cmp_y);
	copy (t, t+r-l+1, a+l);
	
	int tsz = 0;
	for (int i=l; i<=r; ++i)
		if (abs (a[i].x - midx) < mindist) {
			for (int j=tsz-1; j>=0 && a[i].y - t[j].y < mindist; --j)
				upd_ans (a[i], t[j]);
			t[tsz++] = a[i];
		}
}

// IN THE MAIN :

sort (a, a+n, &cmp_x);
mindist = 1E20;
rec (0, n-1);

////////

/////// RANDOM ///////

// Union-find (bmerry style)//

const int MAX = 1e6+1;
int par[MAX]; // Initialize par with -1.

int root(int v){return par[v] < 0 ? v : (par[v] = root(par[v]));}
void merge(int x,int y){	//	x and y are some vertices
	if((x = root(x)) == (y = root(y)))     return ;
		if(par[y] < par[x])	// balancing the height of the tree
			swap(x, y);
		par[x] += par[y];
	par[y] = x;
}

//////////////////

// FAST EXPO MODULO //
int pow(int a,int b,int m)
{
	if(b==0) return 1;
		else if(b%2==0) return pow(a*a%m,b/2,m);
		else return pow(a,b-1,m)*a%m;
}
//////////
// INVERSE MODULO //
Inverse of a modulo m is a^(m-2) modulo m.
/////////

// FFT AND POLYNOMIAL MULTIPLICATION (CHECKED)//

typedef complex<double> base;

void fft (vector<base> & a, bool invert) { // if invert = true, compute inverse transform.
	int n = (int) a.size();
	if (n == 1)  return;
		
		vector<base> a0 (n/2),  a1 (n/2);
	for (int i=0, j=0; i<n; i+=2, ++j) {
		a0[j] = a[i];
		a1[j] = a[i+1];
	}
	// Split vector in even and odd indexes vectors, compute the Fourier transform of the two parts.
	fft (a0, invert);
	fft (a1, invert);
	// Merge the two parts in O(n) ---> total cost of algo is O(nlog(n))
	double ang = 2*PI/n * (invert ? -1 : 1);
	base w (1),  wn (cos(ang), sin(ang));
	for (int i=0; i<n/2; ++i) {
		a[i] = a0[i] + w * a1[i];
		a[i+n/2] = a0[i] - w * a1[i];
		if (invert)
			a[i] /= 2,  a[i+n/2] /= 2;
		w *= wn;
	}
}

void multiply (const vector<int> & a, const vector<int> & b, vector<int> & res) {
	vector<base> fa (a.begin(), a.end()),  fb (b.begin(), b.end());
	size_t n = 1;
	while (n < max (a.size(), b.size()))  n <<= 1;
		n <<= 1;
	fa.resize (n),  fb.resize (n);
	// Find Fourier transform of both polynomials
	fft (fa, false),  fft (fb, false);
	// Multiply term to term (Fourier transform transforms convolution in product)
	for (size_t i=0; i<n; ++i)
		fa[i] *= fb[i];
	// Find invert transform of the result
	fft (fa, true);
	// Convert result to int.
	res.resize (n);
	for (size_t i=0; i<n; ++i)
		res[i] = int (fa[i].real() + 0.5);
}

/////////////

// 2-SAT //
const int MAX = 1e5+1;
int n,m,cur_comp,low[MAX],id[MAX],comp,c[MAX];
vector<int> t[MAX],v;
bool onstack[MAX];
vector<int> ans;

int main()
{
	// n is even, for i in [1,n], i ^ 1 = NOT i. vertices look like (a,NOT a,b, NOT b,...)
	// so we build the graph like this from logic variables :
	for(int i=0;2*i<n;i++)
	{
		int x,y;
		cin >> x >> y;
		g[x^1].pb(y);
		g[y^1].pb(x);
	}
	// first use tarjan to find SCC.
	// WARNING : INDICES OF VERTICES ARE 1-BASED IN OUR IMPLEMENTATION OF TARJAN
	tarjan();
	for (int i=0;i<n;i++)
		if (c[i] == comp[i ^ 1])
			// THERES NO SOLUTION
	// RETREIVE ONE SOLUTION TO THE PROBLEM
	for (int i=0;i<n;i+=2) {
		ans.pb(comp[i] > comp [i ^ 1]? i : i ^ 1);²
}
////////

// SOLVE LINEAR SYSTEM (ax = b) //

// Put b in the last column of a !

int gauss (vector < vector<double> > a, vector<double> & ans) {
	int n = (int) a.size();
	int m = (int) a[0].size() - 1;
	
	vector<int> where (m, -1);
	for (int col=0, row=0; col<m && row<n; ++col) {
		int sel = row;
		for (int i=row; i<n; ++i)
			if (abs (a[i][col]) > abs (a[sel][col]))
				sel = i;
			if (abs (a[sel][col]) < EPS)
				continue;
			for (int i=col; i<=m; ++i)
				swap (a[sel][i], a[row][i]);
			where[col] = row;
		
		for (int i=0; i<n; ++i)
			if (i != row) {
				double c = a[i][col] / a[row][col];
				for (int j=col; j<=m; ++j)
					a[i][j] -= a[row][j] * c;
			}
			++row;
	}
	
	ans.assign (m, 0);
	for (int i=0; i<m; ++i)
		if (where[i] != -1)
			ans[i] = a[where[i]][m] / a[where[i]][i];
		for (int i=0; i<n; ++i) {
			double sum = 0;
			for (int j=0; j<m; ++j)
				sum += ans[j] * a[i][j];
			if (abs (sum - a[i][m]) > EPS)
				return 0;
		}
		
		for (int i=0; i<m; ++i)
			if (where[i] == -1)
				return INF;
			return 1;
}

////////////

////// LCA O(log(n)) queries, O(nlog(n)) preprocessing //////

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
	anc[0][0] = 0 // here it's useless, in practice you should remplace it by anc[root][0] = root
	for(int j=1;j<LMAX;j++)
		for(int i=1;i<=n;i++)
			anc[i][j] = anc[anc[i][j-1]][j-1];
	for(int i=1;i<=n;i++)
		f(i);
	return 0;
}

/////////////