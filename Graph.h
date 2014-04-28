//*************************************************
// Name			: Nicholas Warner
// Date			: 9 April 2014
// Subject		: CSCE 221-501
// Assignment	: Assignment 6
// Copyright	: Nicholas Warner
// Updated		: 27 April 2014
// Description	: Implementation of a Graph
// File			: Graph.h
//*************************************************

#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Vertex.h"
#include "Edge.h"

using namespace std;

class Edge;
class Vertex;

class Graph
{
private:
	vector<Vertex*> vertList;		// all the graph's vertices
	vector<Edge*> edgeList;			// all the graph's edges
	int numVert;					// total number of vertices

public:
	Graph( string filename );		// constructor
	~Graph();						// destructor

	int size()
	// graph size
	{
		return numVert;
	}
	void addEdge( Vertex* source , Vertex* end , int weit )
	// insert a new edge into the graph
	{
		edgeList.push_back( new Edge( source , end , weit ) );
	}
	void addVertex( int id )
	// insert a new vertex into the graph. ID should be the inserted index + 1
	{
		vertList.push_back( new Vertex( id ) );
	}
	int numEdges()
	// total number of edges in the graph
	{
		return edgeList.size();
	}
	vector<Vertex*> getVertices() const
	// return a list of all vertices
	{
		return vertList;
	}
	Vertex* getVertexAtID( int id )
	// Get a specific vertex by locator
	{
		if ( id != 0 )
			return vertList[ id - 1 ];
		else
		{
			cerr << "Bad ID\n";
			return vertList[ 0 ];
		}
	}

	void PrintGraph();									// print the graph to the screen in command line format
	Edge& insertEdge( Vertex* v , Vertex* w , int x );	// insert and return a new undirected edge with end vertices v and w, storing element (weight) x
	Vertex& insertVertex( int x );						// insert and edge with id x
};

Graph::Graph( string filename )
// constructor
{
	ifstream ifs( filename.c_str() );
	int vertnum;
	ifs >> vertnum;						// first number in file, says how many data lines there are
	numVert = vertnum;
	for ( int i = 0; i < vertnum; i++ ) // push all vertices into the vertex vector before assigning the in and out list
	{
		Vertex *vert = new Vertex( i + 1 );
		vertList.push_back( vert );
	}

	int svert , evert , weit;
	ifs >> svert;						// based on first number in each line

	while ( svert != -1 )				// insert edges into the Edge vector so long as first number isn't -1
	{
		ifs >> evert;					// grab second number in line, this is an adjacent vertex
		while ( evert != -1 )
		{
			ifs >> weit;				// one weight means one edge // grab third number, this is the weight (grabs every other number until evert is -1)
			Edge *tempedge = new Edge( vertList[ svert - 1 ] , vertList[ evert - 1 ] , weit ); // new edge
			edgeList.push_back( tempedge );
			vertList[ svert - 1 ]->outList.push_back( tempedge );
			vertList[ evert - 1 ]->inList.push_back( tempedge );
			ifs >> evert;				// grabs the fourth number, then every other number after, this is the adjacent vertex
		}
		ifs >> svert;					// based on first number in each line
	}
	ifs.close();
}

Graph::~Graph()
// destructor
{
	for ( unsigned int i = 0; i < vertList.size(); i++ )
		delete vertList[ i ];
	for ( unsigned int i = 0; i < edgeList.size(); i++ )
		delete edgeList[ i ];
}

void Graph::PrintGraph()
// print out all the edges and associated vertices in the entire graph
{
	for ( unsigned int i = 0; i < vertList.size(); ++i )
	{
		cout << "Vertex: " << vertList[ i ]->getID();
		for ( unsigned int j = 0; j < vertList[ i ]->getOutEdges().size(); ++j )
		{
			cout << " | Edge: " << vertList[ i ]->getOutEdges().at( j )->getWeight()
				 << " | Associated Vertex: " << vertList[ i ]->getOutEdges().at( j )->getEndVertex()->getID();
		}
		cout << "\n";
	}
}

Edge& Graph::insertEdge( Vertex* v , Vertex* w , int x )
// insert and return a new undirected edge with end vertices v and w, storing element (weight) x
{
	Edge *tempedge = new Edge( v , w , x );					// new edge
	edgeList.push_back( tempedge );							// add edge to vector
	vertList[ v->getID() ]->outList.push_back( tempedge );	// add to outlist
	vertList[ w->getID() ]->inList.push_back( tempedge );	// add to inlist
	return *tempedge;										// return our inserted edge
}

Vertex& Graph::insertVertex( int x )
// insert and return a new vertex storing element x
{
	Vertex *vert = new Vertex( vertList.size() );	// might throw seg fault (if so, subtract 1)
	vertList.push_back( vert );						// add new vertex to vertList
	return *vert;									// return our inserted vertex
}
#endif