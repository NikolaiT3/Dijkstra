//*************************************************
// Name			: Nicholas Warner
// Date			: 9 April 2014
// Subject		: CSCE 221-501
// Assignment	: Assignment 6
// Copyright	: Nicholas Warner
// Updated		: 27 April 2014
// Description	: Implementation of a Graph's
//				: Vertex
// File			: Edge.h
//*************************************************

#ifndef VERTEX_H
#define VERTEX_H

#include <vector>
#include <climits>
#include "Edge.h"

using namespace std;

class Graph;
class Edge;

class Vertex
{
private:
	vector<Edge*> inList;	// source vertex
	vector<Edge*> outList;	// end vertex 
	int id;					// vertex name
	int weight;				// the total weight of the vertex, initially INT_MAX. To be changed by starting at a given source			
	int parentID;			// the parent vertex of this vertex as a path is computed
	friend class Graph;

public:
	// overloaded contructors
	Vertex( int sid = 0 , int weit = INT_MAX  ) :
		id( sid ) , weight( weit ) , parentID( 0 )
	{
	}
	Vertex( int sid , vector<Edge*> in , vector<Edge*> out , int weit = INT_MAX ) :
		id( sid ) , weight( weit ) , inList( in ) , outList( out ) , parentID( 0 )
	{
	}

	// copy constructor
	Vertex( const Vertex& v )
	{
		id = v.getID();
		inList = v.getInEdges();
		outList = v.getOutEdges();
		weight = v.getWeight();
		parentID = v.getParentID();
	}
	// assignment operator
	Vertex& operator=( const Vertex& v )
	{
		id = v.getID();
		inList = v.getInEdges();
		outList = v.getOutEdges();
		weight = v.getWeight();
		parentID = v.getParentID();
		return *this;
	}

	vector<Edge*> getOutEdges() const
	// return the vector of out edges
	{
		return outList;
	}
	Edge* getOutEdgeAt( int i )
	// return a specific out degree
	{
		return outList[ i ];
	}
	vector<Edge*> getInEdges() const
	// return the vector of in edges
	{
		return inList;
	}
	int getID() const
	// get vector name (ID)
	{
		return id;
	}
	int getWeight( void ) const
	// return vertex weight
	{
		return weight;
	}
	int getParentID() const
	// get parent vertex name (ID)
	{
		return parentID;
	}
	void setParent( int v )
	// change the parent vertex
	{
		parentID = v;
	}
	void changeWeight( int w )
	// change vertex weight
	{
		weight = w;
	}
	int outEdgeSize()
	// size of out edges vertex
	{
		return outList.size();
	}
	int inEdgeSize()
	// size of in edges vertex
	{
		return inList.size();
	}
	int weightEdgeAt( int n )
	// get a specific edge's weight
	{
		return outList[ n ]->getWeight();
	}
	void changeWeightAtEdge( int n , int w )
	// change a specific edge's weight
	{
		outList[ n ]->changeWeight( w );
	}
	Vertex* adjacentTo( int id , int adjacentID )
	{
		for ( unsigned int i = 0; i < outList.size(); ++i )
		{
			if ( outList[ i ]->getEndVertex()->getID() == adjacentID )
			{
				return outList[ i ]->getEndVertex();
			}
		}
	}
};
#endif