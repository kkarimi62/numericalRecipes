#ifndef HASH_H
#define HASH_H

typedef unsigned long long Ullong;
typedef unsigned int Uint;

#include "vector"
using namespace std;

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
//--- 
template< class keyT, class hfnT > struct Hashtable
{
//--- instantiate a hash table, with methods for maintaining a one-to-one correspondence between
//--- arbitrary keys and unique integers in a specified range.
	int nhash, nmax, nn, ng;
	vector< int > htable, next, garbg;
	vector< Ullong > thehash;
	hfnT hash; //--- an instance of a hash function object	
//	vector< listNode< > > arrLinkdList; //--- array containing linked lists
	Hashtable( int nh, int nv ); 
	//--- constructor. Args are the size of hash table and max number of stored elements (keys)
	int iget( const keyT &key ); //--- Return integer for a previous set key
	int iset( const keyT &key ); //--- Return unique integer for a new key
	int ierase( const keyT &key ); //--- Erase a key
	int ireserve(); //--- Reserve an integer (with no key)
	int irelinquish( int k ); //--- Un-reserve an integer
};

template< class keyT, class hfnT > 
Hashtable< keyT, hfnT >::Hashtable( int nh, int nv ): hash( sizeof( keyT ) ), nhash( nh ), nmax( nv ), 
nn( 0 ), ng( 0 ), htable( nh ), next( nv ), garbg( nv ), thehash( nv ) 
{
//--- constructor. Set nhash, the size of hash table, and nmax, max number of stored elements (keys)
//--- that can be accommodated. Allocate arrays appropriately
	for( int j = 0; j < nh; j++ )
		htable[ j ] = -1; //--- signifies empty
}

template< class keyT, class hfnT >
int Hashtable< keyT, hfnT >::iget( const keyT &key )
{
//--- Returns integer in 0..nmax-1 corresponding to key, or -1 if no such key was previously stored.
	int j,k ;
	Ullong pp = hash.fn( &key ); //--- get 64-bit integer
	j = ( int ) ( pp % nhash );  //--- and map it into the hash table.
	for( k = htable[ j ]; k != -1; k = next[ k ] ) //--- traverse the linked list until an excat match is found 
	{
		if( thehash[ k ] == pp )
			return k;	
	}
	return -1; //--- key wasn't previously stored
}

template< class keyT, class hfnT >
int Hashtable< keyT, hfnT >::iset( const keyT &key )
{
//--- Returns integer in 0..nmax-1 corresponding to key. if key wasn previously set, return the same integer as before. 
	int j, k, kprev;
	Ullong pp = hash.fn( &key ); //--- get 64-bit hash
	j = ( int ) ( pp % nhash );  //--- map into the hash table
	if( htable[ j ] == -1 )      //--- key not in the table: find a free integer, either new or previously erased.  
	{
		k = ng ? garbg[ --ng ] : nn++;
		htable[ j ] = k;
	}
	else 						 //--- key might be in table. Traverse list. 
	{
		for( k = htable[ j ]; k != -1; k = next[ k ] ) //--- traverse the linked list until an excat match is found 
		{
			if( thehash[ k ] == pp )
				return k;		//--- Yes. Return previous vlue
			kprev = k;
		}
		k = ng ? garbg[ --ng ] : nn++; //--- no. get new integer
		next[ kprev ] = k;
	}
	if( k >= nmax )
		throw( "storing too many values" );
	thehash[ k ] = pp; //--- store the key at the new or previous integer.
	next[ k ] = -1;
	return k;
}

template<class keyT, class elT, class hfnT>
struct Hash : Hashtable<keyT, hfnT> {
//--- Extend the Hashtable class with storage for elements of type elT, and
//--- provide methods for storing, retrieving. and erasing elements. 
//--- key is passed by address in all methods.
	using Hashtable<keyT, hfnT>::iget;
	using Hashtable<keyT, hfnT>::iset;
	using Hashtable<keyT, hfnT>::ierase;
	vector< elT > els;

	Hash( int nh, int nm ): Hashtable<keyT, hfnT>(nh, nm), els( nm ) {} //--- same constructor as Hashtable

	void set( const keyT &key, const elT &el ) //--- Store an element el
	{
	//--- Store an element el.
		els[ iset( key ) ] = el; 
	}

	int get( const keyT &key, const elT &el ) {
	//--- Retrieve an element into el. Returns 0 if no element is stored under key, or 1 for success.
		int ll = iget( key );
		if( ll < 0 ) return 0;
		el = els[ ll ];
		return 1;
	}
		
	elT& operator[]( const keyT& key ) {
	//--- Store or retrieve an element using subscript notation for its key. 
	//--- Returns a reference that can be used as an l-value.
		elT el;
		bool exist = get( key, el );
		if( !exist ) 
			throw( "no element is stored under key" );
		return el;
	}

	int count(const keyT &key) {
	//--- Return the number of elements stored under key, that is, either 0 or 1. Int ll = iget(key);
		int ll = iget(key);
		return (ll < 0 ? 0 : 1);
	}

	int erase(const keyT &key) {
	//--- Erase an element. Returns 1 for success, or 0 if no element is stored under key. 
	return (ierase(key) < 0 ? 0 : 1);
	} 
};
#endif
