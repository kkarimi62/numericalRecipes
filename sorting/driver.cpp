#include "sort.h"
#include <vector>
#include "stdio.h"

using namespace std;

int main()
{
	vector<int> v = {-3,0,-4,5,-10,-11,-2,1,3,2,-1};
	for( int i = 0; i < v.size(); i++ ) 
		printf("%d\t",v[i]);
//	shell( v );
//	piksrt( v );
//	printf("\n");
//	for( int i = 0; i < v.size(); i++ ) 
//		printf("%d\t",v[i]);
//	vector<int> u = v;
	int k = select( ( v.size() - 1 ) / 2, v );
	printf("\n");
	for( int i = 0; i < v.size(); i++ ) 
		printf("%d\t",v[i]);
	printf("\nmedian=%d\n",k);
	return 0;
}
