#include "sort.h"
#include <vector>
#include "stdio.h"

using namespace std;

int main()
{
	vector<int> v = {7,5,16,10,8,1,3,15,23,9,6,4,-3,0,-1,-2,-10,-9,-7};
	for( int i = 0; i < v.size(); i++ ) 
		printf("%d\t",v[i]);
	shell( v );
//	piksrt( v );
	printf("\n");
	for( int i = 0; i < v.size(); i++ ) 
		printf("%d\t",v[i]);
	return 0;
}
