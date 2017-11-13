# ifndef NIL
# define NIL ( void *) 0
# endif
# ifndef _BF_H
# define _BF_H
# include <stdint.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>

# include "aes.h"

//Author Prof. Darell Long for the bit vector code 
typedef struct bloomF {
uint8_t *v; // Vector
uint32_t l; // Length
uint32_t s [4]; // Salt
} bloomF ;

// Each function has its own hash function , determined by the salt .
static inline int realLength ( int l)
{
    return 16 * (l / 16 + (l % 16 ? 1 : 0) );
}

//hash function
uint32_t hashBF(bloomF *bFilter ,char *key) 
{
    uint32_t output [4] ={ 0x0 };
    uint32_t sum = 0x0;
    int keyL = strlen(key) ;
    uint8_t * realKey = ( uint8_t *) calloc(realLength(keyL) , sizeof(uint8_t));

    memcpy(realKey, key, keyL) ; 
    for(int i = 0; i < realLength(keyL) ; i += 16)
    {
        AES128_ECB_encrypt (( uint8_t *) bFilter->s, // Salt
        ( uint8_t *) realKey + i, // Input
        ( uint8_t *) output ) ; // Output
        sum ^= output [0] ^ output [1] ^ output [2] ^ output [3];
    }

    free (realKey) ;
    return sum;
}

// Create a new Bloom Filter of a given length and hash function .

static inline bloomF * newBF ( uint32_t l, uint32_t b [])
{
	bloomF *bf = (bloomF *) malloc(sizeof(bloomF));

    bf->v = (uint8_t *) calloc( (l / 8) + 1, sizeof(uint8_t));
    bf->l = l;

    bf->s[0] = b[0];
    bf->s[1] = b[1];
    bf->s[2] = b[2];
    bf->s[3] = b[3];

    return bf;
}

// Delete a Bloom filter

static inline void delBF ( bloomF *v)
{
	free(v->v); free(v);
	return;
}

// Return the value of position k in the Bloom filter

static inline uint32_t valBF ( bloomF *x, uint32_t k)
{
	uint32_t index = ((x->v[k / 8] & (0x1 << k % 8)) != 0);
	return index;
}

static inline uint32_t lenBF ( bloomF *x) { return x->l; }//length of bloom filter is returned

// Count bits in the Bloom filter

static inline uint32_t countBF ( bloomF *b)
{
	uint32_t  ones = 0;
	for(uint32_t i = 0; i < (b->l); i++)
	{
		if(valBF(b, i))
		{
			ones++;
		}
	}

    return ones;
}

// Set an entry in the Bloom filter

static inline void setBF ( bloomF *x, char * key )
{
    uint32_t hashKey = 0;
  
    hashKey = hashBF(x, key);
    uint32_t k = hashKey % (x->l);
	x->v[k / 8] |=  (0x1 << k % 8); 
}

// Clear an entry in the Bloom filter

static inline void clrBF ( bloomF *x, char * key )
{
    uint32_t k = hashBF(x, key);
	x->v[k / 8] &= ~(0x1 << k % 8);
}

// Check membership in the Bloom filter

static inline uint32_t memBF ( bloomF *x, char * key )
{

    uint32_t keyHash = hashBF( x, key);

    uint32_t keyExistsInFilter = valBF(x, keyHash % (x->l));

    return keyExistsInFilter;
}

//prints bloom filter
static inline void printBF ( bloomF *x)
{
   bloomF *y = x;
   y->l = 1000;
}

# endif
