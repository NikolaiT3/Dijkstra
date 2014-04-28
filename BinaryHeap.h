//*************************************************
// Name			: Nicholas Warner
// Date			: 9 April 2014
// Subject		: CSCE 221-501
// Assignment	: Assignment 6
// Copyright	: Nicholas Warner
// Updated		: 27 April 2014
// Description	: Implementation of a
//				: Priority Queue's Binary Heap
// File			: BinaryHeap.h
//*************************************************

#ifndef BINARYHEAP_H_
#define BINARYHEAP_H_

#include "PriorityQueue.h"
#include <stdexcept>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct EmptyHeap : std::range_error
{
	explicit EmptyHeap( char const* msg = NULL ) : range_error( msg )
	// standard empty heap error
	{
	}
};

template< typename T , typename C >		// T = _Item = Item<ElemType>, C = _PQComp = PQComp<ElemType>
class BinaryHeap
{
private:
	static const int DEF_SIZE = 500;	// default size of the heap
	C comp;								// comparator object
	int currentSize;					// the current size of the heap
	int length;							// length of the heap array
	T* array;							// the heap array
	vector<int> locators;				// locators vector (not necessary here, locators are implemented
											// based on the vertex's name (ID), as it corresponds to it's vector position
	int comparisons;					// total number of comparisons made by heap

	void getNewArray( int newSize )
	// allocate more memory for the heap array
	{
		array = new T[ newSize ];
		length = newSize;
	}

	void checkSize()
	// check the size of the heap and, if undersized, expand it
	{
		if ( currentSize == length )
		{
			T *oldArray = array;
			getNewArray( 2 * currentSize );
			for ( int i = 0; i < currentSize; i++ )
			{
				array[ i ] = oldArray[ i ];
			}
			delete[ ] oldArray;
		}
	}

public:
	BinaryHeap( int size = DEF_SIZE )	// constructor
	{
		currentSize = 0;
		getNewArray( size );
		locators.resize( size );
		comparisons = 0;
	}

	bool isEmpty()
	// test whether the heap is empty
	{
		return currentSize == 0;
	}
	T& findMin() throw( EmptyHeap )
	// return the minimum element
	{
		if ( isEmpty() )
			throw EmptyHeap();
		return array[ 0 ];
	}
	T getArray()
	// return the heap array
	{
		return array;
	}
	T getAtLocator( int n ) throw( EmptyHeap )
	// get a specific element 
	{
		return array[ n ];
	}
	int size()
	// return the size of the heap
	{
		return currentSize;
	}
	void replaceKey( int id , int k )
	// replace the key of a specific element
	{
		array[ id ].setKey( k );
		walkDown( id );
	}
	int getComps()
	// return total number of heap comparisons
	{
		return comparisons;
	}
	void buildHeap();							// build the heap from the bottom up
	void insert( const T& n );					// put an element into the heap
	T deleteMin() throw( EmptyHeap );			// return the minimum element and delete it
	void walkDown( int hole );					// walk down the heap, organizing it correctly
	void remove( int id ) throw( EmptyHeap );	// remove a specific element
};


template< typename T , typename C >
void BinaryHeap< T , C >::buildHeap()
// bottom-up heap construction
{
	for ( int i = ( currentSize - 2 ) / 2; i >= 0; i-- ) walkDown( i );
}

template< typename T , typename C >
void BinaryHeap< T , C >::insert( const T& x )
// put an element into the heap
{
	checkSize();
	int hole = currentSize++;
	array[ hole ] = x;
	locators.push_back( hole );
	buildHeap();
}

template<typename T , typename C>
T BinaryHeap< T , C >::deleteMin() throw ( EmptyHeap )
// return the minimum element and delete it
{
	locators[ array[ 0 ].LocIndex() ] = -1;
	T min = array[ 0 ];
	array[ 0 ] = array[ --currentSize ]; // set root to far right child
	walkDown( 0 );
	return min;
}

template< typename T , typename C >	
void BinaryHeap< T , C >::walkDown( int hole )
// walk down the heap, organizing it correctly
{
	int child;
	T key = array[ hole ];
	for ( ; 2 * hole + 1 < currentSize; hole = child ) // walk down
	{
		child = 2 * hole + 1;
		if ( child != currentSize - 1 && ( ++comparisons , comp( array[ child ] , array[ child + 1 ] ) > 0 ) )
		{
			child++;	// right child = 2*hole+2
		}
		if (  ++comparisons , comp( key , array[ child ] ) > 0 )
		{
			array[ hole ] = array[ child ];
		}
		else
		{
			break;
		}
	}
	array[ hole ] = key;

	for ( int i = 0; i < currentSize; ++i )
	{
		locators[ array[ i ].LocIndex() ] = i;
	}
}

template< typename T , typename C >
void BinaryHeap< T , C >::remove( int id ) throw( EmptyHeap )
// remove a specific element
{
	if ( isEmpty() )
	{
		throw EmptyHeap();
	}
	array[ locators[ id ] ] = array[ --currentSize ];
	walkDown( 0 );
}

template< typename T , typename C >
ostream& operator<< ( ostream& out , BinaryHeap< T , C >& bh )
// overloaded output operator to display a BinaryHeap type
{
	for ( int i = 0; i < bh.size(); ++i )
	{
		out << bh.arrayFind( i );
	}
	return out;
}
#endif