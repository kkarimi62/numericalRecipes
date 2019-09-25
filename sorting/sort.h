#include <vector>

using namespace std;
 
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

