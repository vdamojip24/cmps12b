# include <stdint.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include <ctype.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>
# include <getopt.h>
# include "huffman.h"
# include "queue.h"
# include "stack.h"
# define MAXQSIZE 512
# define NODECHAR 254




queue * newQueue ( uint32_t len )
{
  queue *nq; /*new node*/
  nq = (queue *) calloc (1,sizeof(queue));
  if (! nq)
  {
    printf("out of memory!!");
    return NULL;
  }
  nq->size = len;
  nq->head = 0;
  nq->tail = 0;
  nq->Q = (treeNode *)calloc (len,sizeof(treeNode));
  if (! nq->Q)
  {
    printf("out of memory!!");
  }
  return nq;  
}


void delQueue (queue *q)
{
  /*for(uint32_t i = 0; i < q->size; i++)
  {
    if(&q->Q[i] != NULL)
    {
      delNode(&q->Q[i]);
    }
  }*/
  free(q->Q);
  free(q);
}


bool enqueue ( queue *q, treeNode *tN)
{
  int i=0;
  int pos;
  if (q->tail >= MAXQSIZE)
  {
    printf("error, reached end of queue\n");
    exit(4);
  }
  treeNode *curr, *next;
  if (q->head == q->tail )
  {
    pos = q->tail;
  }
  else
  {
    /* start at tail, skip until counts match*/
    for (i = q->tail-1; i >= 0; --i)
    {
      curr = q->Q+i; 
      next = q->Q+(i+1);
      if (tN->count < curr->count)
      {
        next->symbol= curr->symbol;
        next->count= curr->count;
        next->leaf= curr->leaf;
        next->left= curr->left;
        next->right= curr->right;
      }
      else
      {
        break;
      }
    }
    pos=i+1;
  }
  q->Q[pos].symbol= tN->symbol;
  q->Q[pos].count= tN->count;
  q->Q[pos].leaf= tN->leaf;
  q->Q[pos].left= tN->left;
  q->Q[pos].right= tN->right;
  q->tail = (q->tail +1) % q->size;

  return 1;
}


bool dequeue ( queue *q, treeNode *i)
{
  if(q->head == q->tail)
  {
    return false;
  }
  else
  {
    *i = q->Q[q->head];
    q->head = (q->head+1) % q->size;
    return true;
  }
}

treeNode * newNode ( uint8_t s, bool l, uint64_t c)
{
  treeNode *node = (treeNode *)calloc(1, sizeof(treeNode));
  node->symbol = s;
  node->leaf = l;
  node->right = NULL;
  node->left = NULL;
  node->count = c;
  return node;
}

treeNode * loadTree (uint8_t savedTree [] , uint16_t treeBytes )
{
  stack *hstack;
  treeNode *node, *rightTreeNode, *leftTreeNode, *rootNode;
  char symbol, nodeType;

  hstack = newStack(treeBytes);//creates a new stack and allocates memory to it
  int j=0;
  while(j < treeBytes)
  {
      nodeType = savedTree[j];
      if (nodeType == 'L')//if the node is a leaf node, then it gets the symbol following the 'L'
      {
        treeNode *leafNode = malloc(sizeof(treeNode));
          symbol = savedTree[j+1];
          leafNode->symbol = symbol;
          leafNode->count = 0;
          leafNode->leaf = true;
          leafNode->left = NULL;
          leafNode->right = NULL;
          push(hstack, leafNode);//pushes the leaf node on to the stack
          j = j + 2;
      }
        else if(nodeType == 'I')//if the node is an interior node, then we combine the right child and left child and push them back on to the stack
        {
          rightTreeNode = pop(hstack);
          leftTreeNode = pop(hstack);
          node = join(leftTreeNode, rightTreeNode);
          push(hstack, node);
          j++;
        }

  }
  rootNode = pop(hstack);//pops the single rootnode off the stack
  return rootNode;
}


void dumpTree ( treeNode *t, FILE* out)
{
  if (t == NIL)
  {
    return;
  }
  dumpTree(t->left, out);
  dumpTree(t->right, out);
  if (t->leaf)
  {
    fprintf(out, "L%c", t->symbol);
  }
  else
  {
    fprintf(out, "I");
  }
}

treeNode * join ( treeNode *l, treeNode *r)
{
  treeNode *jointNode;
  char symbol = '*';
  jointNode = newNode((uint8_t)symbol, false, l->count + r->count);//creates a new jointNode from the left and right node
  jointNode->left = l; 
  jointNode->right = r;
  return jointNode;

} 

void buildCode ( treeNode *t, code *s, code *table)
{
  uint32_t val=0;
  if (t == NIL)
  {
    return;
  }

  if (t->leaf)
  {
    /*s->count = t->count;
    copyCode(&table[t->symbol], s);*/
    table[t->symbol] = *s;
    /*for(uint32_t j = 0; j < s->l; j++)
    {
      uint32_t bitVal = (s->bits[j>>3] & (0x1<<(j%8))) >> (j%8);
      printf("%d", bitVal);
    }
    printf("\n"); */
  }
  else
  {
    pushCode(s, 0);
    buildCode(t->left, s, table);
    popCode(s, &val);
    pushCode(s,1);
    buildCode(t->right, s, table);
    popCode(s, &val);
  }
}

static inline void spaces(int c) { for (int i = 0; i < c; i += 1) { putchar(' '); } return; }

void printTree(treeNode *t, int depth)
{
  if (t) 
  {
    printTree(t->left, depth + 1);

    if (t->leaf)
    {
      if (isalnum(t->symbol))
      {
        spaces(4 * depth); printf("'%c' (%lu)\n", t->symbol, t->count);
      }
      else
      {
      spaces(4 * depth); printf("0x%X (%lu)\n", t->symbol, t->count);
      }
    }
    else
    {
      spaces(4 * depth); printf("$ (%lu)\n", t->count);
    }

    printTree(t->right, depth + 1); 
  }

  return;
}
