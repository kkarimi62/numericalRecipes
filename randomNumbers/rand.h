#ifndef RAND_H
#define RAND_H

#include "stdio.h"
typedef unsigned long long Ullong;
typedef unsigned int Uint;
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
	inline Uint int32() { return int64() % 4294967295; }; 
};

struct RanHash
{
//--- high-quality random hash of an integer into several numeric types
	inline Ullong int64( Ullong u )
	{
		Ullong v = u * 3935559000370003845LL + 2691343689449507681LL;
		v ^= v >> 21; v ^= v << 37; v ^= v >> 4;
		v *= 4768777513237032717LL;
		v ^= v << 20; v ^= v >> 41; v ^= v << 5;
		return v;
	}
	inline Uint int32( Uint u )
	{
	//--- return hash of u as a 32-bit integer 
		return ( Uint )( int64( u ) & 0xffffffff );
	}
	double inline doub( Ullong u )
	//--- return hash of u as a double in the range 0 to 1 
	{
		return int64( u ) * 5.42101086242752217E-20;
	}
};

#endif
