/******************************************************************************
  Title          : AdjanceyList.h
  Author         : Wei Lian
  Created on     : May 13, 2018
  Description    : header file that include functions that create the graph,dijkstra Algorithm and topological sorting algorithms.
  Purpose        : 
  Modifications  : 

  Notes:
 
******************************************************************************/
#ifndef ADJACENCY_LIST_H
#define ADJACENCY_LIST_H

#include <list>
#include <map>
#include <stack>
#include <queue>
#include <iostream>
#include <utility>
#define INF 0x3f3f3f3f


using namespace std;



template <typename Comparable>
class AdjancecyList
{
	public:
		AdjancecyList(size_t size_){
			this->size_=size_;
			adjList=new list<pair<Comparable,double>>[size_+1];
		}
		//add an edge to the adjlist
		//in this function, a is the start vertex, b is the end vertex.
		void insert( Comparable a, Comparable b,double weight ) 
		{
    		adjList[a].push_back(make_pair(b,weight));
  		}
  		bool isConnected(Comparable a, Comparable b)
  		{
  			typename list<pair<Comparable,double>>::iterator i;
  			for(i =adjList[a].begin();i!=adjList[a].end();++i)
  			{
  				if((*i).first==b)
  					return true;
  			}
  			return false;
  		}
  		//in this function, a is the start vertex, b is the end vertex.
  		//search by the for loop to find if b exist in the a
  		double getWeight(Comparable a, Comparable b)
  		{
  			typename list<pair<Comparable,double>>::iterator i;
  			for(i =adjList[a].begin();i!=adjList[a].end();++i)
  			{
  				if((*i).first==b)
  					return (*i).second;
  			}
  			return -1;
  		}
  		size_t getSize()
  		{
  			return size_;
  		}
  		void printAdjlist()
  		{
  			typename list<pair<Comparable,double>>::iterator j;
  			for(int i=1;i<=size_;++i)
  			{
  				cout<<i<<": ";
  				for(j=adjList[i].begin();j!=adjList[i].end();++j){
  					cout<<(*j).first<<" "<<(*j).second<<" ";
  				}
  				cout<<endl;
  			}
  		}
  		//Implement	Dijkstra’s	Algorithm,	using	a	priority	queue.
  		// Prints shortest paths from src to all other vertices
  		void dijkstraAlgorithm(Comparable sourceVertex)
  		{
  			// Create a priority queue to store vertices that
    		// are being preprocessed. This is weird syntax in C++.
    		// Refer below link for details of this syntax
  			priority_queue<pair<Comparable, double>,vector<pair<Comparable, double>>,greater<pair<Comparable, double>>>pq;
  			// Create a vector for distances and initialize all
    		// distances as infinite (INF)
    		vector<double> Vertex_distance(size_, INF);
    		// Insert source itself in priority queue and initialize
    		// its distance as 0.
    		pq.push(make_pair(0,sourceVertex));
    		Vertex_distance[sourceVertex]=0;
    		/* Looping till priority queue becomes empty (or all
      		distances are not finalized) */
      		int path[size_];
      		// Initialize paths to -1
      		for(int i=0;i<size_;++i)
      		{
      			path[i]=-1;
      		}
      		//while the priorityQueue contains elements
      		while(!pq.empty())
      		{
      			// The first vertex in pair is the minimum distance
        		// vertex, extract it from priority queue.
       			// vertex label is stored in second of pair (it
       			// has to be done this way to keep the vertices
       			// sorted distance (distance must be first item
        		// in pair)
        		int Min_Dist=pq.top().second;
        		pq.pop();
        		// 'i' is used to get all adjacent vertices of a vertex
        		typename list<pair<Comparable,double>>::iterator i;
        		for(i=adjList[Min_Dist].begin();i!=adjList[Min_Dist].end();++i)
        		{
        			// Get vertex label and weight of current adjacent of Min_Dist
        			Comparable temp_vertex=(*i).first;
        			double weight=(*i).second;
        			//If there is shorted path to temp_vertex through Min_dist.
        			if(Vertex_distance[temp_vertex]>Vertex_distance[Min_Dist]+weight)
        			{
        				// Updating distance of v, keeps it shortest
        				Vertex_distance[temp_vertex]=Vertex_distance[Min_Dist]+weight;
        				pq.push(make_pair(Vertex_distance[temp_vertex],temp_vertex));
        				//store the paths we went
        				path[temp_vertex]=Min_Dist;
        			}
        		}
      		}
      		for(int i=1;i<size_;++i)
      		{
      			cout<<i<<": ";
      			if(sourceVertex==i)
      			{
      				cout<<i;
      			}
      			else
      			{
      				printpath(path,i);
      				cout<<i;
      			}
      			cout<<" (Cost: "<<Vertex_distance[i]<<") \n";
      		}
  		}
  		 //print out all paths we went.
  		void printpath(int predecessorVertex[],int end)
  		{
  			//didn't went this way
  			if(predecessorVertex[end]==-1)
  				return;
  			printpath(predecessorVertex,predecessorVertex[end]);
  			cout<<predecessorVertex[end]<<", ";
  		}
  		// This function is a variation of DFSUytil()
  		bool isCyclicUtil(Comparable v, bool visited[],bool recStack[])
  		{
  			// Mark the current node as visited and part of recursion stack
  			if(visited[v]==false)
  			{
  				visited[v]=true;
  				recStack[v]=true;

  				// Recur for all the vertices adjacent to this vertex
  				typename list<pair<Comparable,double>>::iterator i;
  				for(i=adjList[v].begin();i!=adjList[v].end();++i)
  				{
  					if(!visited[(*i).first]&& isCyclicUtil((*i).first,visited,recStack))
  						return true;
  					else if(recStack[(*i).first])
  						return true;
  				}
  			}
  			recStack[v]=false;
  			return false;
  		}
  		// Returns true if the graph contains a cycle, else false.
  		bool isCyclic()
  		{
  			// Mark all the vertices as not visited and not part of recursion stack
    	
  			bool *visited = new bool[size_];
  			bool *recStack = new bool[size_];
  			for(int i=1;i<=size_;i++)
  			{
  				visited[i]=false;
  				recStack[i]=false;
  			}
  			// Call the recursive helper function to detect cycle in different
    		// DFS trees
  			for(int i=1;i<=size_;i++)
  			{
  				if(isCyclicUtil(i,visited,recStack))
  					return true;
  			}
  			return false;

  		}


  		// A recursive function used by topologicalSort
  		void topologicalSortUtil(Comparable v,bool visited[], stack<Comparable> &Stack)
  		{
  			// Mark the current node as visited
  			visited[v]=true;
  			// Recur for all the vertices adjacent to this vertex
  			typename list<pair<Comparable,double>>::iterator i;
  			for(i=adjList[v].begin();i!=adjList[v].end();++i)
  			{
  				if(!visited[(*i).first])
  					topologicalSortUtil((*i).first,visited,Stack);

  			}
  			// Push current vertex to stack which stores result
  			Stack.push(v);
  		}
  		// The function to do Topological Sort. It uses recursive 
		// topologicalSortUtil()
  		void topologicalSort()
  		{
  			stack<Comparable>Stack;
  			// Mark all the vertices as not visited
  			bool *visited = new bool[size_];
  			for(int i=1;i<=size_;i++)
  				visited[i]=false;
  			// Call the recursive helper function to store Topological
    		// Sort starting from all vertices one by one
    		for(int i=1;i<=size_;i++)
    		{
    			if(visited[i]==false)
    				topologicalSortUtil(i,visited,Stack);
    		}
    		// Print contents of stack
    		while(Stack.empty()==false)
    		{
    			cout<<Stack.top()<<",";
    			Stack.pop();
    		}
        cout<<endl;
  		}
	private:
		list<pair<Comparable,double>> *adjList;
		size_t size_;

};
#endif /*ADJACENCY_LIST_H*/