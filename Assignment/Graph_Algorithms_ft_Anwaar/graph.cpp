#include"graph.h"
#include<iostream>
#include<bits/stdc++.h>
using namespace std;

//constructor
Graph:: Graph()
{
	E = 0;

	cout << "Enter no. of vertices:" << endl;
	cin >> V;

	//prompt whether graph is directed or undirected
	cout << "Press 1 if graph is directed, 0 otherwise:";
	cin >> dir_flag;

	//prompt for edges
	int check=1;
	int u,v,w;

	cout << "Enter edges" << endl;
	while(check != 0)
	{
		cout << "Enter u,v & w: ";
		cin >> u >> v >> w;
		AddEdge(u, v, w, dir_flag);
		cout << "Press 1 to add another edge, otherwise 0:";
		cin >> check;
	}

	//initilize visit array to zero
	visit.assign(V,0);
};

//overloaded constructor
Graph::Graph(int n, bool flag)
{
    V = n;
    E = 0;

    visit.resize(n);
    for(int i = 0; i < V; i++)
		visit[i] = 0;

    dir_flag = flag;
}

//utility function to add edge to the graph
void Graph::AddEdge(int u, int v, int w, int dir_flag)
{
	if( u == v)
		return;
	
    E++;
	adj[u].push_back(make_pair(v,w));
	//if undirected
	if(dir_flag == 0)
		adj[v].push_back(make_pair(u,w));
}


void BellmanFord(Graph G, int s)
{
    int V= G.getV();
    int E= G.getE();
    int dis[V], Parent[V];
    //initizles distances and parents 
    int i;
    for(i=0;i<V;i++)
    {
        dis[i]= INT16_MAX;
        Parent[i]= INT16_MAX;
    }
    dis[s]= 0;
    Parent[s]= s;

    //now our business starts
    //for every edge (u,v), check if going to v is cheaper through u
    int counter =0 , u ,v,w ;
    while(counter!= V-1)
    {
        for(i =0 ; i<V; i++)
        for(auto it = G.adj[i].begin(); it!= G.adj[i].end(); it++)
        {
            u= i; v = it->first; w= it->second;
            if(dis[v]> dis[u] + w)
            {
                dis[v]= dis[u] + w;
                Parent[v]= u;
            } 
        }
        
        counter++;
    }

    //our distances and paths are ready by now
    for(i=0; i<V ; i++)
    {
    cout<<" Distance of "<<i<<" from "<<s<<" is: ";
    if(dis[i]==INT16_MAX)
    cout<<"infinity"<<endl;
    else
    {
        cout<<dis[i]<<endl;
         cout<<"The path is: ";

   //extract path
    stack <int> temp;
    temp.push(i);
    int k = Parent[i];
    while(k!=s)
    {
        temp.push(k);
        k = Parent[k];
    }
    temp.push(s);

    while(!temp.empty())
    {
        u = temp.top();  temp.pop();
        cout<<u<<"-";   
    }
    cout<<endl;
    }
    
   


    
    }

}

//_________________________________________________________________________________________
void Dijkstra(Graph G, int s)
{
    int V = G.getV();
    int dis[V], parent[V];
    bool visit[V];
    
    //initilze distances, parents and visit array
    int i;
    for(i=0;i<V;i++)
    {
        dis[i]= INT16_MAX;
        parent[i]= INT16_MAX;
        visit[i] = false;
    }

    dis[s]= 0;
    parent[s] = s;

    int counter =0;
    while(counter != V-1)
    {
        //get the min distance vertex
        //should not be already visited
        int min = min_dis(dis,visit,V);

        visit[min] = true;

        //update min's neighbours if going through min is cheaper and they
        //are not already visited
        int u,v,w;
        if(!G.adj[min].empty())
        {
        for(auto it= G.adj[min].begin(); it!= G.adj[min].end() ; it++)
        {
           u= min ; v = it->first; w= it->second;
           if(visit[v]==false)
           {
               if(dis[v]> (dis[u]+w) )
               {
                   dis[v] = dis[u] + w;
                   parent[v]= u;
               }
           }   
        }
        }

        counter++;
    }

    //distanes and paths are ready
    //print them

    for(i =0; i<V ; i++)
    {
        cout<<"Distance of "<<i<<" from "<<s<<" is :";
        if(dis[i]==INT16_MAX)
        cout<<"infinity"<<endl;
        else
        {
            cout<<dis[i]<<endl;
        
        cout<<"The path is :";

        //extract path
        stack <int> temp;
        temp.push(i);
        int k = parent[i];
        while(k!=s)
        {
            temp.push(k);
            k = parent[k];
        }
        temp.push(s);

        while(!temp.empty())
        {
             k= temp.top(); temp.pop();
             cout<<k<<"-";
        }
        cout<<endl;
    }
    }
}

int min_dis(int dis[],bool visit[],int V)
{
    int index, min=INT16_MAX; ///result
    for(int i=0; i<V ; i++)
    {
      if(dis[i]<min && visit[i]==false)
      {
          min = dis[i];
          index= i;
      }
    }

    return index;

    
}

void all_pair_shortest(Graph G)
{
 int V= G.getV();
 for(int i=0; i<V; i++)
 Dijkstra(G,i);   
}

//_________________________________________________________________________________________

void Flyod_Warshall(Graph G)
{
    int V= G.getV();
    int dis[V][V], path[V][V];

    //initilize the matrices
    int i,j,u,v,w,k;
    for(i=0; i<V; i++)
    for(j=0;j<V;j++)
    {
        if(i==j)
        {
            dis[i][j]= 0;
            path[i][j]= i;
        }
        else
        {
            dis[i][j]= INT16_MAX;
            path[i][j]= INT16_MAX;
        }   
    }
    for(i=0 ; i<V ; i++)
    for(auto it = G.adj[i].begin(); it!= G.adj[i].end(); it++)
    {
        u = i; v = it->first; w = it->second;
        dis[u][v]= w;
        path[u][v]= u;
    }


    //now our business starts
    //for each edge (i,j) check if going through an intermediate edge k is cheaper ( k ranges from 0 to V-1)
    for(k =0; k<V; k++)
    for(i=0;i<V;i++)
    for(j=0;j<V;j++)
    {
        //minor optimizations
        //1. diagonals will not be updated
        //2. kth row and kth column will not change
        if(i!=j && i!=k && j!=k)
        {
            if(dis[i][j]> dis[i][k]+ dis[k][j])
            {
                dis[i][j]= dis[i][k]+ dis[k][j] ; 
                path[i][j]= path[k][j];
            }
        }
    }


    //our distances and path are ready by now
    for(i=0; i<V ; i++)
    for(j =0; j<V ; j++)
    {
        if(dis[i][j]!=INT16_MAX)
        {
        cout<<"Distance b/w "<<i<<" & "<<j<<" is: "<<dis[i][j]<<endl;
        cout<<"The path is: ";

        stack <int> temp;
        temp.push(j);
        k= path[i][j];
        while(k!=i)
        {
            temp.push(k);
            k= path[i][k];
        }
        temp.push(i);
        
        while(!temp.empty())
        {
            int i = temp.top();     temp.pop();
            cout<<i<<"- ";
        }
        cout<<endl;
        }
    }
}

