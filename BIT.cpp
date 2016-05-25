#include<bits/stdc++.h>

#define ll long long

using namespace std;

const int MAX = 1e6+1;
ll ft[MAX];
int A[MAX],n;

/////// Point Updates and Range Queries ///////

// Add v to A[p]
void update(int p,int v):
{
	for (; p <= n; p += p&(-p))
		ft[p] += v;
}
	
// Return sum A[1...b]	 
ll query(int b)
{
	ll sum = 0;
	for(; b > 0; b -= b&(-b))
		sum += ft[b];
		return sum;
}
		
// Return sum A[a...b]
int query(int a,int b) {return query(b) - query(a-1);}

//////////////////////////////////////////

/////// Range Updates and Point queries ///////

// Point query: Returns the value at position b in the array
ll query(int b)	{
	ll sum = 0;
	for (; b; b -= b & -b) sum += ft[b];
	return sum;
}

// Point update: Adds v to the value at position k in the array
void update(int k, int v) {
	for (; k <= N; k += k & -k) ft[k] += v;
}

// Range update: Adds v to each element in [i...j] in the array
void range_update(int i, int j, int v)	{
	update(i, v);
	update(j + 1, -v);
}

///////////////////////////////////

/////// Range Updates and Range Queries ///////

ll query(ll* ft, int b)	{
	ll sum = 0;
	for (; b; b -= b & -b) sum += ft[b];
	return sum;
}

// Range query: Returns the sum of all elements in [1...b]
ll query(int b) {
	return query(B1, b) * b - query(B2, b);
}

// Range query: Returns the sum of all elements in [i...j]
ll range_query(int i, int j)    {
	return query(j) - query(i - 1);
}

// Point update: Adds v to the value at position k in the array
// ft is the fenwick tree which represents that array
void update(ll* ft, int k, ll v) {
	for (; k <= N; k += b & -b) ft[k] += v;
}

// Range update: Adds v to each element in [i...j]
void range_update(int i, int j, ll v)	{
	update(B1, i, v);
	update(B1, j + 1, -v);
	update(B2, i, v * (i - 1));
	update(B2, j + 1, -v * j);
}

//////////////////////////////////////////