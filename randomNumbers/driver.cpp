#include "rand.h"
#include "hash.h"
#include "stdio.h"

int main()
{
//	Ran myRan( 40 );
//	RanHash myRan;
//	printf("random hash=%f\n",myRan.doub( 100 ) );
//	for( int i = 0; i < 100; i++ )
//		printf( "x=%f\n",myRan.doub() );
//	int x = 10;
	double x = 10.0;
	char *xstr="kamran";
	Hashfn2 myHash( sizeof( xstr ) );
	printf( "hash=%llu\n", myHash.fn( xstr ) ); 
	return 0;
}
