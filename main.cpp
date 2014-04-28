//*************************************************
// Name			: Nicholas Warner
// Date			: 9 April 2014
// Subject		: CSCE 221-501
// Assignment	: Assignment 6
// Copyright	: Nicholas Warner
// Updated		: 27 April 2014
// Description	: Implementation of Graphs, heaps,
//				: Priority Queues and Dijkstra's
//				: Algorithm
// File			: main.cpp
//*************************************************

#include <iostream>
#include <string>
#include "PriorityQueue.h"
#include "Graph.h"
using namespace std;

void pathFrom( int source , int dest , vector<Vertex>& path )
{
	int weight = path[ dest - 1 ].getWeight();
	cout << path[ dest - 1 ].getID() << " ---(" << path[ dest - 1 ].getWeight() << ")---> " << path[ dest  - 1].getParentID() << "\n";
	while ( path[ dest - 1 ].getParentID() != source )
	{
		dest = path[ dest - 1 ].getParentID();
		cout << path[ dest - 1 ].getID() << " ---(" << path[ dest - 1 ].getWeight() << ")---> " << path[ dest - 1 ].getParentID() << "\n";
	}
	cout << "Total Weight: " << weight << "\n";
}

void printShortestPaths( vector<Vertex>& path )
{
	for ( unsigned int i = 0; i < path.size(); ++i )
	{
		cout << path[ i ].getParentID() << " ---(" << path[ i ].getWeight() << ")---> " << path[ i ].getID() << "\n";
	}
	cout << "\n";
}

void Dijkstra( Graph& G , vector<Vertex>& path , int source )
{
	PriorityQueue<Vertex> Q;
	path.resize( G.size() );

	Vertex v( source , G.getVertexAtID( source )->getInEdges() , G.getVertexAtID( source )->getOutEdges() , 0 );
	v.setParent( source );
	Q.insert( 0 , v );
	path[ v.getID() - 1 ] = v;

	while ( !Q.isEmpty() )
	{
		v = Q.removeMin();
		for ( unsigned int i = 0; i < v.getOutEdges().size(); ++i )
		{
			if ( v.getOutEdgeAt( i )->getEndVertex()->getWeight() > v.getWeight() + v.getOutEdges()[ i ]->getWeight() )
			{
				v.getOutEdgeAt( i )->getEndVertex()->setParent( v.getID() );
				v.getOutEdgeAt( i )->getEndVertex()->changeWeight( v.getWeight() + v.getOutEdges()[ i ]->getWeight() );
				Q.insert( v.getOutEdgeAt( i )->getEndVertex()->getWeight() , *v.getOutEdgeAt( i )->getEndVertex() );
				path[ v.getOutEdgeAt( i )->getEndVertex()->getID() - 1 ] = *v.getOutEdgeAt( i )->getEndVertex();
			}
		}
	}
	cout << "Total Comparisons: " << Q.getComps() << "\n\n";
}

int main()
{   
	// 4 different test files for this project
	//string str( "random_sparse.txt" );	
	//string str( "test.txt" );
	//string str( "test2.txt" );
	string str( "test3.txt" );

	Graph graph( str );						// our graph
	//graph.PrintGraph();						// Prints Vertices with their associated weights and adjacent vertices

	vector<Vertex> path;					// to keep track of the path
	Dijkstra( graph , path , 1 );			// finds the shortest path between the source and all vertices
	printShortestPaths( path );				// prints the shortest paths
	
	cout << "Path from 1 to 2.\n";			// ease of testing for given demo instructions
	pathFrom( 1 , 2 , path );
	
	cout << "\nPath from 1 to 3.\n";
	pathFrom( 1 , 3 , path );
	
	cout << "\nPath from 1 to 4.\n";
	pathFrom( 1 , 4 , path );
	
	cout << "\nPath from 1 to 5.\n";
	pathFrom( 1 , 5 , path );

	int source = 0;
	int dest = 0;
	while ( true )
	{
		cout << "\nHit control + c (windows) or control + d (linux) to exit loop\n";
		cout << "Source: ";
		cin >> source;
		while ( cin.fail() )
		{
			cin.clear();
			cin.ignore( 1024 , '\n' );
			cout << "Incorrect Input. Try again. Source: ";
			cin >> source;
		}
		cout << "Destination: ";
		cin >> dest;
		while ( cin.fail() )
		{
			cin.clear();
			cin.ignore( 1024 , '\n' );
			cout << "Incorrect Input. Try again. Destination: ";
			cin >> dest;
		}
		cout << "\nPath from " << source << " to " << dest << ":\n";
		pathFrom( source , dest , path );
	}
	return 0;
}