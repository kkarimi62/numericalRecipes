#ifndef HASH_H
#define HASH_H

typedef unsigned long long Ullong;
typedef unsigned int Uint;

struct Hashfn1
{ 
	RanHash RanHash_obj;
	int n; //--- size of key in bytes
	Hashfn1( int nn ):n( nn ){} //--- constructor saves the key size
	Ullong fn( const void *keyT ) //--- returns hash from key
	{
		Uint *k;
		Ullong *kk;
		switch ( n )
		{
			case 4:
				k = ( Uint * ) keyT;
				return RanHash_obj.int32( *k ); //--- return 32-bit hash 
			case 8:
				kk = ( Ullong * ) keyT;
				return RanHash_obj.int64( *kk ); //--- return 64-bit hash
			default:
				throw( "Hashfn1 is for 4 or 8 byte keys only." );
		}
	}
};

struct Hashfn2 {
//--- hash function allowing fixed key sizes or variable-length null terminated strings.
//--- the hash function algorithm is self-contained.
	static Ullong hashfn_tab[ 256 ];
	Ullong h;
	int n; //--- size of key in bytes, when fixed size
	Hashfn2( int nn ): n( nn ) {
		if (n == 1) n = 0; //--- null terminated string key signaled by n = 0
		h = 0x544B2FBACAAF1684LL;
		for (int j=0; j<256; j++) { //--- length 256 look-up table initialized  
			for (int i=0; i<31; i++) { //--- with values from a 64-bit generator
				h = (h >>  7) ^ h;		//--- stepped 31 times between each.
				h = (h << 11) ^ h;
				h = (h >> 10) ^ h;
			}
			hashfn_tab[j] = h; 
		}
}
	Ullong fn( const void *key ) { //--- function that returns hash from key
		int j;
		char *k = (char *)key; //--- cast key ptr to char ptr
		h=0xBB40E64DA205B064LL;
		j=0;
		while(n ? j++ < n : *k) { //--- fixed length or else until null
			h = (h * 7664345821815920749LL) ^ hashfn_tab[(unsigned char)(*k)];
			k++;
		}
		return h;
	}
};
Ullong Hashfn2::hashfn_tab[256]; //Defines storage for the lookup table.	
#endif
