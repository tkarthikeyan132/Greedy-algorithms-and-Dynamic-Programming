#include <iostream>
#include<vector>
using namespace std;

class Graph
{
	private:
	int V;
	int E;
	int dir_flag;

	public:
	Graph(); // constructor
	Graph(int n, bool flag); // overloaded constructor

	#define SIZE 1000
	vector <pair<int,int>> adj[SIZE]; //adjacency list

	void AddEdge(int u, int v, int w, int dir_flag); // utilitity function for adding edge

	vector<int> visit; // visit vector

	void Pgraph();

	// getters for V and E
	int getV()
	{
		return V;
	}

	int getE()
	{
		return E;
	}
	void setV(int x)
	{
		V = x;

	};



};

//flyod warshall algorithm
void Flyod_Warshall( Graph G);

//Bellman Ford Algorithm
void BellmanFord(Graph G, int s);

//dijkstra's algorithm
void Dijkstra(Graph G, int s);
int min_dis(int dis[],bool visit[],int V); //utility function of dijkstra
void all_pair_shortest(Graph G);

