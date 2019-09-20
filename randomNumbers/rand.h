#ifndef RAND_H
#define RAND_H

typedef unsigned long long Ullong;
struct Ran
{
//--- implementation of random number generator with the period is ~ 3x10^57
	Ullong u, v, w;
	//--- constructor call with an integer seed 
	Ran( Ullong j ) : v( 4101842887655102017LL ), w( 1 ) 
	{
		u = j ^ v; int64();
		v = u; int64();
		w = v; int64();	
	}
	//--- return 64-bit random integer
	inline Ullong int64()
	{
		u = u * 2862933555777941757LL + 7046029254386353087LL;
		v ^= v >> 17; v ^= v << 31; v ^= v >> 8;
		w = 4294957665U * ( w & 0xffffffff ) + ( w >> 32 ) ;
		Ullong x = u ^ ( u << 21 ); x ^= x >> 35; x ^= x << 4;
		return ( x + v ) ^ w;
	}
	//--- return double precision random number in the range 0 to 1 
	inline double doub() { return int64() * 5.421010862427522e-20; }; //--- int / maxint 
	//--- 32-bit random integer
	inline int int32() { return int64() % 4294967295; }; 
};

#endif
