#include<bits/stdc++.h>

#define ll long long
#define pb push_back
#define mk make_pair
#define PI 3.14159265359
#define endl '\n'

using namespace std;

struct Ctree
{
	int value,priority,count;
	ll sum;
	bool rev;
	Ctree *l,*r;
	Ctree (){};
	Ctree(int _value,int _priority = rand()): value(_value),priority(_priority),count(1),sum(_value),rev(0),l(NULL),r(NULL) {}
};

int sum(Ctree *t)
{
	return t ? t->sum : 0;
}

void upd_sum(Ctree *t)
{
	if(t)
		t->sum = t->value + sum(t->l) + sum(t->r);
}

int cnt(Ctree *t)
{
	return t ? t->count : 0;
}

void upd_cnt(Ctree *t)
{
	if(t)
		t->count = 1 + cnt(t->l) + cnt(t->r);
}

void push(Ctree *&t)
{
	if(t && t->rev)
	{
		t->rev = 0;
		swap(t->l,t->r);
		if(t->l)
			t->l->rev ^= 1;
		if(t->r)
			t->r->rev ^= 1;
	}
}

ostream& operator<<(ostream &stream,Ctree const& t)
{
	stream << t.value << " " << t.priority << " " << t.count << endl;
	return stream;
}

void disp(Ctree *&t)
{
	if(!t)
		return;
	
	push(t);
	disp(t->l);
	cout << *t;
	disp(t->r);
}

void split(Ctree *t,int pos,Ctree *&l,Ctree *&r,int nb_l = 0)
{
	if(!t)
	{
		l = NULL;
		r = NULL;
		return;
	}
	push(t);
	int cur_key = cnt(t->l) + nb_l;
	if(pos <= cur_key)
	{
		split(t->l,pos,l,t->l,nb_l);
		r = t;
	}
	else
	{
		split(t->r,pos,t->r,r,cur_key + 1);
		l = t;
	}
	upd_cnt(t);
	upd_sum(t);
}


void merge(Ctree *&t,Ctree *l,Ctree *r)
{
	if(!l || !r)
	{
		t = l ? l : r;
		return;
	}
	push(l);
	push(r);
	if(l->priority < r->priority)
	{
		merge(r->l,l,r->l);
		t = r;
	}
	else
	{
		merge(l->r,l->r,r);
		t = l;
	}
	upd_cnt(t);
	upd_sum(t);
}

void insert(Ctree *&t,Ctree *t_ins,int pos)
{
	if(!t)
		t = t_ins;
	Ctree *t1,*t2;
	split(t,pos,t1,t2);
	merge(t1,t1,t_ins);
	merge(t,t1,t2);
}

void erase(Ctree *&t,int pos)
{
	if(!t)
		return;
	Ctree *t1,*t2,*t3;
	split(t,pos,t1,t2);
	split(t2,1,t3,t2);
	merge(t,t1,t2);
	free(t3);
}

ll req_sum(Ctree *&t,int l,int r)
{
	Ctree *t1,*t2,*t3;
	split(t,l,t1,t2);
	split(t2,r-l+1,t2,t3);
	ll ans = sum(t2);
	merge(t2,t2,t3);
	merge(t,t1,t2);
	return ans;
}

Ctree* make_treap(int tab[],int n)
{
	if(!n)
		return NULL;
	Ctree *t = new Ctree(tab[n-1]);
	for(int i=n-2;i>=0;i--)
	{
		insert(t,new Ctree(tab[i]),0);
	}
	
	return t;
}

void reverse(Ctree *&t,int l,int r)
{
	Ctree *t1,*t2,*t3;
	split(t,l,t1,t2);
	split(t2,r-l+1,t2,t3);
	t2->rev ^= 1;
	merge(t2,t2,t3);
	merge(t,t1,t2);
}


int main()
{
	ios_base::sync_with_stdio(0);
	srand(time(NULL));
	
	int tab[] = {1,2,3,4,5,6,7,8};
	Ctree *t = make_treap(tab,8);

	reverse(t,2,6);
	disp(t);
	cout << endl;
	reverse(t,6,7);
	disp(t);
	
	return 0;
}