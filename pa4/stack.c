# include <stdio.h>
# include <stdint.h>
# include <stdbool.h>
# include <stdlib.h>
# include <fcntl.h>
# include <inttypes.h>
//#include "code.h"
# include "huffman.h"
# include "stack.h"

stack *newStack(uint16_t size)
{
    stack *theStack = (stack *)malloc(sizeof(struct stack));//creates pointer to stack and allocates memory for it
    
    treeNode **itemArray = (treeNode **)calloc(size, sizeof(treeNode *));//creates the memory for the array for the stack items
    if(size == 0)//error checking for size of stack
    {
        printf("size must be greater than 0\n");
        return NULL;
    }
    if (itemArray == NULL)//error checking for memory allocation
    {
	   printf("Failed to allocated memory for array\n");
	   return NULL;
    }

    theStack->entries = itemArray;//sets the entries of the stack into the array
    theStack->size = size;//sets the size of the stack
    theStack->top = 0;//sets the top of the stack at 0 when creating it
    return theStack;
}

void delStack(stack *theStack)
{
    free(theStack->entries);//deletes entries of the stack by freeing up memory
    theStack->entries = NULL;//sets pointer to NULL 
    free(theStack);//frees up memory for the stack pointer
    theStack = NULL;//sets the pointer to NULL
    //theStack->size = 0;
    //theStack->top = 0;
}

treeNode *pop(stack *theStack)
{
	treeNode *popped = NULL;//creates a popped tree node
    if (empty(theStack))//checks to see if stack is empty
    {
	   printf("Node can't be popped from stack - stack is empty\n");
        return NULL;
    }
    else 
    {
        popped = theStack->entries[theStack->top-1];//pops the top item of the stack
        theStack->top--;//decrements top by one since the one node is popped off
    }
    return popped;//returns the popped node
}

void push(stack *theStack, treeNode *node)
{
    if (full(theStack))//checks to see if the stack is full
    {
        printf("Node can't be pushed on stack - stack is full\n");
        return;
    }
    theStack->entries[theStack->top++] = node;//pushes a tree Node onto the stack and then increments the top after since one node is added
}

bool empty(stack *theStack)
{
    bool emptyStack = false;
    if(theStack->top == 0)//checks to see if the stack is empty by checking if the top is 0
    {
        emptyStack = true;
    }
    return emptyStack;
}

bool full(stack *theStack)
{
    bool fullStack = false;
    if(theStack->top == theStack->size)//checks to see if the stack is full by comparing the top and the size
    {
        fullStack = true;
    }
    return fullStack;
}
