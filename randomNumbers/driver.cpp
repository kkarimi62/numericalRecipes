#include "rand.h"
#include "stdio.h"

int main()
{
	Ran myRan( 40 );
	for( int i = 0; i < 100; i++ )
		printf( "x=%f\n",myRan.doub() );
	return 0;
}
