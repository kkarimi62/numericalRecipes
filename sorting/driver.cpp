#include "sort.h"
#include <vector>
#include "stdio.h"

using namespace std;

int main()
{
	vector<int> v = {-4,-3,0,5,-10,-11,-2,1,3,2,-1};
	for( int i = 0; i < v.size(); i++ ) 
		printf("%d\t",v[i]);
	printf("\n");
//	shell( v );
//	piksrt( v );
//	printf("\n");
//	for( int i = 0; i < v.size(); i++ ) 
//		printf("%d\t",v[i]);
//	vector<int> u = v;
//	int k = select( ( v.size() - 1 ) / 2, v );
//	printf("\n");
//	hpsort( v );	
//	for( int i = 0; i < v.size(); i++ ) 
//		printf("%d\t",v[i]);
//	printf("\nmedian=%d\n",k);
	quickSort<int> sort_obj( v );
	sort_obj.sortSubArrs( 0, v.size() - 1 );	
	for( int i = 0; i < v.size(); i++ ) 
		printf("%d\t",v[i]);
	printf("\n");
	return 0;
}
