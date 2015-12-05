#include<bits/stdc++.h>

#define ll long long
#define pb push_back
#define mk make_pair
#define PI 3.14159265359
#define endl '\n'

using namespace std;

struct Ctree
{
	int key,priority,count;
	Ctree *l,*r;
	Ctree (){};
	Ctree(int _key): key(_key),priority(rand()),count(0),l(NULL),r(NULL) {}
	Ctree(int _key,int _priority): key(_key),priority(_priority),count(0),l(NULL),r(NULL) {}
};

int cnt(Ctree *t)
{
	return t ? t->count : 0;
}

void upd_cnt(Ctree *t)
{
	if(t)
		t->count = 1 + cnt(t->l) + cnt(t->r);
}

ostream& operator<<(ostream &stream,Ctree const& t)
{
	if(&t == NULL)
		return stream;
// 	if(t.l != NULL)
// 		cout << "l " << t.l->key << " " << t.l->priority << endl;
// 	if(t.r != NULL)
// 		cout << "r " << t.r->key << " " << t.r->priority << endl;
	stream << *(t.l);
	stream << t.key << " " << t.priority << endl;
	stream << *(t.r);
	return stream;
}

void split(Ctree *t,int x,Ctree *&l,Ctree *&r)
{
	if(!t)
	{
		l = NULL;
		r = NULL;
		return;
	}
// 	cout << "yo" << endl;
	if(x <= t->key)
	{
		split(t->l,x,l,t->l);
		r = t;
	}
	else
	{
		split(t->r,x,t->r,r);
		l = t;
	}
	upd_cnt(t);
}

void insert(Ctree *&t,Ctree *t_ins)
{
	if(!t)
		t = t_ins;
	else if(t_ins->priority > t->priority)
	{
		split(t,t_ins->key,t_ins->l,t_ins->r);
		t = t_ins;
	}
	else
		insert(t_ins->key < t->key ? t->l : t->r,t_ins);
}

void merge(Ctree *&t,Ctree *l,Ctree *r)
{
	if(!l || !r)
		t = l ? l : r;
	else if(l->priority < r->priority)
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
}

// Only erases one (not chosen) occurance of the key x :
void erase(Ctree *&t,int x)
{
	if(!t)
		return;
	
	if(t->key == x)
		merge(t,t->l,t->r);
	else
		erase(x < t->key ? t->l : t->r,x);
}

Ctree *unite(Ctree *l,Ctree *r)
{
	if(!l || !r)
		return l ? l : r;
	
	if(l->priority < r->priority)
		swap(l,r);
	Ctree *lr,*rr;
	split(r,l->key,lr,rr);
	l->l = unite(l->l,lr);
	l->r = unite(l->r,rr);
	return l;
}

int main()
{
	ios_base::sync_with_stdio(0);
	srand(time(NULL));
	
	Ctree *t = new Ctree(5);
	insert(t,new Ctree(6));
	insert(t,new Ctree(4));
	Ctree *t1 = new Ctree(1);
	insert(t1,new Ctree(5));
	insert(t,new Ctree(8));
	cout << *unite(t,t1);
	
	return 0;
}