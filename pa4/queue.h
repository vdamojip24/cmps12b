# ifndef _QUEUE_H
# define _QUEUE_H
//code given by Professor Long
typedef treeNode item ; 

typedef struct queue
{
uint32_t size ;
uint32_t head , tail ; 
treeNode *Q; 
} queue ;

queue * newQueue ( uint32_t size ); 
void delQueue ( queue *q) ; 

//bool empty ( queue *q) ;
//bool full ( queue *q) ; 

bool enqueue ( queue *q, treeNode *Q) ; 
bool dequeue ( queue *q, treeNode *Q) ; 

# endif