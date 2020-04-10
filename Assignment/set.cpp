#include <bits/stdc++.h>
using namespace std;

#define SIZE 100

vector <pair<int,int>> adj[SIZE];
vector <int> maxset;

int mis(int num);

void AddEdge(int u, int v,int w)//w == > for level or parent information
{
	adj[u].push_back(make_pair(v,w));
};

int main()
{
	struct node *root=NULL;
	cout<<"enter the number of nodes u want to enter"<<endl;
	int n,num;
	cin>>n;
	int i;
	maxset.assign(10,0);
	int a,b;
	cout<<"enter the edges"<<endl;
	for(i=1;i<=n;i++)
	{
		cin>>a>>b;
		AddEdge(a,b,0);
	}
	cout<<"enter the root node"<<endl;
	cin>>a;
	cout<<mis(a)<<endl;
	return(0);
}

int mis(int num)
{
	if(adj[num].size()==0)//denoting leaf node
	return(1);	
	int out=0;
	for(auto j=adj[num].begin();j!=adj[num].end();j++)
	{
		out=out+mis(j->first);
	}
	int in=1;
	for(auto j=adj[num].begin();j!=adj[num].end();j++)
	{
		if(adj[j->first].size()!=0)//not running for leaf node
		{
			for(auto i=adj[j->first].begin();i!=adj[j->first].end();i++)
			{
				in=in+mis(i->first);
			}
		}
	}
	return(std::max(in,out));
}
	
