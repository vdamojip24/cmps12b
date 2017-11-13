# include <stdlib.h>
# include <stdint.h>
# include <string.h>
# include <stdio.h>
# include "aes.h"
# include "hash.h"

static inline int realLength ( int l)
{
    return 16 * (l / 16 + (l % 16 ? 1 : 0) );
}
//hash function that is given
uint32_t hash(hashTable *h, const char * key)
{
    uint32_t output [4] = { 0x0 };
    uint32_t sum = 0x0;
    int keyL = strlen (key) ;
    uint8_t * realKey = (uint8_t *) calloc(realLength(keyL) , sizeof(uint8_t)) ;

    memcpy ( realKey , key , keyL ) ; 
    for ( int i = 0; i < realLength(keyL) ; i += 16)
    {
        AES128_ECB_encrypt (( uint8_t *) h->s, // Salt
        ( uint8_t *) realKey + i, // Input
        ( uint8_t *) output ) ; // Output
        sum ^= output [0] ^ output [1] ^ output [2] ^ output [3];
    }
    free(realKey) ;
    return sum;
}

//creates new hashtable of a specified length
hashTable * newHT ( uint32_t l, uint32_t array[])
{
	hashTable *table = (hashTable *) malloc(sizeof(hashTable));
	table->l = l;
	memcpy(table->s, array, sizeof(uint32_t) * 4);
	table->h = (listNode **) malloc(sizeof(listNode *)*l);
	return table;
}
//deletes hash table and frees up memory
void delHT(hashTable *table)
{
	delLL(*(table->h));
	free(table);
	table = NULL;
}

//finds hash table
listNode * findHT ( hashTable *hTable , const char *key) 
{
    uint32_t keyHash = hash(hTable, key);

    listNode *keyLL = hTable->h[keyHash % hTable->l];

    listNode *keyNode = findLL(&keyLL , key);

    return keyNode;
}

//inserts the keys into the hash tabble
void insertHT(hashTable *hTable , const char *oldKey , const char *newKey) 
{
    uint32_t keyHash = hash(hTable, oldKey);

//    if (keyHash > hTable->l)
//    {
//        printf("Error: key is larger than the hTable size. Consider modulus Length = %u key = %u.\n", hTable->l, keyHash);
//        return ;
//    }
    // listNode *keyLL = hTable->h[keyHash % (hTable->l)];

    insertLL(&(hTable->h[keyHash % (hTable->l)]), (char *)oldKey,(char *) newKey);
}

//prints the hash table
void printHT(const hashTable *ht) 
{
    fprintf(stdout, "%s", "Hash Table Statistics\n");

    fprintf(stdout, "Number of buckets = %u\n", ht->l);
    
    for (uint32_t i = 0; i < ht->l ; ++i)
    { 
       fprintf(stdout, "Printing bucket %d\n", i);  
       printLL(ht->h[i]);
    }

}

// And so forth
