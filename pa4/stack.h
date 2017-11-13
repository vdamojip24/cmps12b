# ifndef _STACK_H
# define _STACK_H
# include <stdint.h>
# include <stdbool.h>
# include "huffman.h"

//header file given by Professor Long
typedef struct stack
{
uint32_t size ; //size of the stack
uint32_t top ; //top of the stack
treeNode **entries ; //array that holds stack entries
} stack ;

stack * newStack (uint16_t) ; // Constructor
void delStack ( stack *) ; // Destructor

treeNode *pop ( stack *) ; // Returns the top item
void push ( stack *, treeNode *) ; // Adds an item to the top

bool empty ( stack *) ; //checks to see if stack is empty
bool full ( stack *) ; //checks to see if stack is full

# endif
