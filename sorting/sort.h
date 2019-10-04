#include <vector>

using namespace std;
#define MIN( n, m ) ((n <= m) ? (n) : (m));
 
template< class T >
void piksrt( vector< T > &arr )
//--- sort an array[0...n-1] into ascending orderby straight insertion
{
	int i,j,k, n = arr.size();
	T a;
	for( i = 0; i < n; i++ ) //--- pick out each element in turn
	{
		j = i;
		a = arr[ j ];
		while( a < arr[ j - 1 ] and j > 0 ) //--- look for the place to insert it 
		{
			arr[ j ] = arr[ j - 1 ];
			arr[ j - 1 ] = a;
			j--;
			for( k = 0; k < n; k++ ) 
				printf("%d\t",arr[k]);
			printf("\n");
		}
		assert ( a >= arr[ j - 1 ] || j <= 0 );
		arr[ j ] = a;
	} 
}
//---
template < class T >
void shell( vector< T > &arr )
{
//--- sort an array[0...n-1] into ascending order by shell's method 
	int k, j, i, n = arr.size();
	T a;
	int offset = n; //--- determine the starting increment

	while( offset > 0 )
	{
	offset /= 2; 
	for( k = 0; k < offset; k++ ) //--- loop over partial sorts
	{
		for( j = k; j < n; j += offset ) //--- outer loop of straight insertion
		{
			a = arr[ j ]; 
			i = j;
			while( a < arr[ i - offset ] && i - offset >= 0 ) //--- inner loop of straight insertion
			{
				arr[ i ] = arr[ i - offset ];
				i -= offset;
			}
			arr[ i ] = a;
		}
	}
	}
}
//-- utility function
template< class T >
void SWAP( T &a, T &b )
{
	T temp = a;
	a = b;
	b = temp; 
}
//---
template< class T >
struct quickSort {
//--- sort an array[0...n-1] into ascending order by quick sort method 
	quickSort( vector< T > &array ):arr( array ) {};
	vector< T > &arr;
	void sortSubArrs( int l, int ir )
	{
		int mid, i, j;
		T a;
		if( ir <= l + 1 ) //--- active partition contains 1 or 2 elements
		{
			if( ir == l + 1 && arr[ ir ] < arr[ l ] ) //--- case of 2 elements
				SWAP( arr[ l ], arr[ ir ] );
			return; 
		}
		else	
		{	
			mid = ( l + ir ) >> 1; 		 	  //--- choose median of left, center, and right elements
			SWAP( arr[ mid ], arr[ l + 1 ] ); //--- as partitioning element a. Also rearrange so that arr[l]<arr[l+1],
			if( arr[ l ] > arr[ ir ] )        //--- arr[ ir ] > arr[ l + 1 ]
				SWAP( arr[ l ], arr[ ir ] );
			if( arr[ l + 1 ] > arr[ ir ] )       
				SWAP( arr[ l + 1 ], arr[ ir ] );
			if( arr[ l ] > arr[ l + 1 ] )        
				SWAP( arr[ l ], arr[ l + 1 ] );
		i = l + 1; //--- initialize ptrs for partitioning
		j = ir;
		a = arr[ l + 1 ];  //--- partitioning element
		for(;;) //--- beginning of innermost loop
		{
			do i++; while( arr[ i ] < a ); //--- scan up to find element > a
			do j--; while( arr[ j ] > a ); //--- scan down to find element < a
			if( i > j )
				break; //--- ptrs crossed
			SWAP( arr[ i ], arr[ j ] );
		} //--- end of innermost loop
		arr[ l + 1 ] = arr[ j ]; //--- insert partitioning element
		arr[ j ] = a; 

		sortSubArrs( l, j - 1 );
		sortSubArrs( i, ir );
//		if( j >= k )
//			ir = j - 1; //--- keep active the partition that contains the 
//		if( j <= k )    //--- kth element
//			l = i;	
		}
	
	}
};
//--
template< class T >
T select( const int k, vector< T > &arr )
{
//--- given k in [0..n-1] returns an array value from arr[0..n-1] such that arr[0:k-1]<arr[k]<arr[k+1:n-1].
//--- the input array will be rearranged to have this value in index k.
	int i, ir, j, l, mid, n = arr.size();
	T a;
	l = 0;
	ir = n - 1;
	for(;;)
	{
		if( ir <= l + 1 ) //--- active partition contains 1 or 2 elements
		{
			if( ir == l + 1 && arr[ ir ] < arr[ l ] ) //--- case of 2 elements
				SWAP( arr[ l ], arr[ ir ] );
			return arr[ k ]; 
		}
		else
		{	
			mid = ( l + ir ) >> 1; 		 	  //--- choose median of left, center, and right elements
			SWAP( arr[ mid ], arr[ l + 1 ] ); //--- as partitioning element a. Also rearrange so that arr[l]<arr[l+1],
			if( arr[ l ] > arr[ ir ] )        //--- arr[ ir ] > arr[ l + 1 ]
				SWAP( arr[ l ], arr[ ir ] );
			if( arr[ l + 1 ] > arr[ ir ] )       
				SWAP( arr[ l + 1 ], arr[ ir ] );
			if( arr[ l ] > arr[ l + 1 ] )        
				SWAP( arr[ l ], arr[ l + 1 ] );
		i = l + 1; //--- initialize ptrs for partitioning
		j = ir;
		a = arr[ l + 1 ];  //--- partitioning element
		for(;;) //--- beginning of innermost loop
		{
			do i++; while( arr[ i ] < a ); //--- scan up to find element > a
			do j--; while( arr[ j ] > a ); //--- scan down to find element < a
			if( i > j )
				break; //--- ptrs crossed
			SWAP( arr[ i ], arr[ j ] );
		} //--- end of innermost loop
		arr[ l + 1 ] = arr[ j ]; //--- insert partitioning element
		arr[ j ] = a; 
		if( j >= k )
			ir = j - 1; //--- keep active the partition that contains the 
		if( j <= k )    //--- kth element
			l = i;	
		}
	}
}
//---
namespace hpsort_util
{
	template< class T >
	void sift_down( vector< T > &ra, const int l, const int r )
	{
	//--- carry out the sift-down on element ra(l) to maintain the heap structure. 
	//--- l and r determine the left and right range of the sift-down
		int j, jold;
		T a;
		a = ra[ l ];
		jold = l;
		j = 2 * l + 1;
		while( j <= r )
		{
			if( j < r && ra[ j ] < ra[ j + 1 ] ) //--- compare to the better underling
				j++;
			if( a >= ra[ j ] ) //--- found a's level. Terminate the sift-down.
				break;
			ra[ jold ] = ra[ j ]; //--- otherwise, demote a and continue
			jold = j;
			j = 2 * j + 1;
		}
		ra[ jold ] = a; //--- put a into its slot
	}
}
//---
template< class T >
void hpsort( vector< T > &ra )
{
	//--- sort an array ra[0...n-1] ( in ascending order) using heapsort.
	//--- ra is replaced on output by its sorted reaarangement
	int i, n = ra.size();
	for( i = n / 2 - 1; i >= 0; i-- )
	//--- the index i, which here determines the 'left' range of the sift-down, i.e., the element
	//--- to  be sifted down, is decremented from n /2 - 1 down to 0 during the 'hiring' (heap ceation) phase.
		hpsort_util::sift_down( ra, i, n - 1);
	for( i = n - 1; i > 0; i-- )
	{
	//--- here the 'right' range of the sift-down is decremented from n - 2 down to 0 during 
	//--- the 'retirement-and-promotion' (heap selection) phase.
		SWAP( ra[ 0 ], ra[ i ]); 			   //--- clear a space at the end of the array, and retire
		hpsort_util::sift_down( ra, 0, i - 1); //--- the top of the heap to it. 
	}
}
//---
template < typename  T >
struct HeapSelect
{
	//--- object for tracking the m largest values seen thus far in a stream of values
	int m, n, srtd;
	vector< T > heap; 

	//--- constructor: the argument is the number of largest values to track
	HeapSelect( int mm ): m( mm ), n( 0 ), srtd( 0 ), heap( mm, (T)(1.e99) ) {} 

	void add( T val )
	{
	//--- assimilate a new value from the stream
		int j, k;
		if( n < m ) //--- heap not yet filled
		{
			heap[ n++ ] = val; 
			if( n == m ) { 
				quickSort< T > sort_obj( heap );
				sort_obj.sortSubArrs( 0, heap.size() - 1 );
//				sort( heap ); //--- create initial heap by overkill!
			}
		}
		else
		{
			if( val > heap[ 0 ] ) //--- put it on the heap?
			{
				heap[ 0 ] = val;
				for( j = 0;;) //--- sift down
				{
					k = ( j << 1 ) + 1;
					if( k > m - 1 )
						break;
					if( k != ( m - 1 ) && heap[ k ] > heap[ k + 1 ] )
						k++;
					if( heap[ j ] <= heap[ k ] )
						break;
					swap( heap[ k ], heap[ j ]);
					j = k;
				}
			}
			n++;
		}
		srtd = 0; //--- mark heap as "unsorted"
	}

	T report( int k )
	{
	//--- return the kth largest value seen so far. k=0 return the largest, k = 1 the 2nd largest
	//--- k =m-1 the last position tracked. 
		int mm = MIN( n, m );
		if( k > mm - 1 ) throw( "heapselect k too big" );
		if( k == m - 1 ) return heap[ 0 ]; //--- always free, since top of heap
		if( !srtd ) { 
			quickSort< T > sort_obj( heap );
			sort_obj.sortSubArrs( 0, heap.size() - 1 );
//			sort( heap ); 
			srtd = 1; 
		} //--- otherwise, need to sort the heap
		return heap[ mm - 1 - k ];
	}
};
