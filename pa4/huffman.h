# ifndef _HUFFMAN_H
# define _HUFFMAN_H
# include <stdint.h>
# include <stdbool.h>
# include "code.h"


# ifndef NIL
# define NIL ( void *) 0
# endif

//header file given by Professor Long
typedef struct DAH treeNode ;

struct DAH
{
uint8_t symbol ;
uint64_t count ;
bool leaf ;
treeNode *left , * right ;
};

// New node , with symbols , leaf or not , a count associated with it
treeNode * newNode ( uint8_t s, bool l, uint64_t c) ;

// Dump a Huffman tree onto a file
//void dumpTree ( treeNode *t, uint16_t depth, FILE *fptr) ;

void dumpTree(treeNode *t, FILE *in);

// Build a tree from the saved tree
treeNode * loadTree (uint8_t savedTree [] , uint16_t treeBytes ) ;

// Step through a tree following the code
//int32_t stepTree ( treeNode *root , treeNode **t, uint32_t code ) ;

// Parse a Huffman tree to build codes
//void buildCode ( treeNode *t, code s, code table [256]) ;
void buildCode ( treeNode *t, code *s, code *table);

static inline void delNode ( treeNode *h) { free (h) ; return ; }

// Deletes the entire tree
static inline void delTree(treeNode *t)
{
	if(t != NULL)
	{
		delTree(t->left); 
		delTree(t->right);
		delNode(t);
	}
}


static inline int8_t compare ( treeNode *l, treeNode *r)
{
return l->count - r->count ; // l < r if negative , l = r if 0 , ...
}

//void printTree(treeNode *t , int depth);

treeNode * join ( treeNode *l, treeNode *r) ; // Join two subtrees
# endif 

