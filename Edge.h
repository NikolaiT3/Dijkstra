//*************************************************
// Name			: Nicholas Warner
// Date			: 9 April 2014
// Subject		: CSCE 221-501
// Assignment	: Assignment 6
// Copyright	: Nicholas Warner
// Updated		: 27 April 2014
// Description	: Implementation of a Graph's
//				: Edge
// File			: Edge.h
//*************************************************

#include "Vertex.h"

#ifndef EDGE_H
#define EDGE_H

#include <iostream>
#include <vector>

using namespace std;

class Vertex;

class Edge
{
private:
	Vertex *sourceVertex;	// source vertex pointer
	Vertex *endVertex;		// end vertex pointer
	int weight;				// edge weight 

public:
	// contructors
	Edge();
	Edge( Vertex* svert , Vertex* evert , int weit ) :
		sourceVertex( svert ) , endVertex( evert ) , weight( weit )
	{
	}

	int getWeight() const
	// get edge weight
	{
		return weight;
	}
	void changeWeight( int n )
	// change the edge weight
	{
		weight = n;
	}
	Vertex* getSourceVertex() const
	// get the vertex the edge branches from
	{
		return sourceVertex;
	}
	Vertex* getEndVertex() const
	// get the vertex the edge goes to
	{
		return endVertex;
	}
};
#endif