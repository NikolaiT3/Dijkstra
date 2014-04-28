//*************************************************
// Name			: Nicholas Warner
// Date			: 9 April 2014
// Subject		: CSCE 221-501
// Assignment	: Assignment 6
// Copyright	: Nicholas Warner
// Updated		: 27 April 2014
// Description	: Implementation of a Priority Queue
//				: Vertex
// File			: PriorityQueue.h
//*************************************************

#ifndef PRIORITYQUEUE_H_
#define PRIORITYQUEUE_H_

#include <cstdlib>
#include <iostream>
#include <string>
#include <stdexcept>
#include "BinaryHeap.h"

using namespace std;

struct EmptyPriorityQueue : std::range_error
// a standard out of range error
{
	explicit EmptyPriorityQueue( char const* msg = NULL ) : range_error( msg )
	{
	}
};

template< typename ElemType >
class Item
{
private:
	int key;		// distance to the particular vertex
	ElemType elem;	// the vertex
	int locIndex;	// locators are implemented based on the vertex's name (ID), as it corresponds to it's vector position

public:
	// constructors
	Item() 
		: elem() , key( 0 ) , locIndex( -1 ) { }
	Item( ElemType& e , const int k = 0 , int l = -1 )
		: key( k ) , elem( e ) , locIndex( l ) { }

	int Key() const
	// get key (distance)
	{
		return key;
	}
	ElemType Element() const
	// get element (vertex)
	{
		return elem;
	}
	int LocIndex() const	// not necessary. locators are implemented here based on the vertex's name (ID), as it corresponds to it's vector position
	// get locator
	{
		return locIndex;
	}
	void setKey( const int k )
	// change key (distance)
	{
		key = k;
	}

};

template<typename ElemType>
class PQComp
{
public:
	int operator()( const Item<ElemType>& x , const Item<ElemType>& y )
	// compare two item's to be stored in the minimum heap
	{
		return x.Key() - y.Key();
	}
};

template< typename ElemType >
class PriorityQueue
{
protected:
	typedef Item<ElemType> _Item;		// ease of use for Item and PQComp types
	typedef PQComp<ElemType> _PQComp;

private:
	static const int DEF_SIZE = 500;	// default size
	BinaryHeap< _Item , _PQComp> heap;	// the underlying implementation of the priority queue

public:
	// constructor
	PriorityQueue( int size = DEF_SIZE )
		: heap( size ) { }

	bool isEmpty()
	// test whether the priority queue is empty
	{
		return heap.isEmpty();
	}
	int size()
	// size of priority queue
	{
		return heap.size();
	}
	void insert( const int k , ElemType& e , int locIndex = 0 )
	// insert an element into the priority queue
	{
		heap.insert( _Item( e , k , locIndex ) );
	}
	ElemType removeMin() throw( EmptyPriorityQueue )
	// return the minimum and delete it from the priority queue
	{
		return heap.deleteMin().Element();
	}
	ElemType getAtLocator( int id )
	// get a specific element in the priority queue
	{
		return heap.getAtLocator( id ).Element();
	}
	int minKey() throw( EmptyPriorityQueue )
	// get the element with the smallest key
	{
		if ( heap.isEmpty() )
			throw EmptyPriorityQueue();
		return heap.findMin().Key();
	}
	ElemType minElement() throw( EmptyPriorityQueue )
	// get the minimum element without deletion
	{
		if ( heap.isEmpty() )
			throw EmptyPriorityQueue();
		return heap.findMin().Element();
	}
	void replaceKey( int id , int k )
	// replace key of a specific element
	{
		heap.replaceKey( id , k );
	}
	void remove( int id )
	// remove a specific element
	{
		heap.remove( id );
	}
	BinaryHeap<_Item , _PQComp>& getHeap()
	// return the underlying heap structure
	{
		return heap;
	}
	int getComps()
	// return number of comparisons the heap has made so far
	{
		return heap.getComps();
	}
};

template< typename ElemType >
ostream& operator<<( ostream& out , Item<ElemType>& item )
// overloaded output operator to display an Item type
{
	out << item.elem;
	return out;
}

template<typename T>
ostream& operator << ( ostream& out , PriorityQueue<T> pq )
// overloaded output operator to display a PriorityQueue type
{
	out << pq.getHeap();
	return out;
}
#endif