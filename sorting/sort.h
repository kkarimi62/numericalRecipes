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
//--- sort an array[0...n-1] into ascending order by shell's method 
void shell( vector< T > &arr )
{
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
